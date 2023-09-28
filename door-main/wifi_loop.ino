extern bool allowed;
extern bool faraday;

void wifi_loop()
{
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.print("Clique <a href=\"/H\">aqui</a> para abrir a porta.<br>");
            client.println();
            break;
          } else {
            currentLine = "";
          }

        } else if (c != '\r') {
          currentLine += c;
        }

        int var=0;
        if (currentLine.endsWith("GET /H")) {
          faraday = true;
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}