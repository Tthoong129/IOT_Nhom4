#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <functional>
#include "Config.h"

typedef std::function<void(const String& cmd, const String& src)> CommandCallback;
typedef std::function<void(const JsonDocument& doc)> ConfigCallback;
typedef std::function<void()> ConnectCallback;

class MqttService {
public:
    MqttService(const char* ssid, const char* pass, const char* broker, int port);

    void begin(CommandCallback onCommand, ConfigCallback onConfig, ConnectCallback onConnect);
    void update();
    bool isConnected();

    void publishJson(const char* topic, JsonDocument& doc, bool retained = false);

private:
    const char* _ssid;
    const char* _pass;
    const char* _broker;
    int _port;

    WiFiClient   _wifiClient;
    PubSubClient _mqttClient;
    CommandCallback _commandCallback;
    ConfigCallback  _configCallback;
    ConnectCallback _connectCallback;
    String _clientId;
    unsigned long _lastReconnectAttempt;

    void connectWiFi();
    void connectMqtt();
    static void onMqttMessage(char* topic, byte* payload, unsigned int length);
};
