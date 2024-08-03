void loop() {
  if (activateChangeMode) {
    changeMode();
    activateChangeMode = false;
  }
  if (changeLEDColor) {
    setBMIColor(pixel_0_color, pixel_1_color, pixel_2_color, 20);
    changeLEDColor = false;
  }
}





void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  setHEXID();
  getDefaultSSID();

  //verify littlefs partition is available and formatted
  if (!SPIFFS.begin(FORMAT_LITTLEFS_IF_FAILED)) {
    Serial.println("LittleFS Mount Failed");
    return;
  }



  //attempt to open bmi namespace for preferences
  boolean opened = preferences.begin("bmi", false);
  if (opened) {
    Serial.println("opened preferences namespace");
    Serial.println(preferences.getString("ssid"));
  } else {
    Serial.println("Could not open preferences namespace");
  }


  getPrefs();


  //check for setup mode

  if (digitalRead(BUTTON_PIN) == LOW) {
    setupMode = true;
    bmi_host_name_var = defaultHostName;
    Serial.println("Entering Setup Mode");
    Serial.print("Default SSID: ");
    Serial.println(bmi_host_name_var);
  }



  WiFiEventId_t ConEventID = WiFi.onEvent(
    [](WiFiEvent_t event, WiFiEventInfo_t info) {
      mode = 6;
      activateChangeMode = true;
    },
    WiFiEvent_t::ARDUINO_EVENT_WIFI_AP_STACONNECTED);

  WiFiEventId_t DisConEventID = WiFi.onEvent(
    [](WiFiEvent_t event, WiFiEventInfo_t info) {
      mode = 2;
      activateChangeMode = true;
    },
    WiFiEvent_t::ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);

  delay(250);

  if (setupMode == true) {
    WiFi.softAP(bmi_host_name_var.c_str());
  } else {
    WiFi.softAP(bmi_host_name_var.c_str(), bmi_pass_value.c_str());
  }
  delay(250);
  WiFi.softAPConfig(local_ip, gateway, subnet);



  //multicast dns allows to pull up webpage by going to http://bmi.local/
  if (MDNS.begin("bmi")) {
    Serial.println("MDNS responder started");
  } else {
  }

  //add Async callbacks
  setupServerOns();

  //start async server
  server.begin();

  //start adafruit neopixel
  strip.begin();
  strip.show();


  //start asyncbutton event for long presses
  b1.begin();
  b1.onLongPress(on_LongPress);
  b1.enable();
}