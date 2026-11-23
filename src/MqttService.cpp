#include "MqttService.h"

static MqttService* s_instance = nullptr;
static const char* LWT_OFFLINE = "{\"online\":false}";

MqttService::MqttService(const char* ssid, const char* pass, const char* broker, int port)
    : _ssid(ssid), _pass(pass), _broker(broker), _port(port),
      _mqttClient(_wifiClient), _lastReconnectAttempt(0) {
    s_instance = this;
}

void MqttService::onMqttMessage(char* topic, byte* payload, unsigned int length) {
    if (!s_instance || !s_instance->_commandCallback) return;
    if (strcmp(topic, MQTT_TOPIC_CMD) != 0) return;

    String raw;
    raw.reserve(length);
    for (unsigned int i = 0; i < length; i++) raw += (char)payload[i];
    raw.trim();

    // Chap nhan ca JSON {"cmd":"open","src":"dashboard"} lan chuoi thuan "open"
    String cmd = raw, src = "mqtt";
    JsonDocument doc;
    if (!deserializeJson(doc, raw) && doc["cmd"].is<const char*>()) {
        cmd = doc["cmd"].as<String>();
        if (doc["src"].is<const char*>()) src = doc["src"].as<String>();
    }
    cmd.toLowerCase();
    s_instance->_commandCallback(cmd, src);
}

void MqttService::begin(CommandCallback onCommand, ConnectCallback onConnect) {
    _commandCallback = onCommand;
    _connectCallback = onConnect;
    _clientId = "ESP32_Parking_N4_" + String((uint32_t)ESP.getEfuseMac(), HEX);

    _mqttClient.setServer(_broker, _port);
    _mqttClient.setCallback(onMqttMessage);
    _mqttClient.setBufferSize(768);
    _mqttClient.setKeepAlive(15);       // Broker phat hien mat ket noi sau ~22 s -> gui LWT
    _mqttClient.setSocketTimeout(4);    // Khong treo loop() lau khi broker khong phan hoi

    connectWiFi();
    connectMqtt();
}

void MqttService::connectWiFi() {
    Serial.printf("[WIFI] Connecting to %s", _ssid);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.begin(_ssid, _pass);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
        delay(250);
        Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("\n[WIFI] Connected. IP: %s\n", WiFi.localIP().toString().c_str());
    } else {
        Serial.println("\n[WIFI] Timeout. Gate keeps working offline, retrying in background.");
    }
}

void MqttService::connectMqtt() {
    if (WiFi.status() != WL_CONNECTED || _mqttClient.connected()) return;

    unsigned long now = millis();
    if (_lastReconnectAttempt != 0 && now - _lastReconnectAttempt < MQTT_RETRY_MS) return;
    _lastReconnectAttempt = now;

    Serial.printf("[MQTT] Connecting to %s:%d ...\n", _broker, _port);
    // Last Will: broker tu dong bao offline (retained) neu ESP32 mat ket noi dot ngot
    if (_mqttClient.connect(_clientId.c_str(), MQTT_TOPIC_STATUS, 1, true, LWT_OFFLINE)) {
        Serial.println("[MQTT] Connected.");
        _mqttClient.subscribe(MQTT_TOPIC_CMD);
        if (_connectCallback) _connectCallback();
    } else {
        Serial.printf("[MQTT] Failed (rc=%d). Retry in %lus.\n", _mqttClient.state(), MQTT_RETRY_MS / 1000);
    }
}

void MqttService::update() {
    if (WiFi.status() != WL_CONNECTED) return;
    if (_mqttClient.connected()) _mqttClient.loop();
    else connectMqtt();
}

bool MqttService::isConnected() {
    return _mqttClient.connected();
}

void MqttService::publishJson(const char* topic, JsonDocument& doc, bool retained) {
    if (!_mqttClient.connected()) return;
    char buf[640];
    size_t n = serializeJson(doc, buf, sizeof(buf));
    _mqttClient.publish(topic, (const uint8_t*)buf, n, retained);
}
