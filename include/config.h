#pragma once
#include <Arduino.h>

// ============================================================================
// 1. Pin mapping (ESP32 DevKit V1) - phai khop voi diagram.json
// ============================================================================
#define PIN_SS          5    // RC522 SDA (SPI CS)
#define PIN_RST         4    // RC522 RST
#define PIN_SERVO       13   // Servo barie
#define PIN_BUZZER      14   // Buzzer
#define PIN_I2C_SDA     21   // LCD 1602 I2C
#define PIN_I2C_SCL     22
#define PIN_LED_RED     25   // Den STOP
#define PIN_LED_GREEN   26   // Den GO
#define PIN_TRIG        27   // HC-SR04 TRIG
#define PIN_ECHO        32   // HC-SR04 ECHO

// ============================================================================
// 2. Hardware parameters
// ============================================================================
#define LCD_I2C_ADDR    0x27
#define LCD_COLS        16
#define LCD_ROWS        2

const int   SERVO_OPEN_ANGLE  = 90;
const int   SERVO_CLOSE_ANGLE = 0;
const int   BUZZER_LEDC_CH    = 15;     // Kenh LEDC rieng (timer 3), khong dung chung voi servo
const int   BUZZER_FREQ_HZ    = 2000;

// ============================================================================
// 3. Business rules (gia tri demo, rut ngan de trinh bay nhanh)
// ============================================================================
const int           PARKING_CAPACITY   = 2;       // Suc chua bai (so o do)
const unsigned long GATE_HOLD_MS       = 3000;    // Barie tu dong dong sau 3 giay (khi quet the)
const unsigned long ANTI_PINCH_RECHECK = 300;     // Chu ky do lai khi co vat can
const float         ANTI_PINCH_DIST_CM = 15.0;    // Vat can < 15 cm -> hoan dong
const unsigned long CARD_DEBOUNCE_MS   = 1500;    // Cung 1 the phai roi dau doc 1.5 s moi doc lai
const unsigned long LCD_MESSAGE_MS     = 2000;    // Thoi gian hien thong bao tu choi tren LCD

// Bieu phi demo (giay): < 10 s: 3.000d | 10-30 s: 5.000d | > 30 s: 9.000d
const unsigned long FEE_TIER1_SEC = 10;
const unsigned long FEE_TIER2_SEC = 30;
const uint32_t      FEE_TIER1_VND = 3000;
const uint32_t      FEE_TIER2_VND = 5000;
const uint32_t      FEE_TIER3_VND = 9000;

// ============================================================================
// 4. Network parameters
// ============================================================================
const char* const WIFI_SSID   = "Wokwi-GUEST";
const char* const WIFI_PASS   = "";
const char* const MQTT_BROKER = "broker.hivemq.com";
const int         MQTT_PORT   = 1883;
const unsigned long MQTT_RETRY_MS = 5000;         // Tu ket noi lai moi 5 giay

#define MQTT_PREFIX           "parking_n4/"
#define MQTT_TOPIC_SCAN       MQTT_PREFIX "rfid/scan"     // Uplink : luot xe vao/ra hop le
#define MQTT_TOPIC_BARIE_STAT MQTT_PREFIX "barie/status"  // Uplink : trang thai barie (retained)
#define MQTT_TOPIC_ALERT      MQTT_PREFIX "alert"         // Uplink : the la, bai day, vat can
#define MQTT_TOPIC_STATUS     MQTT_PREFIX "status"        // Uplink : snapshot thiet bi (retained + LWT)
#define MQTT_TOPIC_CMD        MQTT_PREFIX "barie/cmd"     // Downlink: open / close / sync
