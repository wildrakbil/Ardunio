
void HTTP_POST_Request(EthernetClient client) {

  String  data = "{ \"name\": \"HCSR04_2\",\"description\": \"local\",\"value\": 23 }";

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

  // Check HTTP status
  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  Serial.print("status: ");
  Serial.println(status);

}
