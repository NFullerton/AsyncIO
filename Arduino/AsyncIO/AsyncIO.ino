// ASyncIO by Nicholas Fullerton on 1/10/2019
// Demo code to work with ASyncIO LabVIEW example. 

// Watchdog timer for soft-reset:
#include <avr/wdt.h>

// Pins:
const int grnOutPin = 3; const int grnInPin = 2;
const int bluOutPin = 5; const int bluInPin = 4;
const int vinPin = A0;

// Empty variables for serial input:
String received = "";
int value;

// Resets the Microcontroller after 15 ms:
void softReset() {
  wdt_enable(WDTO_15MS);
  delay(15);
}

// Scales 0-1023 counts to 0-5 Volts:
double getVoltage(int counts) {
  return counts * (5.0/1023.0);
}
// Converts pin reads into data string:
String readData(int grnOn, int bluOn, int vin) {
  return 
    ">" + String(digitalRead(grnOn)) + ":" + 
    String(digitalRead(bluOn)) + ":" + 
    String(getVoltage(analogRead(vin))); 
}

void setup() {
  pinMode(grnOutPin, OUTPUT); pinMode(grnInPin, INPUT);
  pinMode(bluOutPin, OUTPUT); pinMode(bluInPin, INPUT);
  pinMode(vinPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  if(Serial.available()) {
    received = Serial.readString();
    value = received.toInt();
    if(value == 3) { softReset(); }
    else if(value == -1) { digitalWrite(grnOutPin, HIGH); }
    else if(value == -2) { digitalWrite(grnOutPin, LOW); }
    else if(value == 1) { digitalWrite(bluOutPin, HIGH); }
    else if(value == 2) { digitalWrite(bluOutPin, LOW); }      
  }
  
  Serial.println(readData(grnOutPin, bluOutPin, vinPin));
  delay(100);
}



