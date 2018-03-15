void fifo_init() {

  ringBuffer.init(8192); // Size of circular buffer = 1024 BYTES
  // Execute rest of code, if MPU connection successful
  if (accelgyro.testConnection()) {

    // Sampling Rate
    Serial.print(F("Check Sample Rate set :")); accelgyro.setRate(0x07); //Set rate to 1 KHz for both acceleration and Gyro

    if (accelgyro.getRate() == 0x07) Serial.println(F("Accelerometer Sample Rate = 1 KHz & Gyro Sample rate = 8 KHz"));
    else {
      Serial.print(F("SampleRate different,Register Value: "));
      Serial.println(accelgyro.getRate(), HEX);
    }

    // Check Digital Low Pass Filter Bandwidth .... If 260 Hz BW, Motor RPM must be less than 15,600 RPM (260*60)
    Serial.print(F("Check Low Pass Filter Bandwidth : ")); //accelgyro.setDLPFMode(MPU6050_DLPF_BW_256); uncomment this line to set it to 250 Hz bandwidth
    if (accelgyro.getDLPFMode() == 0x00) Serial.println(F("LPF Bandwidth is  260 Hz"));
    else Serial.println(F("LPF Bandwidth is other than 260 Hz"));

    // Check Temperature FIFO Enabled
    Serial.println(F("Check if Temperature FIFO enabled : "));
    accelgyro.setTempFIFOEnabled(1);
    Serial.println(accelgyro.getTempFIFOEnabled() ? "Yes, Temperature FIFO enabled" : "No, Temperature FIFO disabled");

    // Check Accelerometer FIFO Enabled
    Serial.println(F("Check if Accelerometer FIFO enabled : "));
    accelgyro.setAccelFIFOEnabled(1);
    Serial.println(accelgyro.getAccelFIFOEnabled() ? "Yes, Accelerometer FIFO enabled" : "No, Accelerometer FIFO disabled");

    // Check FIFO Buffer Overflow Interrupt enabled
    Serial.println(F("Check if FIFO Buffer Overflow Interrupt enabled : "));
    accelgyro.setIntFIFOBufferOverflowEnabled(1);
    Serial.println(accelgyro.getIntFIFOBufferOverflowEnabled() ? "Yes, FIFO Buffer Overflow Interrupt enabled" : "No, FIFO Buffer Overflow Interrupt disabled");

    // Check Status of FIFO Buffer Overflow Interrupt Status
    Serial.print(F("Check status of FIFO Buffer Overflow Interrupt status : "));
    Serial.println(accelgyro.getIntFIFOBufferOverflowStatus() ? "Yes, FIFO Buffer Overflowed" : "No, FIFO Buffer yet to overflow"); Serial.flush();

    // Disabling FIFO to reset FIFO buffer
    Serial.println(F("Disabling FIFO operations to reset FIFO buffer: "));
    accelgyro.setFIFOEnabled(0);
    Serial.println(accelgyro.getFIFOEnabled() ? "Yes, FIFO Operations enabled" : " FIFO operations disabled");

    // Resetting FIFO Buffer to clear old vlaues
    Serial.println(F("Resetting FIFO Buffer to clear old values: "));
    accelgyro.resetFIFO();
    Serial.println(accelgyro.getFIFOEnabled() ? "Yes, FIFO Operations enabled" : " FIFO operations disabled");
    //delay(1000);

    // Enabling the FIFO operations
    Serial.println(F("Enabling the FIFO operations: "));
    accelgyro.setFIFOEnabled(1);
    Serial.println(accelgyro.getFIFOEnabled() ? "Yes, FIFO Operations enabled" : "No, FIFO operations disabled");

    // Check again the Status of FIFO Buffer Overflow Interrupt Status after FIFO reset
    Serial.println(F("Check status of FIFO Buffer Overflow Interrupt status : ")); Serial.flush();
    Serial.println(accelgyro.getIntFIFOBufferOverflowStatus() ? "Yes, FIFO Buffer Overflowed" : "No, FIFO Buffer yet to overflow");//delay(5000);
    Serial.flush();

    //*****************READ / WRITE OPERATIONS IN FIFO  ************************//

    Serial.print(F("Number of Bytes available from FIFO Buffer to read: "));
    Serial.println(accelgyro.getFIFOCount());

    emptySdCard(); // clearing the file testdata.txt

    // Configure Timer Interrupt Settings
    noInterrupts();
    timer0_isr_init();
    timer0_attachInterrupt(sampleFIFOBuffer);
    timer0_write(ESP.getCycleCount() + 980600L); // 80MHz == 1sec, so 0.125sec = 80M*0.125=10MHz
    interrupts();

  }   // if condition ends
  Serial.println(F("                "));
  Serial.println(F("Setup complete"));
  Serial.println(F("                "));
  Serial.flush();

  uint32_t currentTimer = micros();
  while (micros() - currentTimer <= 1000000) {
    //  while (micros() - currentTimer <= 10000) {
    //DO nothing
  }
  noInterrupts();
  Serial.println("Buffer Size after Sampling: "); Serial.println(ringBuffer.getSize()); //ringBuffer.clear(); Serial.println(ringBuffer.getSize());
  Serial.print("FIFOCnt "); Serial.println(accelgyro.getFIFOCount()); Serial.flush();



  saveToSdCard(); Serial.println("saved to card");
  //readFromSdCard();
  Serial.println("HURRAY");

}

