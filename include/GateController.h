#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>
#include "Config.h"

// Dieu khien barie (servo + den LED) va co che chong kep xe bang HC-SR04.
// Barie khong bao gio ha khi con vat can < ANTI_PINCH_DIST_CM: lenh dong chi bi hoan, khong bi huy.
class GateController {
public:
    enum Mode {
        GATE_CLOSED,
        GATE_OPEN_TIMED,   // Mo do quet the, tu dong dong sau GATE_HOLD_MS
        GATE_OPEN_HOLD     // Mo tu xa, giu mo den khi co lenh dong (hoac Rule 4)
    };

    enum Event {
        EVT_NONE,
        EVT_OBSTACLE,      // Vua phat hien vat can khi chuan bi dong
        EVT_CLOSED         // Barie vua ha xuong
    };

    GateController(int servoPin, int trigPin, int echoPin, int redLedPin, int greenLedPin);

    void  begin();
    void  open(bool hold, const String& source);
    void  requestClose(const String& source);  // Dong ngay neu thong thoang, nguoc lai hoan den khi het vat can
    Event update();                            // Goi lien tuc trong loop()

    bool   isOpen() const { return _mode != GATE_CLOSED; }
    Mode   getMode() const { return _mode; }
    bool   isBlocked() const { return _blocked; }
    float  lastDistance() const { return _lastDistance; }
    const String& source() const { return _source; }
    float  readDistanceCm();

private:
    int _servoPin, _trigPin, _echoPin, _redLedPin, _greenLedPin;
    Servo _servo;
    Mode  _mode;
    bool  _closePending;     // Da co yeu cau dong, dang cho het vat can
    bool  _blocked;          // Dang hoan dong vi vat can
    unsigned long _openedAt;
    unsigned long _lastCheck;
    float  _lastDistance;
    String _source;          // Nguon gay ra thay doi gan nhat: card / dashboard / rule4 / timeout / serial

    void setLeds(bool red, bool green);
    void doClose();
};
