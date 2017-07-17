int forwardLength = 5000; // set in miliseconds, 5000 = 5 seconds
int backwardLength = 5000;
bool currStatus = false;
void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (currStatus != digitalRead(6)) {
    Serial.println("change");
    if (currStatus == true) {
      digitalWrite(0, HIGH);
      digitalWrite(1, LOW);
      delay(forwardLength);
      digitalWrite(0, LOW);
    }
      else if (currStatus == false) {
        digitalWrite(1, HIGH);
        digitalWrite(0, LOW);
        delay(backwardLength);
        digitalWrite(1, LOW);
      }
      currStatus = digitalRead(6);
    }
    //Serial.println(digitalRead(6));
  }
