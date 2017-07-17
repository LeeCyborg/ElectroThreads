#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// This isn't what she wants really, just a test.
#define PIN 12
Adafruit_NeoPixel strip = Adafruit_NeoPixel(160, PIN, NEO_GRB + NEO_KHZ800);
// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button
      // wend from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;


  if (buttonPushCounter == 0) {
    simpleWave(0.1, 5, 10);
  } else if (buttonPushCounter == 1) {
    colorWipe(strip.Color(255, 0, 0), 50); // Red

  } else if (buttonPushCounter == 2) {
    colorWipe(strip.Color(255, 255, 0), 50); // Red

  }
  else if (buttonPushCounter == 3) {
    colorWipe(strip.Color(0, 0, 255), 50); // Red

  }
  if (buttonPushCounter == 4) {

    buttonPushCounter = 0;
  }
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
      strip.setPixelColor(i, 0, (int)level, (int)level / 15);
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
