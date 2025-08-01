#ifndef OTA_H
#define OTA_H

#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncTCP.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#include <AsyncTCP.h>
#endif

#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <WebSerial.h>
#include <ESPAsyncWebServer.h>

extern AsyncWebServer server;


void connectWifi(const char* ssid, const char* password);
void setupOTA(int port = -1, const char* hostname = nullptr, const char* password = nullptr);
void setupWebSerial(const char* hostname = nullptr);
void handleOTA();


#endif // OTA_H