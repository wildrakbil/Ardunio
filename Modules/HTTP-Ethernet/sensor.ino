boolean connection = true;
boolean status_create = true;

void sensor_create(String name, String description, int value) {
  String  data = "{ \"name\": \"" + name + "\",\"description\": \"" + description + "\",\"value\":" + value + "}";
  while (connection) {
    if (client.connect(TEST_HOST, TEST_PORT)) {
      connection = false;
      GET_request(client, "/sensorByName/", name);
      //Serial.println("GET::" + payload);
      if (strcmp(http_status, "HTTP/1.1 200 ") != 0) {
        payload = "";
        while (status_create) {
          POST_Request(client, data);
          //Serial.println("POST::" + payload);
          if (strcmp(http_status, "HTTP/1.1 201 ") != 0) {
            Serial.print(F("Unexpected response: "));
            Serial.println(http_status);
          } else {
            status_create = false;
          }
        }
      }
      StaticJsonDocument<300> doc;
      deserializeJson(doc, payload);
      String id = doc["data"]["id"];
      sensorId = id;
      payload = "";
    } else {
      Serial.println(F("Connection failed..."));
    }
  }
}
