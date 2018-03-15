void sampleFIFOBuffer() {    //Interrupt Service Routine

  //Serial.print(count++); Serial.print(" ");
  if (ringBuffer.getSize() <= 8016) {
    Wire.beginTransmission(devAddr);
    Wire.write(FIFO_regAddr);
    Wire.endTransmission();
    Wire.beginTransmission(devAddr);
    Wire.requestFrom(devAddr, 128);
    while ( Wire.available()) {
      if (!ringBuffer.put( Wire.read())) {
        Serial.println("I2C Read Failed"); Serial.flush();
      }
    }
    timer0_write(ESP.getCycleCount() + 980600L); // 80MHz == 1sec
  } else {
    //Serial.print("Size of Buffer: ");Serial.println(ringBuffer.getSize());Serial.flush();
    timer0_detachInterrupt();
  }
}
