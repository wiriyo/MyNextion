#include <WiFi.h>
#include <WiFiClient.h>

char ssid[] = "";
char pass[] = "";
int wifiFlag = 0;

void initWiFi() {
  pinMode(wifiLed, OUTPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  digitalWrite(wifiLed, LOW);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  digitalWrite(wifiLed, HIGH);
}

void reconcectWifi() {
  int wifiCount = 0;
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(wifiLed, LOW);
    Serial.print('.');
    delay(1000);
    wifiCount++;
    if (wifiCount == 20) {
      wifiCount = 0;
      ESP.deepSleep(30e6);
      ESP.restart();
    }
  }
}
