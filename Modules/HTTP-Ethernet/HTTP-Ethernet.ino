#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>
#include <HttpClient.h>

#define TEST_HOST "192.168.0.26" //localhost
#define TEST_PORT 8080 //PORT

void config_setup(void);
void sensor(void);
void HTTP_request_methods(void);

const int LED = 6;
const int GP2D12 = A2;
const int alto = 515, bajo = 199; //valores de tensión del GP2D12 (9cm - 30cm)
char http_status[32] = {0};

String payload;
int value;
int cm = 0;
String sensorId;

EthernetClient client;

void setup() {
  pinMode(LED, OUTPUT);
  board_config();
  sensor_create("HCSR04_7", "Nuevo sensor del techo", 0);
  //Serial.print("ID_Sensor :: ");
  //Serial.println(sensorId);
}

void loop() {
  //lectura del valor del GP2D12
  value = analogRead(GP2D12);
  cm = (6787 / (value - 3)) - 4;      //calculo
  if (value > alto || value < bajo) {
    digitalWrite(LED, LOW);
  }
  else {
    digitalWrite(LED, HIGH);
  }

  if (client.connect(TEST_HOST, TEST_PORT)) {
    String  data = "{ \"value\": " + String(cm) + " }";
    PUT_request(client, sensorId, data);
    GET_request(client, "/sensor/", sensorId);
    StaticJsonDocument<300> doc;
    deserializeJson(doc, payload);
    String value = doc["data"]["value"];
    Serial.print("Value_Sensor :: ");
    Serial.println(value);
    payload = "";
  } else {
    Serial.println(F("Connection failed"));
  }
}
