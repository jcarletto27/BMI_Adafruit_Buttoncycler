

void setHEXID() {
#ifdef ESP32
  for (int i = 0; i < 17; i = i + 8) {
    chipID |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
  }
#elif defined(ESP8266)
  chipID = ESP.getChipId();
#endif
  hexID = String(chipID, HEX);

  Serial.println(chipID);
  Serial.println(hexID);
}
float getBatteryVoltagePercent() {
  float voltPercent = 1.00;

  float currentVolt = readVoltage();
  if (currentVolt > 0.01) {
    if (currentVolt > maxVoltage) {
      maxVoltage = currentVolt;

      preferences.putFloat("max_voltage", maxVoltage);
    }
    voltPercent = currentVolt / maxVoltage;
  }

  return voltPercent;
}


float readVoltage() {
  uint32_t Vbatt = 0;
  for (int i = 0; i < 16; i++) {
    Vbatt = Vbatt + analogReadMilliVolts(VOLTAGE_QUERY_PIN);  // ADC with correction
  }
  float Vbattf = 2 * Vbatt / 16 / 1000.0;  // attenuation ratio 1/2, mV --> V
  Serial.println(Vbattf, 3);

  return Vbattf;
}



float getUsedSpacePercent() {
  float totalPerc = (float)getUsedSpaceBytes() / (float)getTotalSpaceBytes();

  if (totalPerc > 1) {
    totalPerc = 1;
  }
  return totalPerc;
}
uint32_t getUsedSpaceBytes() {
  return (uint32_t)LittleFS.usedBytes();
}


uint32_t getTotalSpaceBytes() {
  return (uint32_t)LittleFS.totalBytes();
}

String getDefaultSSID() {
  defaultHostName = "UNBOUND_BMI_0X-5501-" + hexID;
  return defaultHostName;
}

void getPrefs() {
  pixel_0_color = preferences.getUInt("pixel_0_color", WHITE);
  pixel_1_color = preferences.getUInt("pixel_1_color", WHITE);
  pixel_2_color = preferences.getUInt("pixel_2_color", WHITE);
  bmi_host_name_var = preferences.getString("ssid", defaultHostName);
  bmi_pass_value = preferences.getString("pass", "");
  setupMode = preferences.getBool("setup_mode", false);
  maxVoltage = preferences.getFloat("max_voltage", (float)2.70);
}



void setupServerOns() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(LittleFS, "/main.html", "text/html", false, processor);
  });

  server.on("/HARDRESET", HTTP_GET, [](AsyncWebServerRequest* request) {
    preferences.clear();
    preferences.end();
    ESP.restart();
    request->redirect("/");
  });

  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(LittleFS, "/main.js", "text/js", false);
  });


  server.on("/jquery.js", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(LittleFS, "/jquery.js", "text/js", false);
  });

  server.on("/main.css", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(LittleFS, "/main.css", "text/css", false);
  });


  // Handle POST requests to /submit
  server.on("/submit", HTTP_GET, [](AsyncWebServerRequest* request) {
    Serial.println("Submitted");


    if (request->hasParam(ENUM_BMI_HOST_NAME)) {
      String tempVal = request->getParam(ENUM_BMI_HOST_NAME)->value();
      Serial.println(tempVal);
      preferences.putString("ssid", tempVal);
    }

    if (request->hasParam(ENUM_BMI_HOST_PASSWORD)) {
      String tempVal = request->getParam(ENUM_BMI_HOST_PASSWORD)->value();
      Serial.println(tempVal);
      preferences.putString("pass", tempVal);
      //scheduleReboot = true;
    }

    if (request->hasParam(ENUM_BRIGHTNESS_RANGE)) {
      String tempVal = request->getParam(ENUM_BRIGHTNESS_RANGE)->value();
      Serial.println(tempVal);
      int range = tempVal.toInt();
      preferences.putInt("brightness", range);
    }

    if (request->hasParam(ENUM_MODE_SELECTION)) {
      Serial.println("Found Change Mode parameter");
      String tempVal = request->getParam(ENUM_MODE_SELECTION)->value();
      Serial.println(tempVal);
      mode = tempVal.toInt();
      activateChangeMode = true;
    }

    if (request->hasParam(ENUM_PIXEL_0)) {
      String tempVal = request->getParam(ENUM_PIXEL_0)->value();
      Serial.println(tempVal);
      pixel_0_color = hextToIntColor(tempVal);
      preferences.putUInt("pixel_0_color", pixel_0_color);
      changeLEDColor = true;
    }

    if (request->hasParam(ENUM_PIXEL_1)) {
      String tempVal = request->getParam(ENUM_PIXEL_1)->value();
      Serial.println(tempVal);
      pixel_1_color = hextToIntColor(tempVal);
      preferences.putUInt("pixel_1_color", pixel_1_color);
      changeLEDColor = true;
    }

    if (request->hasParam(ENUM_PIXEL_2)) {
      String tempVal = request->getParam(ENUM_PIXEL_2)->value();
      Serial.println(tempVal);
      pixel_2_color = hextToIntColor(tempVal);
      preferences.putUInt("pixel_2_color", pixel_2_color);
      changeLEDColor = true;
    }
    request->redirect("http://bmi.local/");
  });
}

String processor(const String& var) {
  String retVal = "";

  if (var == "usedSpaceBytes")
    retVal = String(getUsedSpaceBytes());

  if (var == "totalSpaceBytes")
    retVal = String(getTotalSpaceBytes());

  if (var == "usedSpacePercent")
    retVal = String(getUsedSpacePercent());

  if (var == "batteryVoltagePercent")
    retVal = String(getBatteryVoltagePercent());

  if (var == "batteryVoltage")
    retVal = String(readVoltage());

  if (var == "SERIAL")
    retVal = hexID;

  if (var == "bmi_host_name")
    retVal = bmi_host_name_var;

  return retVal;
}
