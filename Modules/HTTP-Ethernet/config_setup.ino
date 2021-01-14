
int SERIAL_PORT = 9600;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };// MAC Modulo Ethernet
IPAddress ip(192, 168, 0, 50);// IPv4 Address
IPAddress myDns(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 1);// Gateway
IPAddress subnet(255, 255, 255, 0);// Subnet Mask

void board_config() {
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  Serial.begin(SERIAL_PORT);  // Inicializa el puerto serial
  while (!Serial);   // Espera a que el puerto serial sea conectado, Solo necesario para el Leonardo
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1);
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  //server.begin();
  Serial.print("IPv4 Address: ");
  Serial.println(Ethernet.localIP());
}
