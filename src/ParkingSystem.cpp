#include "ParkingSystem.h"

ParkingSystem::ParkingSystem(uint8_t lcdAddr, int buzzerPin, int maxCapacity)
    : _lcd(lcdAddr, LCD_COLS, LCD_ROWS), _buzzerPin(buzzerPin), _maxCapacity(maxCapacity) {
    _cards[0] = {"04 3B 2A 1C", "29A-123.45", "Nguyen Van A", false, 0};
    _cards[1] = {"14 8C 3D 2E", "51F-999.88", "Tran Thi B",   false, 0};
    _cards[2] = {"24 D5 4E 3F", "43C-678.90", "Le Van C",     false, 0};
    _cards[3] = {"34 E6 5F 4A", "92B-456.78", "Pham Thi D",   false, 0};
}

void ParkingSystem::begin() {
    pinMode(_buzzerPin, OUTPUT);
    digitalWrite(_buzzerPin, LOW);

    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    _lcd.init();
    _lcd.backlight();
    showHome();
}

int ParkingSystem::findCardIndex(const String& uid) {
    for (int i = 0; i < CARD_COUNT; i++) {
        if (uid.equalsIgnoreCase(_cards[i].uid)) {
            return i;
        }
    }
    return -1;
}

int ParkingSystem::getOccupiedCount() const {
    int count = 0;
    for (int i = 0; i < CARD_COUNT; i++) {
        if (_cards[i].isParked) count++;
    }
    return count;
}

int ParkingSystem::getMaxCapacity() const {
    return _maxCapacity;
}

bool ParkingSystem::isFull() const {
    return getOccupiedCount() >= _maxCapacity;
}

CardScanEvent ParkingSystem::processCard(const String& rawUid) {
    CardScanEvent event;
    int idx = findCardIndex(rawUid);

    if (idx == -1) {
        event.result = CARD_NOT_FOUND;
        event.card.uid = rawUid;
        event.durationSec = 0;
        event.fee = 0;
        return event;
    }

    VehicleCard& card = _cards[idx];
    unsigned long now = millis();

    if (!card.isParked) {
        if (isFull()) {
            event.result = CARD_PARKING_FULL;
            event.card = card;
            event.durationSec = 0;
            event.fee = 0;
            return event;
        }

        card.isParked = true;
        card.entryTime = now;
        event.result = CARD_CHECK_IN;
        event.card = card;
        event.durationSec = 0;
        event.fee = 0;
    } else {
        card.isParked = false;
        unsigned long dur = (now - card.entryTime) / 1000;
        if (dur == 0) dur = 1;

        uint32_t fee = 3000;
        if (dur > 30) fee = 9000;
        else if (dur >= 10) fee = 5000;

        event.result = CARD_CHECK_OUT;
        event.card = card;
        event.durationSec = dur;
        event.fee = fee;
    }

    return event;
}

void ParkingSystem::showHome() {
    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.printf("BAI XE: %d/%d XE", getOccupiedCount(), _maxCapacity);
    _lcd.setCursor(0, 1);
    _lcd.print("Moi quet the...");
}

void ParkingSystem::showCheckIn(const String& plate) {
    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print("VAO: " + plate);
    _lcd.setCursor(0, 1);
    _lcd.print("Moi vao! -> MO");
}

void ParkingSystem::showCheckOut(const String& plate, unsigned long durationSec, uint32_t fee) {
    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print("RA: " + plate);
    _lcd.setCursor(0, 1);
    _lcd.printf("T:%lus %ud", durationSec, fee);
}

void ParkingSystem::showLotFull() {
    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print("BAI XE DA DAY!");
    _lcd.setCursor(0, 1);
    _lcd.print("Vui long quay lai");
}

void ParkingSystem::showDenied() {
    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print("THE KHONG HOP LE");
    _lcd.setCursor(0, 1);
    _lcd.print("Tu choi truy cap");
}

void ParkingSystem::showStatus(const String& line1, const String& line2) {
    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print(line1);
    _lcd.setCursor(0, 1);
    _lcd.print(line2);
}

void ParkingSystem::beep(int count, int durationMs, int pauseMs) {
    for (int i = 0; i < count; i++) {
        long pulses = (long)1500 * durationMs / 1000;
        for (long j = 0; j < pulses; j++) {
            digitalWrite(_buzzerPin, HIGH);
            delayMicroseconds(333);
            digitalWrite(_buzzerPin, LOW);
            delayMicroseconds(333);
        }
        if (count > 1 && i < count - 1) {
            delay(pauseMs);
        }
    }
}
