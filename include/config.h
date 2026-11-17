#pragma once
#include <Arduino.h>

// Pin mapping
#define PIN_SS          5
#define PIN_RST         4
#define PIN_SERVO       13
#define PIN_BUZZER      14
#define PIN_I2C_SDA     21
#define PIN_I2C_SCL     22
#define PIN_LED_RED     25
#define PIN_LED_GREEN   26
#define PIN_TRIG        27
#define PIN_ECHO        32

// Hardware parameters
#define LCD_I2C_ADDR    0x27
#define LCD_COLS        16
#define LCD_ROWS        2

const int SERVO_OPEN_ANGLE    = 90;
const int SERVO_CLOSE_ANGLE   = 0;
const unsigned long GATE_HOLD_MS = 3500;
const float ANTI_PINCH_DIST_CM   = 15.0;

// Network parameters
const char* const WIFI_SSID   = "Wokwi-GUEST";
const char* const WIFI_PASS   = "";
const char* const MQTT_BROKER = "broker.hivemq.com";
const int         MQTT_PORT   = 1883;
#define MQTT_PREFIX           "parking_n4/"

#define MQTT_TOPIC_SCAN       MQTT_PREFIX "rfid/scan"
#define MQTT_TOPIC_CMD        MQTT_PREFIX "barie/cmd"
#define MQTT_TOPIC_BARIE_STAT MQTT_PREFIX "barie/status"
#define MQTT_TOPIC_ALERT      MQTT_PREFIX "alert"
#define MQTT_TOPIC_STATUS     MQTT_PREFIX "status"
