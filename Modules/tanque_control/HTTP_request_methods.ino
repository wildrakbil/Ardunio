
const String URL_GET_ALL = "http://192.168.0.40:8080/home/sensors";
const String URL_GET_BY_ID = "http://192.168.0.40:8080/home/sensor/";
const String URL_PUT = "http://192.168.0.40:8080/home/sensor/";

String GET_request(String sensorID) {
  String payload = "";
  if (http.begin(client, URL_GET_BY_ID + sensorID)) {
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
    int httpCode = http.GET();   //Send the request
    if (httpCode > 0) {
      //Serial.println("httpCode :: " + httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        payload = http.getString();   // Obtener respuesta
        //Serial.println("payload :: " + payload);
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
  http.end();
  return payload;
}

void PUT_request(String sensorID, String body) {
  //Serial.println("sensorID :: " + sensorID + "\nBody :: " + body);
  if (http.begin(client, URL_PUT + sensorID)) {
    http.addHeader("Content-Type", "application/json");
    int httpCode =  http.PUT(body);
    if (httpCode > 0) {
      //Serial.println("httpCode ::" + httpCode  );
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        Serial.println("Valid httpCode ::" + httpCode  );
      }
    } else {
      Serial.printf("[HTTP] PUT... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
  } else {
    Serial.printf("[HTTP} Unable to connect\n");
  }
  http.end();
}

void POST_request() {
}
