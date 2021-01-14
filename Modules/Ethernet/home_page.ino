String readString;

void go_home_page(EthernetClient client) {
  boolean currentLineIsBlank = true;
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      if (readString.length() < 100) {
        readString += c;
      }
      if (c == '\n' && currentLineIsBlank) {
        Serial.println(readString); //Imprime en el monitor serial
        client.println("HTTP/1.1 200 OK");           //envia una nueva pagina en codigo HTML
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println("Refresh: 3");  // refresca la pagina automaticamente cada 3 segundos
        client.println();
        client.println("<!DOCTYPE HTML>");
        client.println("<HTML>");
        client.println("<HEAD>");
        client.println("<TITLE>Ethernet Arduino</TITLE>");
        client.println("<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css\" integrity=\"sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T\" crossorigin=\"anonymous\" > ");
        client.println("</HEAD>");
        client.println("<BODY>");
        client.println("<hr />");
        client.println("<H1>Arduino Ethernet Shield</H1>");
        client.println("<br />");
        client.println("<H2>LED Control on/off</H2>");
        client.println("<br />");

        client.println("<br />");
        client.println("<a href=\"/?ledOn\"\"> Encender LED</a> ");
        client.println(" | | | ");
        client.println("<a href=\"/?ledOff\"\"> Apagar LED</a><br /> ");
        client.println("<br />");

        int intSensorResult = analogRead(analogInPin);
        client.print("Entrada Analoga");
        client.print(analogInPin);
        client.print(" es ");
        client.print(intSensorResult);
        client.println("<br />");

        client.println("<hr />");
        client.println("<p>by: W. GARZON</p>");

        client.println("<script src=\"https://code.jquery.com/jquery-3.3.1.slim.min.js\" integrity=\"sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo\" crossorigin=\"anonymous\"></script>");
        client.println("<script src=\"https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js\" integrity=\"sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1\" crossorigin=\"anonymous\"></script>");
        client.println("<script src=\"https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js\" integrity=\"sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM\" crossorigin=\"anonymous\"></script>");
        client.println("</BODY>");
        client.println("</HTML>");

        if (readString.indexOf("?ledOn") > 0) {
          digitalWrite(LED, HIGH);
        }
        if (readString.indexOf("?ledOff") > 0) {
          digitalWrite(LED, LOW);
        }
        // Limpia el String(Cadena de Caracteres para una nueva lectura
        readString = "";
        break;
      }

      if (c == '\n') {
        currentLineIsBlank = true;
      }
      else if (c != '\r') {
        currentLineIsBlank = false;
      }
    }
  }
  delay(15);
  client.stop();
}
