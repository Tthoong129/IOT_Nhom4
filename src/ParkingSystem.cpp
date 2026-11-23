#include "ParkingSystem.h"

ParkingSystem::ParkingSystem(uint8_t lcdAddr, int buzzerPin)
    : _lcd(lcdAddr, LCD_COLS, LCD_ROWS), _buzzerPin(buzzerPin), _cardCount(0),
      _homeAt(0), _beepLeft(0), _beepOnMs(0), _beepOffMs(0), _beepOn(false), _beepAt(0) {
    _pricing = { true, DEFAULT_TIER1_SEC, DEFAULT_TIER1_FEE, DEFAULT_TIER2_SEC, DEFAULT_TIER2_FEE, DEFAULT_TIER3_FEE };

    // 3 the mac dinh (khop the mau Blue / Green / Yellow cua Wokwi MFRC522).
    // The Red "AA BB CC DD" mac dinh chua dang ky de demo quet the la, va co the them qua Dashboard.
    _cards[0] = {"01 02 03 04", "29A-123.45", "Nguyễn Văn A", true, false, 0, 0};
    _cards[1] = {"11 22 33 44", "51F-999.88", "Trần Thị B",   true, false, 0, 0};
    _cards[2] = {"55 66 77 88", "43C-678.90", "Lê Văn C",     true, false, 0, 0};
    _cardCount = 3;
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
// Dynamic configuration sync (tu Dashboard qua MQTT retained parking_n4/config)
// ---------------------------------------------------------------------------
void ParkingSystem::applyConfig(const JsonDocument& doc) {
    if (doc["p"].is<JsonObjectConst>()) {
        JsonObjectConst p = doc["p"].as<JsonObjectConst>();
        _pricing.enabled  = p["en"]  | true;
        _pricing.tier1Sec = max(1UL, (unsigned long)(p["t1s"] | DEFAULT_TIER1_SEC));
        _pricing.tier1Fee = p["t1f"] | DEFAULT_TIER1_FEE;
        _pricing.tier2Sec = max(_pricing.tier1Sec + 1, (unsigned long)(p["t2s"] | DEFAULT_TIER2_SEC));
        _pricing.tier2Fee = p["t2f"] | DEFAULT_TIER2_FEE;
        _pricing.tier3Fee = p["t3f"] | DEFAULT_TIER3_FEE;
    }

    if (doc["c"].is<JsonArrayConst>()) {
        VehicleCard next[MAX_CARDS];
        int nextCount = 0;

        // 1. Giu trang thai dang do (slot, entryTime) neu UID con trong danh sach moi
        for (JsonObjectConst item : doc["c"].as<JsonArrayConst>()) {
            if (nextCount >= MAX_CARDS) break;
            String uid = item["u"] | "";
            uid.trim();
            uid.toUpperCase();
            if (uid.isEmpty()) continue;

            VehicleCard c;
            c.uid          = uid;
            c.licensePlate = item["p"] | "N/A";
            c.ownerName    = item["o"] | "Khách";
            c.active       = item["a"] | true;
            c.monthly      = item["m"] | false;
            c.slot         = 0;
            c.entryTime    = 0;

            int oldIdx = findCardIndex(uid);
            if (oldIdx >= 0 && _cards[oldIdx].slot > 0) {
                c.slot      = _cards[oldIdx].slot;
                c.entryTime = _cards[oldIdx].entryTime;
            }
            next[nextCount++] = c;
        }

        // 2. Bao ve xe dang nam trong bai neu vi ly do nao do bi xoa nham khoi config
        for (int i = 0; i < _cardCount && nextCount < MAX_CARDS; i++) {
            if (_cards[i].slot == 0) continue;
            bool exists = false;
            for (int j = 0; j < nextCount; j++) {
                if (next[j].uid.equalsIgnoreCase(_cards[i].uid)) { exists = true; break; }
            }
            if (!exists) next[nextCount++] = _cards[i];
        }

        for (int i = 0; i < nextCount; i++) _cards[i] = next[i];
        _cardCount = nextCount;
    }

    Serial.printf("[CFG] Synced: %d cards | Fee %s (%lu/%lu/%lu)\n",
                  _cardCount, _pricing.enabled ? "ON" : "FREE",
                  (unsigned long)_pricing.tier1Fee, (unsigned long)_pricing.tier2Fee,
                  (unsigned long)_pricing.tier3Fee);
}

// ---------------------------------------------------------------------------
// Business logic
// ---------------------------------------------------------------------------
int ParkingSystem::findCardIndex(const String& uid) const {
    for (int i = 0; i < _cardCount; i++) {
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
    for (int i = 0; i < _cardCount; i++) {
        if (_cards[i].slot == slot) return &_cards[i];
    }
    return nullptr;
}

int ParkingSystem::getOccupiedCount() const {
    int count = 0;
    for (int i = 0; i < _cardCount; i++) {
        if (_cards[i].slot > 0) count++;
    }
    return count;
}

uint32_t ParkingSystem::calcFee(unsigned long durationSec, bool monthly) const {
    if (!_pricing.enabled || monthly) return 0;
    if (durationSec > _pricing.tier2Sec) return _pricing.tier3Fee;
    if (durationSec >= _pricing.tier1Sec) return _pricing.tier2Fee;
    return _pricing.tier1Fee;
}

CardScanEvent ParkingSystem::processCard(const String& rawUid) {
    CardScanEvent ev;
    ev.uid = rawUid;
    ev.monthly = false;
    ev.slot = 0;
    ev.durationSec = 0;
    ev.fee = 0;

    int idx = findCardIndex(rawUid);
    if (idx < 0) {
        ev.result = CARD_NOT_FOUND;
        return ev;
    }

    VehicleCard& card = _cards[idx];
    ev.uid          = card.uid;
    ev.licensePlate = card.licensePlate;
    ev.ownerName    = card.ownerName;
    ev.monthly      = card.monthly;

    if (card.slot == 0) {
        if (!card.active) {
            ev.result = CARD_LOCKED;
            return ev;
        }
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
        ev.fee = calcFee(dur, card.monthly);
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

void ParkingSystem::showCheckIn(const String& plate, int slot, bool monthly) {
    char l1[17], l2[17];
    snprintf(l1, sizeof(l1), "VAO: %s", plate.c_str());
    snprintf(l2, sizeof(l2), monthly ? "O so %d -VE THANG" : "O so %d - Moi vao", slot);
    showMessage(l1, l2);
}

void ParkingSystem::showCheckOut(const String& plate, unsigned long durationSec, uint32_t fee, bool monthly) {
    char l1[17], l2[17];
    snprintf(l1, sizeof(l1), "RA: %s", plate.c_str());
    if (monthly)              snprintf(l2, sizeof(l2), "%lus - VE THANG", durationSec);
    else if (!_pricing.enabled || fee == 0) snprintf(l2, sizeof(l2), "%lus - MIEN PHI", durationSec);
    else                      snprintf(l2, sizeof(l2), "%lus Phi:%lud", durationSec, (unsigned long)fee);
    showMessage(l1, l2);
}

void ParkingSystem::showLotFull()    { showMessage("BAI XE DA DAY!", "Het cho gui xe!", LCD_MESSAGE_MS); }
void ParkingSystem::showRemoteOpen() { showMessage("MO BARIE TU XA", "Lenh: Dashboard"); }

void ParkingSystem::showDenied(const String& uid) {
    char l2[17];
    snprintf(l2, sizeof(l2), "UID:%s", uid.c_str());
    showMessage("THE CHUA DANG KY", l2, LCD_MESSAGE_MS);
}

void ParkingSystem::showLocked(const String& plate) {
    char l2[17];
    snprintf(l2, sizeof(l2), "Xe: %s", plate.c_str());
    showMessage("THE DA BI KHOA!", l2, LCD_MESSAGE_MS);
}

void ParkingSystem::showObstacle(float distCm) {
    char l2[17];
    snprintf(l2, sizeof(l2), "Vat can %.0fcm", distCm);
    showMessage("TAM HOAN DONG", l2);
}
