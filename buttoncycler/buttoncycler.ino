#ifdef ESP32
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>
#include <Adafruit_NeoPixel.h>
#include <LittleFS.h>
#include <DNSServer.h>
#include <Preferences.h>
#include <espasyncbutton.hpp>

//split for consistancy sake