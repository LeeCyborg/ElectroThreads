int speedVal = 30; //change to alter speed
int ledPin = 5;    // MF board pin 5

void setup() {
}

void loop() {
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    analogWrite(ledPin, fadeValue);
    delay(speedVal);
  }
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    analogWrite(ledPin, fadeValue);
    delay(speedVal);
  }
}


