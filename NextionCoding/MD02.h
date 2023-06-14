uint8_t result;

#include <ModbusMaster.h>

ModbusMaster node;

void MD02setup() {
  Serial2.begin(9600);
  while (!Serial2) {
    Serial.println("loop for init software serial");
  }
  node.begin(1, Serial2);
}

void MD02Read() {
  //Sensor
  result = node.readInputRegisters(1, 2);
  if (result == node.ku8MBSuccess) {

    temp = node.getResponseBuffer(0) / 10.0f;
    hum = node.getResponseBuffer(1) / 10.0f;
    Serial.print("Temp: ");
    Serial.println(temp);
    Serial.print("Humi: ");
    Serial.println(hum);
    NexRead();
    for (int i = 0; i <= 5; i++) {
      bool ledStat = digitalRead(wifiLed);
      ledStat = !ledStat;
      digitalWrite(wifiLed, ledStat);
      delay(150);
    }
    digitalWrite(wifiLed, LOW);
  }
}
