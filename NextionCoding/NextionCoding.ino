float temp, hum;
uint8_t pool_size1;
uint8_t count = 0;
unsigned long currentmillis = 0;
unsigned long previousMillis = 0;
unsigned long interval = 0;

unsigned long tcurrentmillis = 0;
unsigned long tpreviousMillis = 0;
unsigned long tinterval = 15e5;

void MD02setup();
void MD02Read();
void bt2PushCallback(void *ptr);
void bt3PushCallback(void *ptr);
void bt4PushCallback(void *ptr);
void bt5PushCallback(void *ptr);
void initWiFi();
void sendData2GGSheet();
void NexSetup();
void NexRead();

#define wifiLed 2  //D2

#include "MD02.h"
#include "Nextion.h"
#include "WifiConnect.h"
#include "GoogleSheet.h"

TaskHandle_t Task1;

void setup() {

  Serial.begin(9600);
  MD02setup();
  NexSetup();
  initWiFi();
  Serial.print("setup() running on core ");
  Serial.println(xPortGetCoreID());

  xTaskCreatePinnedToCore(
    Task1code, /* Function to implement the task */
    "Task1",   /* Name of the task */
    10000,     /* Stack size in words */
    NULL,      /* Task input parameter */
    0,         /* Priority of the task */
    &Task1,    /* Task handle. */
    0);        /* Core where the task should run */
}

void Task1code(void *parameter) {
  for (;;) {
    tcurrentmillis = millis();
    if (tcurrentmillis - tpreviousMillis >= tinterval) {
      sendData2GGSheet();
      tpreviousMillis = tcurrentmillis;
    }
  }
}

void loop() {
  currentmillis = millis();
  nexLoop(nex_listen_list);
  if (currentmillis - previousMillis >= interval) {
    reconcectWifi();
    MD02Read();
    previousMillis = currentmillis;
    interval = 60e3;
  }
}
