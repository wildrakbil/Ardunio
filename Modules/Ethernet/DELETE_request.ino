void HTTP_DELETE_Request(EthernetClient client) {

  // Send HTTP request
  client.print(F("Delete "));
  client.print("/home/sensor/");
  client.print("1");
  client.println(F(" HTTP/1.0"));

  //Headers
  client.print(F("Host: "));
  client.println(TEST_HOST);
  client.println(F("Cache-Control: no-cache"));

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  Serial.print("status: ");
  Serial.println(status);
}
