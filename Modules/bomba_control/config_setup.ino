
IPAddress ip(192, 168, 0, 50);// IPv4 Address
IPAddress myDns(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 1);// Gateway
IPAddress subnet(255, 255, 255, 0);// Subnet Mask

void board_config() {
  Ethernet.begin(mac, ip, myDns, gateway, subnet);
  Serial.begin(SERIAL_PORT);  // Inicializa el puerto serial
  Serial.println("Start System ...");
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
  Serial.print("IPv4 Address: ");
  Serial.println(Ethernet.localIP());
  lcd.backlight();
  lcd.init();
}
