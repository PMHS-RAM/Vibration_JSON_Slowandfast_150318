

void emptySdCard() {

  // SD.open(filename,OPEN_READ|OPEN_WRITE) SD.open(filename) defaults to OPEN_READ
  root = SD.open("/");
  //root.rewindDirectory();
  printDirectory(root, 0); //Display the card contents
  root.close();
  Serial.println("\r\nPrinted Directories before emptying");  Serial.flush();
  //-------------------------------------------------------------------------------
  // SD.exists(filename) returns TRUE is found the name of the file to test for existence, which can include directories (delimited by forward-slashes, /)
  Serial.println("Look for a file called 'testfile.txt', if found remove it");
  if (SD.exists("testdata.txt")) {
    Serial.println("File testdata.txt found");
    if (SD.remove("testdata.txt")) Serial.println("File successfully deleted"); else Serial.println("Error - file not deleted");
    if (!SD.exists("testdata.txt")) Serial.println("Following confirmation checks, 'testfile.txt' now deleted\r\n");
  }
  else Serial.println("File testdata.txt not found");
  root.close(); Serial.flush();
}



void readFromSdCard() {

  Serial.println("Open a file called 'testfile.txt' and read the data from it");
  testfile = SD.open("testdata.txt", FILE_READ); // FILE_WRITE opens file for writing and moves to the end of the file
  while (testfile.available()) {
    Serial.write(testfile.read());
  }
  Serial.println("\r\nCompleted reading data from file\r\n");
  // close the file:
  testfile.close(); Serial.flush();
}

void printDirectory(File dir, int numTabs) {
  int colcnt = 0;
  while (true) {
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    if (numTabs > 0) {
      for (uint8_t i = 0; i <= numTabs; i++) {
        Serial.print('\t');
      }
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else
    {
      // files have sizes, directories do not
      Serial.print("\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void printRingBuffer() {

  for (uint16_t count = 1; count <= (ringBuffer.getSize()) ; count++) {
    int16_t Xg = (((int16_t) ringBuffer.get()) << 8 ) | ringBuffer.get();
    int16_t Yg = (((int16_t) ringBuffer.get()) << 8 ) | ringBuffer.get();
    int16_t Zg = (((int16_t) ringBuffer.get()) << 8 ) | ringBuffer.get();
    int16_t temp = (((int16_t) ringBuffer.get()) << 8 ) | ringBuffer.get();
    Serial.print(count); Serial.print(". Xg: "); Serial.print(Xg); Serial.print(" Yg: "); Serial.print(Yg); Serial.print(" Zg: "); Serial.print(Zg);
    Serial.print(" Temp: "); Serial.println(temp); Serial.flush(); //Serial.print(" Buff Size: ");Serial.println(ringBuffer.getSize());Serial.flush();
  }
}






