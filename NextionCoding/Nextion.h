#include <Nextion.h>

SoftwareSerial HMISerial(35, 32);  // RX,TX
ModbusMaster node1;

//==========Define IO connect to relay==========//
#define sw1 25
#define sw2 26

NexVariable vaTemp = NexVariable(4, 8, "vatemp");
NexVariable vaHum = NexVariable(4, 10, "vahum");
NexVariable vvalTemp = NexVariable(4, 11, "vvaltemp");
NexVariable vvalHum = NexVariable(4, 12, "vvalhum");
NexVariable vzTemp = NexVariable(4, 13, "vztemp");
NexVariable vzHum = NexVariable(4, 14, "vzhum");

//Page id 3 DualState Button
NexButton bt0 = NexButton(3, 2, "bt0");
NexButton bt1 = NexButton(3, 3, "bt1");

//Page id 8 Modbus Relay
NexButton bt2 = NexButton(7, 2, "bt2");
NexButton bt3 = NexButton(7, 3, "bt3");
NexButton bt4 = NexButton(7, 4, "bt4");
NexButton bt5 = NexButton(7, 5, "bt5");

//Declare variable global
bool statusbt0 = false;
bool statusbt1 = false;

//Modbus Relay
bool statusbt2 = false;
bool statusbt3 = false;
bool statusbt4 = false;
bool statusbt5 = false;

// Register objects to the touch event list
NexTouch *nex_listen_list[] = {

  &bt0,
  &bt1,

  &bt2,
  &bt3,
  &bt4,
  &bt5,

  NULL
};
//=========Nextion Library and Object==========//

//================ON,OFF Relay1=================//
void bt0PushCallback(void *ptr) {
  if (statusbt0 == false) {
    digitalWrite(sw1, LOW);
    statusbt0 = true;
  } else if (statusbt0 == true) {
    digitalWrite(sw1, HIGH);
    statusbt0 = false;
  }
}
//================ON,OFF Relay1=================//

//=================ON,OFF Relay2================//
void bt1PushCallback(void *ptr) {
  if (statusbt1 == false) {
    digitalWrite(sw2, LOW);
    statusbt1 = true;
  } else {
    digitalWrite(sw2, HIGH);
    statusbt1 = false;
  }
}

//==========Modbus Relay============//
//==========ON,OFF MRelay1==========//
void bt2PushCallback(void *ptr) {
  if (statusbt2 == false) {
    pool_size1 = node1.writeSingleRegister(0x01, 0x0100);
    statusbt2 = true;
  } else if (statusbt2 == true) {
    pool_size1 = node1.writeSingleRegister(0x01, 0x0200);
    statusbt2 = false;
  }
}
//==========ON,OFF MRelay1==========//

//==========ON,OFF MRelay2==========//
void bt3PushCallback(void *ptr) {
  if (statusbt3 == false) {
    pool_size1 = node1.writeSingleRegister(0x02, 0x0100);
    statusbt3 = true;
  } else if (statusbt3 == true) {
    pool_size1 = node1.writeSingleRegister(0x02, 0x0200);
    statusbt3 = false;
  }
}
//==========ON,OFF MRelay2==========//

//==========ON,OFF MRelay3==========//
void bt4PushCallback(void *ptr) {
  if (statusbt4 == false) {
    pool_size1 = node1.writeSingleRegister(0x03, 0x0100);
    statusbt4 = true;
  } else if (statusbt4 == true) {
    pool_size1 = node1.writeSingleRegister(0x03, 0x0200);
    statusbt4 = false;
  }
}
//==========ON,OFF MRelay3==========//

//==========ON,OFF MRelay4==========//
void bt5PushCallback(void *ptr) {
  if (statusbt5 == false) {
    pool_size1 = node1.writeSingleRegister(0x04, 0x0100);
    statusbt5 = true;
  } else if (statusbt5 == true) {
    pool_size1 = node1.writeSingleRegister(0x04, 0x0200);
    statusbt5 = false;
  }
}
//==========ON,OFF MRelay4==========//
//==========Modbus Relay============//

void NexSetup() {
  nexInit();  //initial Nextion
  node1.begin(2, Serial2);
  pinMode(sw1, OUTPUT);
  pinMode(sw2, OUTPUT);
  digitalWrite(sw1, HIGH);
  digitalWrite(sw2, HIGH);
  //2CH Relay
  bt0.attachPush(bt0PushCallback, &bt0);
  bt1.attachPush(bt1PushCallback, &bt1);

  //4CH Modbus
  bt2.attachPush(bt2PushCallback, &bt2);
  bt3.attachPush(bt3PushCallback, &bt3);
  bt4.attachPush(bt4PushCallback, &bt4);
  bt5.attachPush(bt5PushCallback, &bt5);
}

void NexRead() {

  char atemp[6];
  dtostrf(temp, 5, 1, atemp);

  char ahum[6];
  dtostrf(hum, 5, 1, ahum);

  int val1 = map(temp, 0, 100, 0, 180);
  int val2 = map(hum, 0, 100, 0, 180);
  int val3 = map(temp, 0, 100, 0, 100);
  int val4 = map(hum, 0, 100, 0, 100);

  vaTemp.setText(atemp);
  vaHum.setText(ahum);
  vvalTemp.setValue(val3);
  vvalHum.setValue(val4);
  vzTemp.setValue(val1);
  vzHum.setValue(val2);
}