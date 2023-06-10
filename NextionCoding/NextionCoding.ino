float temp, hum;

#include "Nextion.h"
#include "MD02.h"


unsigned long currentmillis;
unsigned long previousMillis = 0;
unsigned long interval = 1000;

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
  //nexLoop(nex_listen_list);
}
