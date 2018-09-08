#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;


const char* ssid     = "ssid"; // Your SSID (Name of your WiFi)
const char* password = "password"; //Your Wifi password

const char* host = "api.thingspeak.com";
String api_key = "api_key"; // Your API Key provied by thingspeak

extern String LocalWifiIP = "";

#define DELAY_TIME_BETWEEN_THINGSPEAK_UPDATE 300
unsigned long lThingspeakLoopPreviousTime = 0;

void setup_Thingspeak(){ 
  Connect_to_Wifi();
  // Set Time
  lThingspeakLoopPreviousTime = millis();
}

void loop_Thingspeak(){
  static unsigned int SensorLoop = 0;
  unsigned long lThingspeakLoopActual = millis();
  unsigned long lThingspeakLoopDelayTime = (lThingspeakLoopActual - lThingspeakLoopPreviousTime) / 1000;

  if(lThingspeakLoopDelayTime > DELAY_TIME_BETWEEN_THINGSPEAK_UPDATE) {
    Send_Data();
    lThingspeakLoopPreviousTime = millis();
  }
}

void Connect_to_Wifi()
{
    // We start by connecting to a WiFi network
    WiFiMulti.addAP(ssid, password);

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");
    
    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
 
}

void Send_Data()
{
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    delay(5000);
    return;
  }
  else
  {
    String data_to_send = api_key;
    data_to_send += "&field1=";
    data_to_send += String(BME280_Temp);
    data_to_send += "&field2=";
    data_to_send += String(BME280_Humidity);
    data_to_send += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);
  }

  client.stop();
}
