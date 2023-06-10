#include <Nextion.h>
//#include <SoftwareSerial.h>

SoftwareSerial HMISerial(34, 35);  // RX,TX


//Page id 3 DualState Button
// NexButton bt0 = NexButton(3, 2, "bt0");
// NexButton bt1 = NexButton(3, 3, "bt1");

// //Page id 4 Text XY-MD02
NexText textemp1 = NexText(4, 2, "texttemp1");
NexText texhumi1 = NexText(4, 3, "texthumi1");


//Page id 5 Progress BarXY-MD02
NexText textemp2 = NexText(5, 4, "texttemp2");
NexText texhumi2 = NexText(5, 5, "texthumi2");
NexProgressBar pgtemp1 = NexProgressBar(5, 2, "pgtemp1");
NexProgressBar pghumi1 = NexProgressBar(5, 3, "pghumi1");

//Page id 6 Guage XY-MD02
NexGauge guagetemp1 = NexGauge(6, 3, "z0");
NexGauge guagehumi1 = NexGauge(6, 4, "z1");


//Page id 8 Modbus Relay
// NexButton bt2 = NexButton(7, 2, "bt2");
// NexButton bt3 = NexButton(7, 3, "bt3");
// NexButton bt4 = NexButton(7, 4, "bt4");
// NexButton bt5 = NexButton(7, 5, "bt5");

// Declare variable global
// bool statusbt0 = false;
// bool statusbt1 = false;
// //Modbus Relay
// // bool statusbt2 = false;
// // bool statusbt3 = false;
// // bool statusbt4 = false;
// // bool statusbt5 = false;

// // Register objects to the touch event list
// NexTouch *nex_listen_list[] = {

//   &bt0,
//   &bt1,

//   // &bt2,
//   // &bt3,
//   // &bt4,
//   // &bt5,

//   NULL
// };
//=========Nextion Library and Object==========//

//==========Define IO connect to relay==========//
// #define sw1 19
// #define sw2 18

// //================ON,OFF Relay1=================//
// void bt0PushCallback(void *ptr) {
//   if (statusbt0 == false) {
//     digitalWrite(sw1, LOW);
//     statusbt0 = true;
//   } else if (statusbt0 == true) {
//     digitalWrite(sw1, HIGH);
//     statusbt0 = false;
//   }
// }
// //================ON,OFF Relay1=================//

// //=================ON,OFF Relay2================//
// void bt1PushCallback(void *ptr) {
//   if (statusbt1 == false) {
//     digitalWrite(sw2, LOW);
//     statusbt1 = true;
//   } else {
//     digitalWrite(sw2, HIGH);
//     statusbt1 = false;
//   }
// }
// void endNextionCommand() {
//   HMISerial.write(0xff);
//   HMISerial.write(0xff);
//   HMISerial.write(0xff);
// }
void endNextionCommand() {
  Serial.write(0xff);
  Serial.write(0xff);
  Serial.write(0xff);
}

void NexSetup() {
  nexInit();  //initial Nextion
  //2CH Relay
  //   bt0.attachPush(bt0PushCallback, &bt0);
  //   bt1.attachPush(bt1PushCallback, &bt1);
 // HMISerial.begin(9600);
}

void Nexloop() {
  char atemp[6];
  dtostrf(temp, 6, 2, atemp);
  //  String ahum = String(hum);
   textemp1.setText(atemp);

  //page 4
  // String command = "texttemp1.txt=\"" + String(temp) + "\"";
  // HMISerial.print(command);
  // endNextionCommand();

  String command1 = "texthumi1.txt=\"" + String(hum) + "\"";
  HMISerial.print(command1);
  endNextionCommand();

  String command2 = "texttemp2.txt=\"" + String(temp) + "\"";
  Serial.print(command2);
  endNextionCommand();

  String command3 = "texthumi2.txt=\"" + String(hum) + "\"";
  Serial.print(command3);
  endNextionCommand();


  int val1 = map(temp, 0, 100, 0, 180);
  int val2 = map(hum, 0, 100, 0, 180);
  int val3 = map(temp, 0, 100, 0, 100);
  int val4 = map(hum, 0, 100, 0, 100);
  //pgtemp1.setValue(temp);
  Serial.print("pgtemp1.val=");
  Serial.print(val3);
  endNextionCommand();

  //pghumi1.setValue(hum);
  Serial.print("pghumi1.val=");
  Serial.print(val4);
  endNextionCommand();

  //Page 5 Guage XY-MD02

  Serial.print("z0.val=");  //Send the object tag
  Serial.print(val1);       //Send the value
  endNextionCommand();

  Serial.print("z1.val=");  //Send the object tag
  Serial.print(val2);       //Send the value
  endNextionCommand();
}