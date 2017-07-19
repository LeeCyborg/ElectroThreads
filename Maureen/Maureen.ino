#include <Adafruit_NeoPixel.h>
const int sensorPin = 0;    // pin that the sensor is attached to
// variables:
int PIN = 12;
int Pixels = 60;
#define BG 1
uint32_t currentBg = random(256);
uint32_t nextBg = currentBg;
int step = -1;
int center = 0;
int color;
int maxSteps = 16;
float fadeRate = 0.6;
int diff;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(Pixels, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'\ while (millis() < 5000) 
}

void loop() {
  //Serial.println(sensorValue);
  Serial.println(analogRead(0));
  if(analogRead(0) < 165) { 
    ripple();
    
  } else {
    colorWipe(strip.Color(250, 0, 0), 0); // loose  
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}


void ripple() {

      nextBg = 0;

    for(uint16_t l = 0; l < Pixels; l++) {
      strip.setPixelColor(l, Wheel(80, 1));
    }
  if (step == -1) {
    center = random(Pixels);
    color = 80;
    step = 0;
  }
  if (step == 0) {
    strip.setPixelColor(center, Wheel(color, 1));
    step ++;
  }
  else {
    if (step < maxSteps) {
      strip.setPixelColor(wrap(center + step), Wheel(color, pow(fadeRate, step)));
      strip.setPixelColor(wrap(center - step), Wheel(color, pow(fadeRate, step)));
      if (step > 3) {
        strip.setPixelColor(wrap(center + step - 3), Wheel(color, pow(fadeRate, step - 2)));
        strip.setPixelColor(wrap(center - step + 3), Wheel(color, pow(fadeRate, step - 2)));
      }
      step ++;
    }
    else {
      step = -1;
    }
  }
  
  strip.show();
  delay(50);
}


int wrap(int step) {
  if(step < 0) return Pixels + step;
  if(step > Pixels - 1) return step - Pixels;
  return step;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos, float opacity) {
  
  if(WheelPos < 85) {
    return strip.Color((WheelPos * 3) * opacity, (255 - WheelPos * 3) * opacity, 0);
  }
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color((255 - WheelPos * 3) * opacity, 0, (WheelPos * 3) * opacity);
  }
  else {
    WheelPos -= 170;
    return strip.Color(0, (WheelPos * 3) * opacity, (255 - WheelPos * 3) * opacity);
  }
}
