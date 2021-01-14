void GET_request(EthernetClient client, String path , String sensor) {

  // Send HTTP request
  client.print(F("GET "));
  //client.print("/home/sensor/" + idSensor);
  client.print("/home" + path + sensor);
  client.println(F(" HTTP/1.1"));

  //Headers
  client.print(F("Host: "));
  client.println(TEST_HOST);
  client.println(F("Cache-Control: no-cache"));

  if (client.println() == 0) {
    Serial.println(F("Failed to send request"));
    return;
  }

  client.readBytesUntil('\r', http_status, sizeof(http_status));

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
    payload += c;
  }

}


void PUT_request(EthernetClient client, String idSensor,  String  data) {

  // Send HTTP request
  client.print(F("PUT "));
  client.print("/home/sensor/" + idSensor);
  client.println(F(" HTTP/1.0"));

  //Headers
  client.print(F("Host: "));
  client.println(TEST_HOST);
  client.println(F("Cache-Control: no-cache"));
  client.println("User-Agent: Arduino/1.0");
  client.println("Accept: application/json");
  client.print("Content-Length: ");
  client.println(data.length());
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();
  client.println(data);
  client.readBytesUntil('\r', http_status, sizeof(http_status));

}


void POST_Request(EthernetClient client,  String  data) {

  // Send HTTP request
  client.print(F("POST "));
  client.print("/home/sensor");
  client.println(F(" HTTP/1.0"));

  //Headers
  client.print(F("Host: "));
  client.println(TEST_HOST);
  client.println(F("Cache-Control: no-cache"));
  client.println("User-Agent: Arduino/1.0");
  client.println("Accept: application/json");
  client.print("Content-Length: ");
  client.println(data.length());
  client.println("Content-Type: application/json");
  client.println("Connection: close");
  client.println();
  client.println(data);
  client.readBytesUntil('\r', http_status, sizeof(http_status));

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
