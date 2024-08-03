#ifdef ESP32
#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

#include <ESPAsyncWebServer.h>  //ESPAsyncWebServer 3.1.0
#include <Adafruit_NeoPixel.h> //Adafruit NeoPixel 1.12.3
#include <LittleFS.h>
#include <DNSServer.h>
#include <Preferences.h>
#include <espasyncbutton.hpp>  //ESPAsyncButton 1.2.1

//split for consistancy sake