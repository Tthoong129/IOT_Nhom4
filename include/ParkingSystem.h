#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Config.h"

// Quan ly the da dang ky, o do, tinh phi, man hinh LCD va coi buzzer (khong blocking).
struct VehicleCard {
    const char* uid;
    const char* licensePlate;
    const char* ownerName;     // UTF-8, chi gui len MQTT (LCD chi hien bien so)
    int  slot;                 // 0 = khong trong bai, 1..PARKING_CAPACITY = o dang do
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
    String uid;
    String licensePlate;
    String ownerName;
    int slot;
    unsigned long durationSec;
    uint32_t fee;
};

class ParkingSystem {
public:
    static const int CARD_COUNT = 3;

    ParkingSystem(uint8_t lcdAddr, int buzzerPin);

    void begin();
    void update();                                  // Goi trong loop(): buzzer + LCD tu ve man hinh chinh
    CardScanEvent processCard(const String& rawUid);

    int  getOccupiedCount() const;
    int  getCapacity() const { return PARKING_CAPACITY; }
    bool isFull() const { return getOccupiedCount() >= PARKING_CAPACITY; }
    const VehicleCard* cardInSlot(int slot) const;  // slot 1..PARKING_CAPACITY

    // LCD
    void showHome();
    void showCheckIn(const String& plate, int slot);
    void showCheckOut(const String& plate, unsigned long durationSec, uint32_t fee);
    void showLotFull();
    void showDenied();
    void showObstacle(float distCm);
    void showRemoteOpen();
    void showMessage(const char* line1, const char* line2, unsigned long autoHomeMs = 0);

    // Buzzer
    void beep(int count, int onMs = 120, int offMs = 100);

private:
    LiquidCrystal_I2C _lcd;
    int _buzzerPin;
    VehicleCard _cards[CARD_COUNT];

    unsigned long _homeAt;     // 0 = khong hen gio
    int  _beepLeft;
    int  _beepOnMs, _beepOffMs;
    bool _beepOn;
    unsigned long _beepAt;

    int  findCardIndex(const String& uid) const;
    int  findFreeSlot() const;
    static uint32_t calcFee(unsigned long durationSec);
};
