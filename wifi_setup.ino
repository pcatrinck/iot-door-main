void wifi_setup()
{
  Serial.print("Conecting to... ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi conected.");
  Serial.println("IP adress: ");
  Serial.println(WiFi.localIP());
 
  server.begin();
}