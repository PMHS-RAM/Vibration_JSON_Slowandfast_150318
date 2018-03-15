void setup_wifi() {


  WiFiManager wifiManager;

  wifiManager.autoConnect("AutoConnectAP");


  Serial.println("connected...yeey :)");


  //  delay(10);
  //  // We start by connecting to a WiFi network
  //  Serial.println();
  //  Serial.print("Connecting to ");
  //  Serial.println(ssid);
  //
  //  WiFi.begin(ssid, password);
  //
  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(500);
  //    Serial.print(".");Serial.println("connected...yeey :)");
  //  }
  //
  //  randomSeed(micros());
  //
  //  Serial.println("");
  //  Serial.println("WiFi connected");
  //  Serial.println("IP address: ");
  //  Serial.println(WiFi.localIP());
}
