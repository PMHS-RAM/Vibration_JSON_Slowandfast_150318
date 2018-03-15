void slow_data() {
  unsigned long finishAT = millis() + interval1;

  n = 0; axsumX, aysumX, azsumX = 0;

  rawTemp = accelgyro.getTemperature();

  temp1 = (rawTemp / 340.) + 36.53;

  while (millis() <= finishAT)
  {
    //accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    ax = accelgyro.getAccelerationX();
    ay = accelgyro.getAccelerationY();
    az = accelgyro.getAccelerationZ();

    if (n == 0)
    {
      axminX = ax;
      ayminX = ay;
      azminX = az;
      axmaxX = ax;
      aymaxX = ay;
      azmaxX = az;
      axsumX = ax;
      aysumX = ay;
      azsumX = az;
    }
    else
    {
      axminX = _min(axminX, ax);
      ayminX = _min(ayminX, ay);
      azminX = _min(azminX, az);
      axmaxX = _max(axmaxX, ax);
      aymaxX = _max(aymaxX, ay);
      azmaxX = _max(azmaxX, az);
      axsumX = axsumX + ax;
      aysumX = aysumX + ay;
      azsumX = azsumX + az;
    }

    n = n + 1;
  }           //While Loop Ends

  axavgX = (axsumX / (float(n)));
  ayavgX = (aysumX / (float(n)));
  azavgX = (azsumX / (float(n)));

}
