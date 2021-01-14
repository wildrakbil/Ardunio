boolean alreadyConnected = false;

void get_sensor_value(EthernetClient client) {
  unsigned long timeout = millis();
  if (!alreadyConnected) {
    client.flush();
    Serial.println("We have a new client conextion");
    client.println("HTTP/1.1 200 OK");
    alreadyConnected = true;
  }

  if (client.available() > 0) {
    char thisChar = client.read();
    //server.write(thisChar);
    Serial.write(thisChar);
  } else {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Timeout !");
      client.stop();
      return;
    }
  }
}
