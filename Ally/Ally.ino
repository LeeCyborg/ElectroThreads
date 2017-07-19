int speedVal = 90; //change to alter speed
int ledPin = 5;    // MF board pin 5

void setup() {
  pinMode(ledPin, OUTPUT);
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


