void initial_config() {

  Serial.begin(9600);
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for (;;);
  }

  Serial.print("connecting...");
  Serial.println(Ethernet.localIP());

}
