void saveToSdCard() {

  root = SD.open("/");
  //root.rewindDirectory();
  printDirectory(root, 0); //Display the card contents
  root.close();
  Serial.println("\r\nPrinting directories before saving");
  Serial.println("\r\nOpen a file called 'testfile.txt' and write some data records"); Serial.flush();
  String tstamp = String(epoch);
  testfile = SD.open("testdata.txt", FILE_WRITE); // FILE_WRITE opens file for writing and moves to the end of the file
  if (testfile) {
    for (uint16_t count = 1; count <= (1002) ; count++) {
      testfile.print("F"); testfile.print("|"); testfile.print(epoch); testfile.print("|"); testfile.print(count); testfile.print(".");
      int16_t Xg = (((int16_t) ringBuffer.get()) << 8 ) | ringBuffer.get(); testfile.print("Xg:"); testfile.print(Xg); testfile.print("|");
      int16_t Yg = (((int16_t) ringBuffer.get()) << 8 ) | ringBuffer.get(); testfile.print("Yg:"); testfile.print(Yg); testfile.print("|");
      int16_t Zg = (((int16_t) ringBuffer.get()) << 8 ) | ringBuffer.get(); testfile.print("Zg:"); testfile.print(Zg); testfile.print("|");
      int16_t temp = (((int16_t) ringBuffer.get()) << 8 ) | ringBuffer.get();

   temperature = (temp / 340.) + 36.53;
      testfile.print("Temp:"); testfile.print(temperature); testfile.println();
    }
  }
  //  epoch=0;
  testfile.close(); Serial.flush();
}
