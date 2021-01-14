#include <Ethernet.h>
#include <SPI.h>


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress ip(192,168,0,101);
IPAddress gateway(192, 168, 43, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress servidor_dns(200,58,112,193);

byte server[] = {192, 168, 0, 101}; // localHost


EthernetClient client;

void initial_config(void);
void setup()
{
  initial_config();
}

void loop()
{
  if (client.connect(server, 80) > 0) {
    Serial.println("connected");
    client.println("GET /home/sensors HTTP/1.0");
    client.println("Content-Type: application/json");
    client.println();
    if (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  } else {
    Serial.println("connection failed");
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for (;;);
  }
}
