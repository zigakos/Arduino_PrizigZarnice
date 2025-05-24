const int b1Pin = 2;     
const int b2Pin = 3;    
const int b3Pin = 4;     
const int b4Pin = 5;     
const int led1Pin = 8;   
const int led2Pin = 9;   
bool b1State = false;
bool b2State = false;
bool b3State = false;
bool b4State = false;
bool b1PrevState = false;
bool b2PrevState = false;
bool b3PrevState = false;
bool b4PrevState = false;


bool led1On = false;
bool led2On = false;


unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; 

void setup() {

  pinMode(b1Pin, INPUT_PULLUP);
  pinMode(b2Pin, INPUT_PULLUP);
  pinMode(b3Pin, INPUT_PULLUP);
  pinMode(b4Pin, INPUT_PULLUP);

  
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);

  
  digitalWrite(led1Pin, LOW);
  digitalWrite(led2Pin, LOW);
  
  
  Serial.begin(9600);
  Serial.println("LED Control System Started");
}

void loop() {
 
  bool currentB1 = !digitalRead(b1Pin);
  bool currentB2 = !digitalRead(b2Pin);
  bool currentB3 = !digitalRead(b3Pin);
  bool currentB4 = !digitalRead(b4Pin);

  
  if (currentB1 != b1PrevState || currentB2 != b2PrevState || 
      currentB3 != b3PrevState || currentB4 != b4PrevState) {
   
    lastDebounceTime = millis();
  }

 
  if ((millis() - lastDebounceTime) > debounceDelay) {
    
    if (currentB1 != b1State) {
      b1State = currentB1;
      if (b1State) {
       
        if (!led1On && !led2On) {
       
          led1On = true;
          updateLEDs();
          Serial.println("LED 1 turned ON");
        }
      }
    }
    
    if (currentB2 != b2State) {
      b2State = currentB2;
      if (b2State) {
        if (!led1On && !led2On) {
          led2On = true;
          updateLEDs();
          Serial.println("LED 2 turned ON");
        }
      }
    }

    if (currentB3 != b3State) {
      b3State = currentB3;
      if (b3State) {
 
        if (led1On || led2On) {
          led1On = false;
          led2On = false;
          updateLEDs();
          Serial.println("All LEDs turned OFF");
        }
      }
    }

    if (currentB4 != b4State) {
      b4State = currentB4;
      if (b4State) {
        if (led1On && !led2On) {
          led1On = false;
          led2On = true;
          updateLEDs();
          Serial.println("Swapped: LED 1 OFF, LED 2 ON");
        } else if (!led1On && led2On) {
          led1On = true;
          led2On = false;
          updateLEDs();
          Serial.println("Swapped: LED 1 ON, LED 2 OFF");
        }
      }
    }
  }

  b1PrevState = currentB1;
  b2PrevState = currentB2;
  b3PrevState = currentB3;
  b4PrevState = currentB4;
}

void updateLEDs() {
  digitalWrite(led1Pin, led1On ? HIGH : LOW);
  digitalWrite(led2Pin, led2On ? HIGH : LOW);
}