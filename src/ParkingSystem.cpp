#include "ParkingSystem.h"

ParkingSystem::ParkingSystem(uint8_t lcdAddr, int buzzerPin)
    : _lcd(lcdAddr, LCD_COLS, LCD_ROWS), _buzzerPin(buzzerPin),
      _homeAt(0), _beepLeft(0), _beepOnMs(0), _beepOffMs(0), _beepOn(false), _beepAt(0) {
    // The da dang ky (trung UID voi the mau cua Wokwi MFRC522).
    // The Red "AA BB CC DD" co y KHONG dang ky de mo phong the la.
    _cards[0] = {"01 02 03 04", "29A-123.45", "Nguyễn Văn A", 0, 0};   // Blue card   / phim 1
    _cards[1] = {"11 22 33 44", "51F-999.88", "Trần Thị B",   0, 0};   // Green card  / phim 2
    _cards[2] = {"55 66 77 88", "43C-678.90", "Lê Văn C",     0, 0};   // Yellow card / phim 3
}

void ParkingSystem::begin() {
    ledcSetup(BUZZER_LEDC_CH, BUZZER_FREQ_HZ, 8);
    ledcAttachPin(_buzzerPin, BUZZER_LEDC_CH);
    ledcWriteTone(BUZZER_LEDC_CH, 0);

    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    _lcd.init();
    _lcd.backlight();
    showMessage("BAI GIU XE RFID", "Dang khoi dong..");
}

// ---------------------------------------------------------------------------
// Non-blocking services
// ---------------------------------------------------------------------------
void ParkingSystem::update() {
    unsigned long now = millis();

    if (_homeAt != 0 && (long)(now - _homeAt) >= 0) {
        _homeAt = 0;
        showHome();
    }

    if (_beepLeft > 0 && (long)(now - _beepAt) >= 0) {
        if (_beepOn) {
            ledcWriteTone(BUZZER_LEDC_CH, 0);
            _beepOn = false;
            _beepLeft--;
            _beepAt = now + _beepOffMs;
        } else {
            ledcWriteTone(BUZZER_LEDC_CH, BUZZER_FREQ_HZ);
            _beepOn = true;
            _beepAt = now + _beepOnMs;
        }
    }
}

void ParkingSystem::beep(int count, int onMs, int offMs) {
    _beepLeft  = count;
    _beepOnMs  = onMs;
    _beepOffMs = offMs;
    _beepOn    = false;
    _beepAt    = millis();
    ledcWriteTone(BUZZER_LEDC_CH, 0);
}

// ---------------------------------------------------------------------------
// Business logic
// ---------------------------------------------------------------------------
int ParkingSystem::findCardIndex(const String& uid) const {
    for (int i = 0; i < CARD_COUNT; i++) {
        if (uid.equalsIgnoreCase(_cards[i].uid)) return i;
    }
    return -1;
}

int ParkingSystem::findFreeSlot() const {
    for (int s = 1; s <= PARKING_CAPACITY; s++) {
        if (cardInSlot(s) == nullptr) return s;
    }
    return 0;
}

const VehicleCard* ParkingSystem::cardInSlot(int slot) const {
    for (int i = 0; i < CARD_COUNT; i++) {
        if (_cards[i].slot == slot) return &_cards[i];
    }
    return nullptr;
}

int ParkingSystem::getOccupiedCount() const {
    int count = 0;
    for (int i = 0; i < CARD_COUNT; i++) {
        if (_cards[i].slot > 0) count++;
    }
    return count;
}

uint32_t ParkingSystem::calcFee(unsigned long durationSec) {
    if (durationSec > FEE_TIER2_SEC) return FEE_TIER3_VND;
    if (durationSec >= FEE_TIER1_SEC) return FEE_TIER2_VND;
    return FEE_TIER1_VND;
}

CardScanEvent ParkingSystem::processCard(const String& rawUid) {
    CardScanEvent ev;
    ev.uid = rawUid;
    ev.slot = 0;
    ev.durationSec = 0;
    ev.fee = 0;

    int idx = findCardIndex(rawUid);
    if (idx < 0) {
        ev.result = CARD_NOT_FOUND;
        return ev;
    }

    VehicleCard& card = _cards[idx];
    ev.uid = card.uid;
    ev.licensePlate = card.licensePlate;
    ev.ownerName = card.ownerName;

    if (card.slot == 0) {
        int slot = findFreeSlot();
        if (slot == 0) {
            ev.result = CARD_PARKING_FULL;
            return ev;
        }
        card.slot = slot;
        card.entryTime = millis();
        ev.result = CARD_CHECK_IN;
        ev.slot = slot;
    } else {
        unsigned long dur = (millis() - card.entryTime) / 1000;
        if (dur == 0) dur = 1;
        ev.result = CARD_CHECK_OUT;
        ev.slot = card.slot;
        ev.durationSec = dur;
        ev.fee = calcFee(dur);
        card.slot = 0;
        card.entryTime = 0;
    }
    return ev;
}

// ---------------------------------------------------------------------------
// LCD screens (16 x 2)
// ---------------------------------------------------------------------------
void ParkingSystem::showMessage(const char* line1, const char* line2, unsigned long autoHomeMs) {
    _lcd.clear();
    _lcd.setCursor(0, 0);
    _lcd.print(line1);
    _lcd.setCursor(0, 1);
    _lcd.print(line2);
    _homeAt = autoHomeMs ? millis() + autoHomeMs : 0;
}

void ParkingSystem::showHome() {
    char l1[17], l2[17];
    int used = getOccupiedCount();
    snprintf(l1, sizeof(l1), "BAI XE: %d/%d XE", used, PARKING_CAPACITY);
    snprintf(l2, sizeof(l2), used >= PARKING_CAPACITY ? "Het cho trong" : "Moi quet the...");
    showMessage(l1, l2);
}

void ParkingSystem::showCheckIn(const String& plate, int slot) {
    char l1[17], l2[17];
    snprintf(l1, sizeof(l1), "VAO: %s", plate.c_str());
    snprintf(l2, sizeof(l2), "O so %d - Moi vao", slot);
    showMessage(l1, l2);
}

void ParkingSystem::showCheckOut(const String& plate, unsigned long durationSec, uint32_t fee) {
    char l1[17], l2[17];
    snprintf(l1, sizeof(l1), "RA: %s", plate.c_str());
    snprintf(l2, sizeof(l2), "%lus Phi:%lud", durationSec, (unsigned long)fee);
    showMessage(l1, l2);
}

void ParkingSystem::showLotFull()          { showMessage("BAI XE DA DAY!", "Het cho gui xe!", LCD_MESSAGE_MS); }
void ParkingSystem::showDenied()           { showMessage("THE KHONG HOP LE", "Tu choi vao bai", LCD_MESSAGE_MS); }
void ParkingSystem::showRemoteOpen()       { showMessage("MO BARIE TU XA", "Lenh: Dashboard"); }

void ParkingSystem::showObstacle(float distCm) {
    char l2[17];
    snprintf(l2, sizeof(l2), "Vat can %.0fcm", distCm);
    showMessage("TAM HOAN DONG", l2);
}
