#include "MqttService.h"

static MqttService* s_instance = nullptr;

MqttService::MqttService(const char* ssid, const char* pass, const char* broker, int port)
    : _ssid(ssid), _pass(pass), _broker(broker), _port(port),
      _mqttClient(_wifiClient), _lastReconnectAttempt(0) {
    s_instance = this;
}

void MqttService::onMqttMessage(char* topic, byte* payload, unsigned int length) {
    if (!s_instance || !s_instance->_commandCallback) return;

    String msg = "";
    for (unsigned int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }
    msg.trim();

    if (String(topic) == MQTT_TOPIC_CMD) {
        String cmd = msg;
        JsonDocument doc;
        if (!deserializeJson(doc, msg) && doc["cmd"].is<const char*>()) {
            cmd = doc["cmd"].as<String>();
        }
        cmd.toLowerCase();
        s_instance->_commandCallback(cmd);
    }
}

void MqttService::begin(CommandCallback onCommand) {
    _commandCallback = onCommand;
    _clientId = "ESP32_Parking_" + String(random(0xffff), HEX);

    _mqttClient.setServer(_broker, _port);
    _mqttClient.setCallback(onMqttMessage);
    _mqttClient.setBufferSize(512);

    connectWiFi();
    connectMqtt();
}

void MqttService::connectWiFi() {
    Serial.printf("[WIFI] Connecting to %s...\n", _ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(_ssid, _pass);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 8000) {
        delay(300);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("\n[WIFI] Connected. IP: %s\n", WiFi.localIP().toString().c_str());
    } else {
        Serial.println("\n[WIFI] Connection timeout. Retrying in background.");
    }
}

void MqttService::connectMqtt() {
    if (WiFi.status() != WL_CONNECTED) return;
    if (_mqttClient.connected()) return;

    unsigned long now = millis();
    if (now - _lastReconnectAttempt < 5000) return;
    _lastReconnectAttempt = now;

    Serial.printf("[MQTT] Connecting to broker %s:%d...\n", _broker, _port);
    if (_mqttClient.connect(_clientId.c_str())) {
        Serial.println("[MQTT] Connected.");
        _mqttClient.subscribe(MQTT_TOPIC_CMD);
        _mqttClient.publish(MQTT_TOPIC_STATUS, "{\"status\":\"online\"}");
    } else {
        Serial.printf("[MQTT] Connect failed (rc=%d)\n", _mqttClient.state());
    }
}

void MqttService::update() {
    if (WiFi.status() == WL_CONNECTED) {
        if (!_mqttClient.connected()) {
            connectMqtt();
        } else {
            _mqttClient.loop();
        }
    }
}

bool MqttService::isConnected() {
    return _mqttClient.connected();
}

void MqttService::publishScan(const String& uid, const String& action, const String& plate,
                              const String& owner, unsigned long durationSec, uint32_t fee,
                              int occupied, int capacity) {
    if (!_mqttClient.connected()) return;

    JsonDocument doc;
    doc["uid"]          = uid;
    doc["action"]       = action;
    doc["licensePlate"] = plate;
    doc["ownerName"]    = owner;
    doc["durationSec"]  = durationSec;
    doc["fee"]          = fee;
    doc["parkedCount"]  = occupied;
    doc["totalSlots"]   = capacity;

    char buf[300];
    serializeJson(doc, buf);
    _mqttClient.publish(MQTT_TOPIC_SCAN, buf);
}

void MqttService::publishAlert(const String& type, const String& uid) {
    if (!_mqttClient.connected()) return;

    JsonDocument doc;
    doc["type"] = type;
    doc["uid"]  = uid;

    char buf[128];
    serializeJson(doc, buf);
    _mqttClient.publish(MQTT_TOPIC_ALERT, buf);
}

void MqttService::publishGateState(bool isOpen) {
    if (!_mqttClient.connected()) return;
    _mqttClient.publish(MQTT_TOPIC_BARIE_STAT, isOpen ? "{\"state\":\"open\"}" : "{\"state\":\"closed\"}");
}
