#include "GateController.h"

GateController::GateController(int servoPin, int trigPin, int echoPin, int redLedPin, int greenLedPin)
    : _servoPin(servoPin), _trigPin(trigPin), _echoPin(echoPin),
      _redLedPin(redLedPin), _greenLedPin(greenLedPin),
      _state(GATE_CLOSED), _openTimer(0), _lastDistance(100.0) {}

void GateController::begin() {
    pinMode(_redLedPin, OUTPUT);
    pinMode(_greenLedPin, OUTPUT);
    setLeds(true, false);

    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    _servo.setPeriodHertz(50);
    _servo.attach(_servoPin, 500, 2400);
    _servo.write(SERVO_CLOSE_ANGLE);
}

void GateController::setLeds(bool red, bool green) {
    digitalWrite(_redLedPin, red ? HIGH : LOW);
    digitalWrite(_greenLedPin, green ? HIGH : LOW);
}

void GateController::open(bool holdManual) {
    _servo.write(SERVO_OPEN_ANGLE);
    _state = holdManual ? GATE_HOLD_MANUAL : GATE_OPEN;
    _openTimer = millis();
    setLeds(false, true);
}

bool GateController::close() {
    float dist = readObstacleDistanceCm();
    if (dist > 0 && dist < ANTI_PINCH_DIST_CM) {
        Serial.printf("[GATE] Cannot close: obstacle detected (dist=%.1fcm). Anti-pinch holding open.\n", dist);
        return false;
    }

    _servo.write(SERVO_CLOSE_ANGLE);
    _state = GATE_CLOSED;
    setLeds(true, false);
    return true;
}

float GateController::readObstacleDistanceCm() {
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    long duration = pulseIn(_echoPin, HIGH, 25000);
    if (duration == 0) return 999.0;
    _lastDistance = duration * 0.0343 / 2.0;
    return _lastDistance;
}

void GateController::update() {
    unsigned long now = millis();

    if (_state == GATE_OPEN) {
        if (now - _openTimer >= GATE_HOLD_MS) {
            float dist = readObstacleDistanceCm();
            if (dist > 0 && dist < ANTI_PINCH_DIST_CM) {
                // Obstacle detected under the barrier, delay close - recheck fast (every 500ms)
                _openTimer = now - (GATE_HOLD_MS - 500);
                Serial.printf("[GATE] Anti-pinch triggered (dist=%.1fcm). Holding barrier open.\n", dist);
            } else {
                close();
                Serial.println("[GATE] Passage clear. Barrier closed.");
            }
        }
    }
}

bool GateController::isOpen() const {
    return _state != GATE_CLOSED;
}

GateController::State GateController::getState() const {
    return _state;
}
