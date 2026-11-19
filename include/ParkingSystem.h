#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Config.h"

struct VehicleCard {
    String uid;
    String licensePlate;
    String ownerName;
    bool isParked;
    unsigned long entryTime;
};

enum CardProcessResult {
    CARD_NOT_FOUND,
    CARD_CHECK_IN,
    CARD_CHECK_OUT,
    CARD_PARKING_FULL
};

struct CardScanEvent {
    CardProcessResult result;
    VehicleCard card;
    unsigned long durationSec;
    uint32_t fee;
};

class ParkingSystem {
public:
    ParkingSystem(uint8_t lcdAddr, int buzzerPin, int maxCapacity = 2);

    void begin();
    CardScanEvent processCard(const String& rawUid);

    int getOccupiedCount() const;
    int getMaxCapacity() const;
    bool isFull() const;

    void showHome();
    void showCheckIn(const String& plate);
    void showCheckOut(const String& plate, unsigned long durationSec, uint32_t fee);
    void showLotFull();
    void showDenied();
    void showStatus(const String& line1, const String& line2);

    void beep(int count, int durationMs = 80, int pauseMs = 50);

private:
    LiquidCrystal_I2C _lcd;
    int _buzzerPin;
    int _maxCapacity;

    static const int CARD_COUNT = 6;
    VehicleCard _cards[CARD_COUNT];

    int findCardIndex(const String& uid);
};
