
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>
#include <HttpClient.h>

#define TEST_HOST "192.168.0.26" //localhost
#define TEST_PORT 8080 //PORT

int LED = 6;
const int analogInPin = A1;

EthernetClient client;

void config_setup(void);
void home_page(EthernetClient client);
void cmd_conextion(EthernetClient client);
void get_request(EthernetClient client);
void post_request(EthernetClient client);
void put_request(EthernetClient client);
void DELETE_request(EthernetClient client);

void setup() {
  pinMode(LED, OUTPUT);
  board_config();
}

boolean response = false;
String payload;

void loop() {

  /*if (!response) {
    if (client.connect(TEST_HOST, TEST_PORT)) {
      HTTP_DELETE_Request(client);
      Serial.println(F("End Request"));
      response = true;
    } else {
      Serial.println(F("Connection failed"));
    }
  }*/

  /*if (!response) {
    if (client.connect(TEST_HOST, TEST_PORT)) {
      HTTP_PUT_Request(client);
      Serial.println(F("End Request"));
      response = true;
    } else {
      Serial.println(F("Connection failed"));
    }
  }*/

  /*if (!response) {
    if (client.connect(TEST_HOST, TEST_PORT)) {
      HTTP_POST_Request(client);
      Serial.println(F("End Request"));
      response = true;
    } else {
      Serial.println(F("Connection failed"));
    }
  }*/

  if (!response) {
    if (client.connect(TEST_HOST, TEST_PORT)) {
      HTTP_GET_Request(client);
      Serial.println(F("End Response"));
      response = true;
    } else {
      Serial.print(F("TEST_HOST : "));
      Serial.println(TEST_HOST);
      Serial.print(F("TEST_PORT : "));
      Serial.println(TEST_PORT);
      Serial.println(F("Connection failed"));
    }
    Serial.print("payload:");
    Serial.println(payload);
    StaticJsonDocument<300> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
      return;
    }
    String name = doc["name"];
    Serial.println(name);
    }

}
