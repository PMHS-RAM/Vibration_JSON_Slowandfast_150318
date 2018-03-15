

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    //    if (client.connect(clientId.c_str())) {
    if (client.connect(MQTT::Connect(clientId.c_str()).set_auth("8jgxm5QM3hSC", "J4M!R3J7Dmm2zND&"))) {
      Serial.println("connected");
      client.set_callback(callback);
      // Once connected, publish an announcement...
      //      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("Slow/STPCP-NEW_F");
    } else {
      Serial.println("failed ");
      //      Serial.print(client.state());
      //      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
