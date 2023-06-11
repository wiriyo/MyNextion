float temp, hum;
void bt2PushCallback(void *ptr);
void bt3PushCallback(void *ptr);
void bt4PushCallback(void *ptr);
void bt5PushCallback(void *ptr);
uint8_t pool_size1;

#include "Nextion.h"
#include "MD02.h"


unsigned long currentmillis=0;
unsigned long previousMillis = 0;
unsigned long interval = 0;


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
    interval = 30000;
  }
  nexLoop(nex_listen_list);
}
