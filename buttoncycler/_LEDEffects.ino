
void on_LongPress() {
  b1.onPress(nullptr);
  b1.onRelease(nullptr);
  changeMode();
}



void changeMode() {

  if (++mode > 4) mode = 0;  // Advance to next mode, wrap around after last
  switch (mode) {            // Start the new animation...
    case 0:
      bootSequence();
      break;
    case 1:
      uploadSequence();
      break;
    case 2:
      redSequence();
      break;
    case 3:
      powerDownSequence();
      break;
    case 4:
      strip.clear();
      strip.show();
      break;
  }
}



void setBMIColor(uint32_t pixel_0_color, uint32_t pixel_1_color, uint32_t pixel_2_color, int wait) {
  strip.setPixelColor(0, pixel_0_color);
  strip.setPixelColor(1, pixel_1_color);
  strip.setPixelColor(2, pixel_2_color);
  strip.setBrightness(brightness);
  strip.show();
  delay(wait);
  return;
}

void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) {  // For each pixel in strip...
    strip.setPixelColor(i, color);               //  Set pixel's color (in RAM)
    strip.show();                                //  Update strip to match
    strip.setBrightness(brightness);
    delay(wait);  //  Pause for a moment
  }
  return;
}

void powerDownSequence() {
  int randomRed = 255;  //random(0, 255);
  int randomGreen = random(0, 255);
  int randomBlue = random(0, 255);
  for (int i = 0; i < 3; i++) {

    uint32_t randomColor = strip.Color(randomRed, randomGreen, randomBlue);
    strip.setPixelColor(i, randomColor);
    strip.setBrightness(brightness);
    strip.show();
    delay(25);
  }

  colorFadePixel(0, 0, 0, 10, 0);
  colorFadePixel(0, 0, 0, 10, 1);
  colorFadePixel(0, 0, 0, 10, 2);
}

void redSequence() {
  int wait = 30;
  setBMIColor(WHITE, WHITE, WHITE, wait);

  //fade to yellow
  colorFadePixel(255, 255, 0, 5, 0);
  colorFadePixel(255, 255, 0, 5, 1);
  colorFadePixel(255, 255, 0, 5, 2);

  //fade to Red
  colorFadePixel(255, 0, 0, 5, 0);
  colorFadePixel(255, 0, 0, 5, 1);
  colorFadePixel(255, 0, 0, 5, 2);
  //blink RED, fade brightness
  setBMIColor(RED, RED, RED, wait);
  setBMIColor(BLANK, BLANK, BLANK, 150);
  setBMIColor(RED, RED, RED, wait);
  setBMIColor(BLANK, BLANK, BLANK, 150);
  fadeBrightness(50, 100, 255, 0, 0, wait, 5);
  strip.setBrightness(brightness);
  return;
}

void uploadSequence() {
  int wait = 30;
  strip.clear();
  for (int a = 0; a < 5; a++) {
    setBMIColor(GREEN, GREEN, GREEN, wait);
    setBMIColor(BLANK, GREEN, GREEN, wait);
    setBMIColor(GREEN, BLANK, GREEN, wait);
    setBMIColor(GREEN, GREEN, BLANK, wait);
  }
  setBMIColor(GREEN, GREEN, GREEN, wait);
  colorFadePixel(255, 255, 255, 5, 0);
  colorFadePixel(255, 255, 255, 5, 1);
  colorFadePixel(255, 255, 255, 5, 2);
}




void bootSequence() {
  strip.clear();
  int wait = 30;
  for (int a = 0; a < 5; a++) {
    setBMIColor(WHITE, BLANK, BLANK, wait);
    setBMIColor(BLANK, WHITE, BLANK, wait);
    setBMIColor(BLANK, BLANK, WHITE, wait);
    setBMIColor(BLANK, WHITE, BLANK, wait);
  }

  setBMIColor(WHITE, BLANK, BLANK, wait);
  fadePixelBrightness(10, 10, 0, 255, 0, 5, 2, 0);
  setBMIColor(GREEN, BLANK, BLANK, 10);
  fadePixelBrightness(10, 10, 0, 255, 0, 5, 2, 1);
  setBMIColor(GREEN, GREEN, BLANK, 10);
  fadePixelBrightness(10, 10, 0, 255, 0, 5, 2, 2);
  setBMIColor(GREEN, BLANK, GREEN, 10);
  fadeBrightness(10, 10, 255, 255, 255, 50, 1);
  setBMIColor(WHITE, WHITE, WHITE, 10);
  return;
}

void colorFadePixel(uint8_t r, uint8_t g, uint8_t b, uint8_t wait, int pixel) {
  //fade between current color and another
  uint8_t startR, startG, startB;
  uint32_t startColor = strip.getPixelColor(pixel);  // get the current colour
  startB = startColor & 0xFF;
  startG = (startColor >> 8) & 0xFF;
  startR = (startColor >> 16) & 0xFF;  // separate into RGB components

  while ((startR != r) || (startG != g) || (startB != b)) {  // while the curr color is not yet the target color
    if (startR < r) startR++;
    else if (startR > r) startR--;  // increment or decrement the old color values
    if (startG < g) startG++;
    else if (startG > g) startG--;
    if (startB < b) startB++;
    else if (startB > b) startB--;
    strip.setPixelColor(pixel, startR, startG, startB);  // set the color
    strip.setBrightness(brightness);
    strip.show();
    delay(wait);
  }
}

void fadePixelBrightness(int steps, int maxBrightness, int red, int green, int blue, int wait, int loops, int pixel) {
  //fade an indidiual pixels brightness
  strip.setBrightness(maxBrightness);

  for (int h = 0; h < loops; h++) {
    //strip.clear();
    for (int a = 0; a < steps; a++) {
      float fadeStep = float(a) / float(steps);
      int redFade = red * fadeStep;
      int greenFade = green * fadeStep;
      int blueFade = blue * fadeStep;

      strip.setPixelColor(pixel, strip.Color(redFade, greenFade, blueFade));
      strip.setBrightness(brightness);
      strip.show();
      delay(wait);
    }
    for (int a = steps; a > 0; a--) {
      float fadeStep = float(a) / float(steps);
      int redFade = red * fadeStep;
      int greenFade = green * fadeStep;
      int blueFade = blue * fadeStep;


      for (int x = 0; x < 3; x++) {
        strip.setPixelColor(x, strip.Color(redFade, greenFade, blueFade));
      }
      strip.setBrightness(maxBrightness);
      strip.show();
      delay(wait);
    }
  }
  return;
}


void fadeBrightness(int steps, int maxBrightness, int red, int green, int blue, int wait, int loops) {
  //Fades brightness for full strip
  strip.setBrightness(maxBrightness);

  for (int h = 0; h < loops; h++) {

    strip.clear();
    for (int a = 0; a < steps; a++) {
      float fadeStep = float(a) / float(steps);
      int redFade = red * fadeStep;
      int greenFade = green * fadeStep;
      int blueFade = blue * fadeStep;

      for (int x = 0; x < 3; x++) {
        strip.setPixelColor(x, strip.Color(redFade, greenFade, blueFade));
      }
      strip.show();
      delay(wait);
    }
    for (int a = steps; a > 0; a--) {
      float fadeStep = float(a) / float(steps);
      int redFade = red * fadeStep;
      int greenFade = green * fadeStep;
      int blueFade = blue * fadeStep;


      for (int x = 0; x < 3; x++) {
        strip.setPixelColor(x, strip.Color(redFade, greenFade, blueFade));
      }
      strip.setBrightness(maxBrightness);
      strip.show();
      delay(wait);
    }
  }

  if (digitalRead(BUTTON_PIN) == LOW) {
    return;
  }
}

uint32_t hextToIntColor(String hexstring) {

  int number = (int)strtol(&hexstring[1], NULL, 16);
  // Split them up into r, g, b values
  int r = number >> 16;
  int g = number >> 8 & 0xFF;
  int b = number & 0xFF;

  return strip.Color(r, g, b);
}
