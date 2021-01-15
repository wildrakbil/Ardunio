#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#ifndef STASSID
#define STASSID "RED MASGAR"
#define STAPSK  "Mario1072639375"
#endif

const int SERIAL_PORT = 115200;

const char* ssid     = STASSID;
const char* password = STAPSK;

ESP8266WiFiMulti WiFiMulti;
HTTPClient http;
WiFiClient client;

//include
void config_setup(void);
void HTTP_request_methods(void);

// defines pins numbers

#define TRIGGER 2 //D1
#define ECHO    0 //D2

void setup() {
  board_config();
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  delay(500);
}


void loop() {
  long tiempo;
  float dist;
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  tiempo = pulseIn(ECHO, HIGH);
  dist = float (tiempo / 2) / 29.1;
  Serial.print("Distancia: ");
  Serial.println(dist);

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
    String sensorID = "1";
    String body = "{\"value\":" +  String(dist, 2) +  "}";
    Serial.print("Body: ");
    Serial.println(body);
    PUT_request(sensorID, body);

    String data = GET_request(sensorID);
    StaticJsonDocument<300> doc;
    deserializeJson(doc, data);
    String value = doc["data"]["value"];
    Serial.printf("Sensor value ::  %s\n", value.c_str());

  } else {
    Serial.println("Error in WiFi connection");
  }
  delay(500);
}


/*String data = GET_request(sensorID);
      StaticJsonDocument<300> doc;
      deserializeJson(doc, data);
      String value = doc["data"]["value"];
      Serial.printf("Sensor value ::  %s\n", value.c_str());

  JsonArray array = doc["data"].as<JsonArray>();
  for (JsonVariant v : array) {
  Serial.println("Sensor name :: " + v["name"].as<String>());
  }
*/
