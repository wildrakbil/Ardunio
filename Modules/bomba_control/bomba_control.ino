#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoJson.h>
#include <HttpClient.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TEST_HOST "192.168.0.26" //localhost
#define TEST_PORT 8080 //PORT
const int SERIAL_PORT = 9600;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };// MAC Modulo Ethernet

LiquidCrystal_I2C lcd(0x27, 16, 2);
EthernetClient client;

//include
void config_setup(void);
void sensor(void);
void HTTP_request_methods(void);
void LCD(void);
// pines
const int LED = 6;
const int LCD_VCC = 5;
const int GP2D12 = A2;
//Bomba
int bomba_auto = 13;
int bomba_manual = 12;
// constans
const int alto = 515, bajo = 199; //valores de tensión del GP2D12 (9cm - 30cm)
// variable
char http_status[32] = {0};
String payload;
String sensorId = "1";
String HCSR04_value;

void setup() {
  board_config();
  Serial.println("Setup System complete");
  pinMode(LED, OUTPUT);
  pinMode(LCD_VCC, OUTPUT);
  digitalWrite(LCD_VCC, HIGH);
  pinMode(bomba_manual, OUTPUT);
  pinMode(bomba_auto, OUTPUT);
  digitalWrite(bomba_manual, HIGH);
}

void loop() {
  delay(2000);
  // logica consultar valor de HCSR04
  if (client.connect(TEST_HOST, TEST_PORT)) {
    GET_request(client, "/sensor/", sensorId);
    Serial.print("payload :: ");
    Serial.println(payload);
    StaticJsonDocument<300> doc;
    Serial.println(payload);
    deserializeJson(doc, payload);
    String value = doc["data"]["value"];
    HCSR04_value = value;
    printLCD("HCSR04_value : ", value);
    Serial.println("HCSR04_value : " + value);
    client.stop();
  } else {
    Serial.println("Connection failed...");
    printLCD("Connection: ", "failed...");
  }
  // logica de la bomba
  float value = HCSR04_value.toFloat();
  if (value < 4) {
    digitalWrite(bomba_auto, LOW);
    printLCD("Bomba: ", "LOW");
  }
  else {
    digitalWrite(bomba_auto, HIGH);
    printLCD("Bomba: ", "HIGH");
  }
}
