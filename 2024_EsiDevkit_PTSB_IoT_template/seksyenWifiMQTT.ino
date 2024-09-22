void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

 

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  display.setTextColor(WHITE,BLACK);
  display.setCursor(0,10);
  display.print("WiFi connected");
  display.setCursor(0,20);
  display.print(WiFi.localIP());
   display.display();
  delay(5000);
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // letakkan kawalan topic sub MQTT anda disini ---------------------------------



  //------------------------------------------------------------------------------
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Letakan Id bagi Peranti anda")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("namaTopicAnda1");
      client.subscribe("namaTopicAnda3");
      client.subscribe("namaTopicAnda3");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
