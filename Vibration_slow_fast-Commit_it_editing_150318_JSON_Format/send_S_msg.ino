
void send_Smsg() {

  /***************************************With Time Stamp ************************/
  //Commented because, Rearranging the structure as per Rishi format on 13-03-2018

  /*String data = String("Slow/STPCP-NEW") + String("|") + String(epoch) + String("|")
                + String(axminX) + String("|") + String(axmaxX) + String("|") + String(axavgX) + String("|")
                + String(ayminX) + String("|") + String(aymaxX) + String("|") + String(ayavgX) + String("|")
                + String(azminX) + String("|") + String(azmaxX) + String("|") + String(azavgX) + String("|") + String(temp);
  */
  //Rishi String Format

  /*
     String data = String("$") + String("|") + String(temp1) + String("|") + String(axmaxX) + String("|")  + String(axminX) + String("|")  + String(axavgX) + String("|")
                + String(aymaxX) + String("|")  + String(ayminX) + String("|")  + String(ayavgX)  + String("|")
                + String(azmaxX) + String("|") + String(azminX) + String("|") + String(azavgX) + String("|") + String("#");


    char bufferdata[130];

    data.toCharArray(bufferdata, 130);

    Serial.println(bufferdata);
  */

  DynamicJsonBuffer  jsonBuffer(500);

  JsonObject& root = jsonBuffer.createObject();

  /*root["sensor"] = "Accelerometer";*/ root["time"] = epoch; root["Temperatue"] = temp1;
  root["maxX"] = axmaxX; root["minX"] = axminX;  root["avgX"] = axavgX;
  root["maxY"] = aymaxX; root["minY"] = ayminX;  root["avgY"] = ayavgX;
  root["maxZ"] = azmaxX; root["minZ"] = azminX;  root["avgZ"] = azavgX;



  root.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

  if (client.publish(topicName, JSONmessageBuffer) == true) {
    Serial.println("Success sending message");
  } else {
    Serial.println("Error sending message");
  }

  client.loop();
  Serial.println("-------------");

}





//
//void send_Smsg_json() {
//
//  StaticJsonBuffer<300> JSONbuffer;
//  JsonObject& JSONencoder = JSONbuffer.createObject();
//
//  JSONencoder["D"] = "ESP8x";
//  JSONencoder["S"] = "ACCr";
//  JsonArray& values = JSONencoder.createNestedArray("Data");
//
//  values.add(epoch);
//
//  values.add(axminX);
//  values.add(axmaxX);
//  values.add(axavgX);
//
//  values.add(ayminX);
//  values.add(aymaxX);
//  values.add(ayavgX);
//
//  values.add(azminX);
//  values.add(azmaxX);
//  values.add(azavgX);
//  values.add(temp);
//
//  char JSONmessageBuffer[456];
//  Serial.println("Size of JSON MSG BUFFER");
//  Serial.print(sizeof(JSONmessageBuffer));
//  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
//  Serial.println("Sending message to MQTT topic..");
//  Serial.println(JSONmessageBuffer);
//
//  if (client.publish("ESP8266", JSONmessageBuffer) == true) {
//    Serial.println("Success sending message");
//  } else {
//    Serial.println("Error sending message");
//  }
//
//  client.loop();
//  Serial.println("-------------");
//
//  //delay(10000);
//
//}
//


















