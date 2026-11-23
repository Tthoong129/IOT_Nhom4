// ============================================================================
// He thong bai giu xe may tu quan su dung RFID - Tang 1 & 2 (ESP32)
//  - Doc the RFID, quyet dinh vao/ra/tu choi NGAY TAI CONG (khong phu thuoc mang)
//  - Dieu khien barie + chong kep xe (HC-SR04), LCD, den LED, buzzer
//  - Dong bo trang thai len Node-RED qua MQTT (ESP32 la nguon du lieu goc)
// ============================================================================
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include "Config.h"
#include "GateController.h"
#include "ParkingSystem.h"
#include "MqttService.h"

GateController gate(PIN_SERVO, PIN_TRIG, PIN_ECHO, PIN_LED_RED, PIN_LED_GREEN);
ParkingSystem  parking(LCD_I2C_ADDR, PIN_BUZZER);
MqttService    mqtt(WIFI_SSID, WIFI_PASS, MQTT_BROKER, MQTT_PORT);
MFRC522        rfid(PIN_SS, PIN_RST);

String        lastUid = "";
unsigned long lastUidSeen = 0;

// ---------------------------------------------------------------------------
// MQTT publishers
// ---------------------------------------------------------------------------
// Snapshot toan bo trang thai (retained): Node-RED dung de dong bo khi khoi dong / ket noi lai
void publishSnapshot() {
    JsonDocument doc;
    doc["online"]   = true;
    doc["gate"]     = gate.isOpen() ? "open" : "closed";
    doc["occupied"] = parking.getOccupiedCount();
    doc["capacity"] = parking.getCapacity();
    doc["uptime"]   = millis() / 1000;
    doc["rssi"]     = WiFi.RSSI();
    JsonArray slots = doc["slots"].to<JsonArray>();
    for (int s = 1; s <= parking.getCapacity(); s++) {
        JsonObject o = slots.add<JsonObject>();
        o["slot"] = s;
        const VehicleCard* c = parking.cardInSlot(s);
        if (c) {
            o["uid"]       = c->uid;
            o["plate"]     = c->licensePlate;
            o["owner"]     = c->ownerName;
            o["parkedSec"] = (millis() - c->entryTime) / 1000;
        }
    }
    mqtt.publishJson(MQTT_TOPIC_STATUS, doc, true);
}

void publishGateState() {
    JsonDocument doc;
    doc["state"]  = gate.isOpen() ? "open" : "closed";
    doc["mode"]   = gate.getMode() == GateController::GATE_OPEN_HOLD ? "hold"
                  : gate.getMode() == GateController::GATE_OPEN_TIMED ? "auto" : "none";
    doc["source"] = gate.source();
    doc["angle"]  = gate.isOpen() ? SERVO_OPEN_ANGLE : SERVO_CLOSE_ANGLE;
    mqtt.publishJson(MQTT_TOPIC_BARIE_STAT, doc, true);
}

void publishScan(const CardScanEvent& ev, const char* action) {
    JsonDocument doc;
    doc["action"]       = action;
    doc["uid"]          = ev.uid;
    doc["licensePlate"] = ev.licensePlate;
    doc["ownerName"]    = ev.ownerName;
    doc["slot"]         = ev.slot;
    doc["durationSec"]  = ev.durationSec;
    doc["fee"]          = ev.fee;
    doc["parkedCount"]  = parking.getOccupiedCount();
    doc["totalSlots"]   = parking.getCapacity();
    mqtt.publishJson(MQTT_TOPIC_SCAN, doc);
}

void publishAlert(const char* type, const String& uid, const String& plate, float distCm = -1) {
    JsonDocument doc;
    doc["type"] = type;
    if (uid.length())   doc["uid"] = uid;
    if (plate.length()) doc["licensePlate"] = plate;
    if (distCm >= 0)    doc["distanceCm"] = round(distCm * 10) / 10.0;
    doc["parkedCount"] = parking.getOccupiedCount();
    doc["totalSlots"]  = parking.getCapacity();
    mqtt.publishJson(MQTT_TOPIC_ALERT, doc);
}

// ---------------------------------------------------------------------------
// Card handling (quyet dinh tai cong)
// ---------------------------------------------------------------------------
void handleCardScan(const String& uid) {
    if (gate.isOpen()) {
        Serial.println("[RFID] Gate is open, scan ignored.");
        return;
    }

    CardScanEvent ev = parking.processCard(uid);
    switch (ev.result) {
        case CARD_CHECK_IN:
            Serial.printf("[IN ] %s | %s | slot %d\n", ev.licensePlate.c_str(), ev.uid.c_str(), ev.slot);
            parking.showCheckIn(ev.licensePlate, ev.slot);
            parking.beep(1, 150);
            gate.open(false, "card");
            publishScan(ev, "check_in");
            publishGateState();
            publishSnapshot();
            break;

        case CARD_CHECK_OUT:
            Serial.printf("[OUT] %s | %lus | %lu VND\n", ev.licensePlate.c_str(), ev.durationSec, (unsigned long)ev.fee);
            parking.showCheckOut(ev.licensePlate, ev.durationSec, ev.fee);
            parking.beep(2, 100);
            gate.open(false, "card");
            publishScan(ev, "check_out");
            publishGateState();
            publishSnapshot();
            break;

        case CARD_PARKING_FULL:
            Serial.printf("[FULL] %s denied: parking lot is full.\n", ev.licensePlate.c_str());
            parking.showLotFull();
            parking.beep(2, 250, 120);
            publishAlert("LOT_FULL", ev.uid, ev.licensePlate);
            break;

        case CARD_NOT_FOUND:
            Serial.printf("[DENY] Unregistered card: %s\n", uid.c_str());
            parking.showDenied();
            parking.beep(3, 120);
            publishAlert("INVALID_CARD", uid, "");
            break;
    }
}

// ---------------------------------------------------------------------------
// Downlink commands (Dashboard / Rule 4 / Serial)
// ---------------------------------------------------------------------------
void onCommand(const String& cmd, const String& src) {
    Serial.printf("[CMD] %s (src=%s)\n", cmd.c_str(), src.c_str());

    if (cmd == "open" || cmd == "open_hold") {
        gate.open(true, src);            // Giu mo den khi co lenh dong (Rule 4 dong sau 10 s)
        parking.showRemoteOpen();
        parking.beep(1, 80);
        publishGateState();
    } else if (cmd == "close") {
        if (!gate.isOpen()) {
            publishGateState();          // Da dong san: bao lai trang thai de dashboard dong bo
            return;
        }
        gate.requestClose(src);          // Dong ngay neu thong thoang, hoan neu co vat can
    } else if (cmd == "sync") {
        publishGateState();
        publishSnapshot();
    }
}

void onMqttConnected() {
    publishGateState();
    publishSnapshot();
}

// ---------------------------------------------------------------------------
// Serial console (kiem thu tren Wokwi)
// ---------------------------------------------------------------------------
void handleSerialInput() {
    if (!Serial.available()) return;
    String line = Serial.readStringUntil('\n');
    line.trim();
    if (line.isEmpty()) return;

    if      (line == "1") handleCardScan("01 02 03 04");   // Xe 1 - Blue card
    else if (line == "2") handleCardScan("11 22 33 44");   // Xe 2 - Green card
    else if (line == "3") handleCardScan("55 66 77 88");   // Xe 3 - Yellow card
    else if (line == "4") handleCardScan("AA BB CC DD");   // The chua dang ky - Red card
    else if (line.startsWith("scan ")) { String u = line.substring(5); u.trim(); u.toUpperCase(); handleCardScan(u); }
    else if (line == "open")  onCommand("open", "serial");
    else if (line == "close") onCommand("close", "serial");
    else if (line == "sonar") Serial.printf("[SONAR] %.1f cm\n", gate.readDistanceCm());
    else if (line == "status") {
        Serial.printf("[STATUS] %d/%d xe | barie %s | MQTT %s\n", parking.getOccupiedCount(), parking.getCapacity(),
                      gate.isOpen() ? "MO" : "DONG", mqtt.isConnected() ? "OK" : "OFFLINE");
    }
    else Serial.println("Lenh: 1 2 3 (the dang ky), 4 (the la), scan <uid>, open, close, sonar, status");
}

// ---------------------------------------------------------------------------
// RFID polling: cung mot the phai roi khoi dau doc >= CARD_DEBOUNCE_MS moi duoc doc lai
// ---------------------------------------------------------------------------
void pollRfid() {
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

    String uid;
    for (byte i = 0; i < rfid.uid.size; i++) {
        if (rfid.uid.uidByte[i] < 0x10) uid += "0";
        uid += String(rfid.uid.uidByte[i], HEX);
        if (i < rfid.uid.size - 1) uid += " ";
    }
    uid.toUpperCase();
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();

    unsigned long now = millis();
    bool repeated = (uid == lastUid) && (now - lastUidSeen < CARD_DEBOUNCE_MS);
    lastUid = uid;
    lastUidSeen = now;
    if (!repeated) handleCardScan(uid);
}

// ---------------------------------------------------------------------------
void setup() {
    Serial.begin(115200);
    delay(200);
    Serial.println("\n[BOOT] RFID Smart Parking - Nhom 4");

    gate.begin();
    parking.begin();
    SPI.begin();
    rfid.PCD_Init();

    mqtt.begin(onCommand, onMqttConnected);

    parking.showHome();
    parking.beep(2, 60, 60);
    Serial.println("[BOOT] Ready. Type 'help' for serial commands.");
}

void loop() {
    mqtt.update();
    parking.update();

    switch (gate.update()) {
        case GateController::EVT_OBSTACLE:
            parking.showObstacle(gate.lastDistance());
            parking.beep(1, 300);
            publishAlert("ANTI_PINCH", "", "", gate.lastDistance());
            break;
        case GateController::EVT_CLOSED:
            parking.showHome();
            publishGateState();
            publishSnapshot();
            break;
        default:
            break;
    }

    pollRfid();
    handleSerialInput();
}
