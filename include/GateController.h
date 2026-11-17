#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>
#include "Config.h"

class GateController {
public:
    enum State {
        GATE_CLOSED,
        GATE_OPEN,
        GATE_HOLD_MANUAL
    };

    GateController(int servoPin, int trigPin, int echoPin, int redLedPin, int greenLedPin);

    void begin();
    void open(bool holdManual = false);
    void close();
    void update();

    bool isOpen() const;
    State getState() const;
    float readObstacleDistanceCm();

private:
    int _servoPin;
    int _trigPin;
    int _echoPin;
    int _redLedPin;
    int _greenLedPin;

    Servo _servo;
    State _state;
    unsigned long _openTimer;
    float _lastDistance;

    void setLeds(bool red, bool green);
};
