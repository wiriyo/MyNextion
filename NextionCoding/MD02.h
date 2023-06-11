#include <ModbusMaster.h>

ModbusMaster node,node1 ;

uint8_t result;
// uint8_t pool_size1;

//==========Modbus Relay============//
//==========ON,OFF MRelay1==========//
void bt2PushCallback(void *ptr) {
  if (statusbt2 == false) {
    pool_size1 = node1.writeSingleRegister(0x01, 0x0100);
    //relayControl_modbusRTU(2, 1, 1);
    //digitalWrite(sw1, LOW);
    statusbt2 = true;
  } else if (statusbt2 == true) {
    pool_size1 = node1.writeSingleRegister(0x01, 0x0200);
    //relayControl_modbusRTU(2, 1, 0);
    //digitalWrite(sw1, HIGH);
    statusbt2 = false;
  }
}
//==========ON,OFF MRelay1==========//

//==========ON,OFF MRelay2==========//
void bt3PushCallback(void *ptr) {
  if (statusbt3 == false) {
    pool_size1 = node1.writeSingleRegister(0x02, 0x0100);
    //relayControl_modbusRTU(2, 2, 1);
    //digitalWrite(sw1, LOW);
    statusbt3 = true;
  } else if (statusbt3 == true) {
    pool_size1 = node1.writeSingleRegister(0x02, 0x0200);
    //relayControl_modbusRTU(2, 2, 0);
    //digitalWrite(sw1, HIGH);
    statusbt3 = false;
  }
}
//==========ON,OFF MRelay2==========//

//==========ON,OFF MRelay3==========//
void bt4PushCallback(void *ptr) {
  if (statusbt4 == false) {
    pool_size1 = node1.writeSingleRegister(0x03, 0x0100);
    //relayControl_modbusRTU(2, 3, 1);
    //digitalWrite(sw1, LOW);
    statusbt4 = true;
  } else if (statusbt4 == true) {
    pool_size1 = node1.writeSingleRegister(0x03, 0x0200);
    //relayControl_modbusRTU(2, 3, 0);
    //digitalWrite(sw1, HIGH);
    statusbt4 = false;
  }
}
//==========ON,OFF MRelay3==========//

//==========ON,OFF MRelay4==========//
void bt5PushCallback(void *ptr) {
  if (statusbt5 == false) {
    pool_size1 = node1.writeSingleRegister(0x04, 0x0100);
    //relayControl_modbusRTU(2, 4, 1);
    //digitalWrite(sw1, LOW);
    statusbt5 = true;
  } else if (statusbt5 == true) {
    pool_size1 = node1.writeSingleRegister(0x04, 0x0200);
    //relayControl_modbusRTU(2, 4, 0);
    //digitalWrite(sw1, HIGH);
    statusbt5 = false;
  }
}
//==========ON,OFF MRelay4==========//
//==========Modbus Relay============//

void MD02setup()
{
  Serial2.begin(9600);
  while (!Serial2) {
    Serial.println("loop for init software serial");
  }
  node.begin(1, Serial2);
  node1.begin(2,Serial2);
}

void MD02Read()
{
  //Sensor
  result = node.readInputRegisters(1, 2);
  if (result == node.ku8MBSuccess)
  {
   
    temp = node.getResponseBuffer(0) / 10.0f;
    hum = node.getResponseBuffer(1) / 10.0f;
    Serial.print("Temp: ");
    Serial.println(temp);
    Serial.print("Humi: ");
    Serial.println(hum);
    Serial.println();
    NexRead();
  }


}
  