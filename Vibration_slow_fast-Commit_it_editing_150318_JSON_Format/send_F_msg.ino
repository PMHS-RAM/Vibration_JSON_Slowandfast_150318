
void send_Fmsg() {
  /////////////////
  Serial.println("----------------------------------");
  Serial.print(epoch);
   Serial.println(" ");
  testfile = SD.open("testdata.txt");
  if (testfile) {
    Serial.println("testdata.txt");
    Serial.println("I am reading file");
  }
  else
  {
    Serial.println("error opening testdata.txt");
  }
  while (testfile.available())
  {
    //     Serial.println("Inside the testfile.available()");
    String line = testfile.readStringUntil('\n');
    //    line.toCharArray(buf, 80);
    //Serial.println(buf);
    client.publish(topicName, line);
    client.loop();
  }

  testfile.close();
  ////////////////////Slow/STPCP-NEW
}
