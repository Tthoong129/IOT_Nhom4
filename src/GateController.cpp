#include "GateController.h"

GateController::GateController(int servoPin, int trigPin, int echoPin, int redLedPin, int greenLedPin)
    : _servoPin(servoPin), _trigPin(trigPin), _echoPin(echoPin),
      _redLedPin(redLedPin), _greenLedPin(greenLedPin),
      _mode(GATE_CLOSED), _closePending(false), _blocked(false),
      _openedAt(0), _lastCheck(0), _lastDistance(999.0), _source("boot") {}

void GateController::begin() {
    pinMode(_redLedPin, OUTPUT);
    pinMode(_greenLedPin, OUTPUT);
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    _servo.setPeriodHertz(50);
    _servo.attach(_servoPin, 500, 2400);
    _servo.write(SERVO_CLOSE_ANGLE);
    setLeds(true, false);
}

void GateController::setLeds(bool red, bool green) {
    digitalWrite(_redLedPin, red ? HIGH : LOW);
    digitalWrite(_greenLedPin, green ? HIGH : LOW);
}

void GateController::open(bool hold, const String& source) {
    _servo.write(SERVO_OPEN_ANGLE);
    setLeds(false, true);
    _mode = hold ? GATE_OPEN_HOLD : GATE_OPEN_TIMED;
    _closePending = false;
    _blocked = false;
    _openedAt = millis();
    _source = source;
}

void GateController::requestClose(const String& source) {
    if (!isOpen()) return;
    _source = source;
    _closePending = true;
    _lastCheck = 0;          // Kiem tra ngay o lan update() tiep theo
}

float GateController::readDistanceCm() {
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    long duration = pulseIn(_echoPin, HIGH, 25000);   // Toi da ~4 m
    _lastDistance = (duration == 0) ? 999.0 : duration * 0.0343 / 2.0;
    return _lastDistance;
}

void GateController::doClose() {
    _servo.write(SERVO_CLOSE_ANGLE);
    setLeds(true, false);
    _mode = GATE_CLOSED;
    _closePending = false;
    _blocked = false;
}

GateController::Event GateController::update() {
    if (!isOpen()) return EVT_NONE;

    unsigned long now = millis();

    // Barie mo boi the: het thoi gian giu thi tu dong yeu cau dong
    if (_mode == GATE_OPEN_TIMED && !_closePending && now - _openedAt >= GATE_HOLD_MS) {
        _closePending = true;
        _source = "timeout";
        _lastCheck = 0;
    }

    if (!_closePending) return EVT_NONE;
    if (_lastCheck != 0 && now - _lastCheck < ANTI_PINCH_RECHECK) return EVT_NONE;
    _lastCheck = now;

    float dist = readDistanceCm();
    if (dist < ANTI_PINCH_DIST_CM) {
        if (!_blocked) {
            _blocked = true;
            Serial.printf("[GATE] Obstacle %.1f cm under barrier -> close postponed.\n", dist);
            return EVT_OBSTACLE;
        }
        return EVT_NONE;
    }

    if (_blocked) Serial.printf("[GATE] Passage clear (%.1f cm).\n", dist);
    doClose();
    Serial.printf("[GATE] Barrier closed (source=%s).\n", _source.c_str());
    return EVT_CLOSED;
}
