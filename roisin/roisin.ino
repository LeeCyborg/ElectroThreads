int forwardLength = 9000;                 // set in miliseconds, 5000 = 5 seconds
int backwardLength = 9000;
bool currStatus;                           //variable to hold previous switch state           

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
  
  
    currStatus = digitalRead(6);            //read switch initial state
  Serial.println("currStatus: "+currStatus);            
}

void loop() {
  if (currStatus != digitalRead(6)) {        //if switch state has changed from stored value
    
      Serial.println("switch changed");
      
      if (currStatus == true) {              //if previous state = open - unspool motor
       Serial.println("unspooling");
        digitalWrite(0, HIGH);
        digitalWrite(1, LOW);
        delay(forwardLength);
        digitalWrite(0, LOW);
      }
        else if (currStatus == false) {     //if previous state = closed - unspool motor
          Serial.println("spooling");
          digitalWrite(1, HIGH);
          digitalWrite(0, LOW);
          delay(backwardLength);
          digitalWrite(1, LOW);
        }
    currStatus = digitalRead(6);            //set state to updated switch state
    
    
    }
    //Serial.println(digitalRead(6));
}
