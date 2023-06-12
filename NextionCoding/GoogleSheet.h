#include <HTTPClient.h>
const char *host = "script.google.com";
const char *httpsPort = "443";
String GAS_ID = "AKfycbyHrEODp5a7CnjoTr789zw1Rx9BYnpRqLfF6d0w-czD21Cu9CkMJdRjZhpgp-NiafN2";  //Google Script id from deploy app

void sendData2GGSheet() {
  HTTPClient http;
  String url = "https://script.google.com/macros/s/" + GAS_ID + "/exec?temp1=" + temp + "&humi1=" + hum;
  
  Serial.println("Posting Temperature and humidity data to Google Sheet");
  //---------------------------------------------------------------------
  //starts posting data to google sheet
  http.begin(url.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();
  Serial.print("HTTP Status Code: ");
  Serial.println(httpCode);
  //---------------------------------------------------------------------
  //getting response from google sheet
  String payload;
  if (httpCode > 0) {
    payload = http.getString();
    Serial.println("Payload: " + payload);
  }
  else sendData2GGSheet();
  //---------------------------------------------------------------------
  http.end();
}
