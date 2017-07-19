#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// This isn't what she wants really, just a test.
#define PIN 5
#define NUMPIXELS 60
int fadeRate = 0;
int MaxBrightness = 255;
int TotalSteps = 15;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
// this constant won't change:
const int  buttonPin = 6;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button


int whiteStart = 0;
int whiteEnd = NUMPIXELS / 6;

int blackStart = NUMPIXELS / 6 * 5;
int blackEnd = NUMPIXELS;
bool justChanged = false;

int del = 0;

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
  Serial.println(buttonPushCounter);
  // compare the buttonState to its previous state

  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      justChanged = true;
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;


  if (buttonPushCounter == 0) {
    if (justChanged) colorWipe(strip.Color(0, 0, 0), 50); // Off

  } else if (buttonPushCounter == 1) {
    if (justChanged) colorWipe(strip.Color(255, 255, 255), 50); // Everything bright (particular ones for use for optics will be chosen later)

  } else if (buttonPushCounter == 2) {
    flow(10); //the problem with the button is here - if the button is pressed while the delay inside this function is being run then nothing happens.
    //ideally we should use a hardware interrupt
    //but for now we'll do waits of 5ms, and only actually do the flow every tenth time.
  }
  else if (buttonPushCounter == 3) {
    if (justChanged) {
        colorWipe(strip.Color(0,0,0), 0);
        delay(3000);
        setSection(0, 60, 255, 255, 255);
    }
  }
  if (buttonPushCounter == 4) {
    buttonPushCounter = 0;
    colorWipe(strip.Color(0, 0, 0), 50); // Off
  }

  justChanged = false;
}


/*void simpleWave(float rate, int cycles, int wait) {
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
  }*/

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void flow(uint8_t wait) {
  del++;

  if (del == 10) {
    del = 0;

    for (int i = 0; i < strip.numPixels(); i++) {

      uint8_t col = 0;

      if (whiteStart > whiteEnd) {
        //white LEDs have looped around
        if (i >= whiteStart || i < whiteEnd) col += 1;
      }
      else {
        if (i >= whiteStart && i < whiteEnd) col += 1;
      }

      if (blackStart > blackEnd) {
        //black LEDs have looped around
        if (i >= blackStart || i < blackEnd) col += 2;
      }
      else {
        if (i >= blackStart && i < blackEnd) col += 2;
      }

      if (col == 1) strip.setPixelColor(i, strip.Color(255, 255, 255)); //white pixel
      if (col == 2) strip.setPixelColor(i, strip.Color( 70,  70,  70)); //black pixel
      if (col == 3) strip.setPixelColor(i, strip.Color( 90,  90,  90)); //grey  pixel
    }


    strip.show(); // This sends the updated pixel color to the hardware.


    whiteStart++;
    whiteEnd++;

    blackStart--;
    blackEnd--;

    //loop around
    if (whiteEnd > NUMPIXELS) {
      whiteEnd = 0;
    }

    if (whiteStart == NUMPIXELS) {
      whiteStart = 0;
    }

    if (blackStart == 0) {
      blackStart = NUMPIXELS - 1;
    }

    if (blackEnd == 0) {
      blackEnd = NUMPIXELS;
    }
  }
  delay(wait); // Delay for a period of time (in milliseconds).
}
void setSection(int start, int finish, int Nred, int Ngreen, int Nblue) {
  uint32_t c = strip.getPixelColor(start);
  uint8_t  redCur = (c >> 16) & 0xFF;
  uint8_t  greenCur = (c >>  8) & 0xFF;
  uint8_t  blueCur = c & 0xFF;
  uint8_t redNew = Nred;
  uint8_t greenNew = Ngreen;
  uint8_t blueNew = Nblue;
  for (int i = 1; i < TotalSteps; i++)
  {
    uint8_t red = (((redCur * (TotalSteps - i)) + (redNew * i)) / TotalSteps);
    uint8_t green = (((greenCur * (TotalSteps - i)) + (greenNew * i)) / TotalSteps);
    uint8_t blue = (((blueCur * (TotalSteps - i)) + (blueNew * i)) / TotalSteps);
    for (int j = start; j < finish + 1; j++) {
      strip.setPixelColor(j, red, green, blue);
      strip.show();
      delay(fadeRate);
    }
  }
}



