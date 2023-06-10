float temp, hum;

#include "Nextion.h"
#include "MD02.h"


unsigned long currentmillis;
unsigned long previousMillis = 0;
unsigned long interval = 5000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MD02setup();
  NexSetup();
  
}

void loop() {
  currentmillis = millis();
  if (currentmillis - previousMillis >= interval) {
    MD02Read();
    previousMillis = currentmillis;
  }
}
