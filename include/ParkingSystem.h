#pragma once
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include "Config.h"

// Quan ly the da dang ky, o do, bieu phi dong, man hinh LCD va coi buzzer (khong blocking).
struct VehicleCard {
    String uid;
    String licensePlate;
    String ownerName;      // UTF-8, chi gui len MQTT (LCD chi hien bien so)
    bool   active;         // false = the bi khoa tam thoi
    bool   monthly;        // true = ve thang (mien phi 0d khi ra vao)
    int    slot;           // 0 = khong trong bai, 1..PARKING_CAPACITY = o dang do
    unsigned long entryTime;
};

struct PricingConfig {
    bool          enabled;   // false = mien phi gui xe (0d)
    unsigned long tier1Sec;
    uint32_t      tier1Fee;
    unsigned long tier2Sec;
    uint32_t      tier2Fee;
    uint32_t      tier3Fee;
};

enum CardProcessResult {
    CARD_NOT_FOUND,
    CARD_LOCKED,
    CARD_CHECK_IN,
    CARD_CHECK_OUT,
    CARD_PARKING_FULL
};

struct CardScanEvent {
    CardProcessResult result;
    String uid;
    String licensePlate;
    String ownerName;
    bool   monthly;
    int    slot;
    unsigned long durationSec;
    uint32_t fee;
};

class ParkingSystem {
public:
    ParkingSystem(uint8_t lcdAddr, int buzzerPin);

    void begin();
    void update();                                   // Goi trong loop(): buzzer + LCD tu ve man hinh chinh
    CardScanEvent processCard(const String& rawUid);
    void applyConfig(const JsonDocument& doc);       // Cap nhat dong danh sach the + bang gia tu MQTT

    int  getOccupiedCount() const;
    int  getCardCount() const { return _cardCount; }
    int  getCapacity() const { return PARKING_CAPACITY; }
    bool isFull() const { return getOccupiedCount() >= PARKING_CAPACITY; }
    const VehicleCard* cardInSlot(int slot) const;
    const VehicleCard& cardAt(int i) const { return _cards[i]; }
    const PricingConfig& pricing() const { return _pricing; }

    // LCD
    void showHome();
    void showCheckIn(const String& plate, int slot, bool monthly);
    void showCheckOut(const String& plate, unsigned long durationSec, uint32_t fee, bool monthly);
    void showLotFull();
    void showDenied(const String& uid);
    void showLocked(const String& plate);
    void showObstacle(float distCm);
    void showRemoteOpen();
    void showMessage(const char* line1, const char* line2, unsigned long autoHomeMs = 0);

    // Buzzer
    void beep(int count, int onMs = 120, int offMs = 100);

private:
    LiquidCrystal_I2C _lcd;
    int           _buzzerPin;
    VehicleCard   _cards[MAX_CARDS];
    int           _cardCount;
    PricingConfig _pricing;

    unsigned long _homeAt;     // 0 = khong hen gio
    int  _beepLeft;
    int  _beepOnMs, _beepOffMs;
    bool _beepOn;
    unsigned long _beepAt;

    int  findCardIndex(const String& uid) const;
    int  findFreeSlot() const;
    uint32_t calcFee(unsigned long durationSec, bool monthly) const;
};
