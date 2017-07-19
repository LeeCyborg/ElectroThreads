#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// This isn't what she wants really, just a test.
#define PIN 10
Adafruit_NeoPixel strip = Adafruit_NeoPixel(160, PIN, NEO_GRB + NEO_KHZ800);
void setup() {

  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
simpleWave(1, 10, 20);
}


void simpleWave(float rate, int cycles, int wait) {
  float pos = 0.0;
  // cycle through x times
  for (int x = 0; x < (strip.numPixels()*cycles); x++)
  {
    pos = pos + rate;
    for (int i = 0; i < strip.numPixels(); i++) {
      // sine wave, 3 offset waves make a rainbow!
      float level = sin(i + pos) * 127 + 128;
      // set color level
      strip.setPixelColor(i, (int)level/(i*-1), 0, (int)level / i+10);
    }
    strip.show();
    delay(wait);
  }
}  void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
