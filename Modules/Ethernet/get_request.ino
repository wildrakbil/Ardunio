void HTTP_GET_Request(EthernetClient client) {

  yield();

  // Send HTTP request
  client.print(F("GET "));
  client.print("/home/sensors");
  client.println(F(" HTTP/1.1"));

  //Headers
  client.print(F("Host: "));
  client.println(TEST_HOST);
  client.println(F("Cache-Control: no-cache"));

  if (client.println() == 0) {
    Serial.println(F("Failed to send request"));
    return;
  }

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0)
  {
    Serial.print(F("Unexpected response: "));
    Serial.println(status);
    //return;
  }

  // Skip HTTP headers
  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders))
  {
    Serial.println(F("Invalid response"));
    return;
  }

  char c = ' ';
  // limpia el header del response
  while (client.available() && client.peek() != '{')
  {
    client.readBytes(&c, 1);
  }

  // While the client is still availble read each
  // byte and print to the serial monitor
  while (client.available() && client.peek() != ']') {
    client.readBytes(&c, 1);
    //Serial.print(c);
    payload += c;
  }
}
