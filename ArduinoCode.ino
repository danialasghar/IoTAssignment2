

#include "DHT.h"

#define DHTPIN 0 

#define DHTTYPE DHT11  

#include <ESP8266WiFi.h> // control the NodeMcu
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "Ali Salamat";
const char* password = "ttsahf777555";
WiFiClient wifiClient; 

void setup_wifi() 
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void setup() {
  Serial.begin(9600);
  setup_wifi();
  dht.begin();
}

void loop() {
  
  delay(10000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  if (WiFi.status() != WL_CONNECTED) {
    setup_wifi();
  } else {
    HTTPClient http; 

 http.begin(wifiClient, "http://10.0.0.70:8000/api/myapp/");
 http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    String string1 = "temperature=";
    String string2 = String(t);
    String string3 = String("&");
    String string4 = "humidity=";
    String string5 = String(h);
    String string6 = String(string1 + string2);
    String string7 = String(string6+ string3);
    String string8 = String(string7+ string4);
    String string9 = String(string8+ string5);
    
    Serial.println(string9);

    int httpCode = http.POST(string9);
    Serial.println(httpCode);
    http.end();
  }

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
}
