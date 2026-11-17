#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <functional>
#include "Config.h"

typedef std::function<void(const String& cmd)> CommandCallback;

class MqttService {
public:
    MqttService(const char* ssid, const char* pass, const char* broker, int port);

    void begin(CommandCallback onCommand);
    void update();

    bool isConnected();
    void publishScan(const String& uid, const String& action, const String& plate,
                     const String& owner, unsigned long durationSec, uint32_t fee,
                     int occupied, int capacity);
    void publishAlert(const String& type, const String& uid);
    void publishGateState(bool isOpen);

private:
    const char* _ssid;
    const char* _pass;
    const char* _broker;
    int _port;

    WiFiClient _wifiClient;
    PubSubClient _mqttClient;
    CommandCallback _commandCallback;
    String _clientId;
    unsigned long _lastReconnectAttempt;

    void connectWiFi();
    void connectMqtt();
    static void onMqttMessage(char* topic, byte* payload, unsigned int length);
};
