
void init_BMP() {
  Serial.println("REBOOT");
  // Initialize the sensor 
  //(it is important to get calibration values stored on the device).
  if (pressure.begin())
  {
    Serial.println("BMP180 init success");

    status = pressure.startTemperature();
    if (status != 0)
    {
      // Wait for the measurement to complete:
      delay(status);
  
      // Retrieve the completed temperature measurement:
      // Function returns 1 if successful, 0 if failure.
      status = pressure.getTemperature(Temp);//sets temperature
      if (status != 0)
      {
        // Print out the measurement:
        Serial.print("temperature: ");
        Serial.print((9.0/5.0)*Temp+32.0,2);//Temp is in C - converting to F
        Serial.println(" deg F");

        for (int i=0; i<32; i++){
          Calib_Pressure += readPressure();
        }
        Calib_Pressure = Calib_Pressure/32;
      }
      else Serial.println("error retrieving temperature measurement\n");
    }
    else Serial.println("error starting temperature measurement\n");
  }
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
}

double readPressure() {
  // Start a pressure measurement:
  // The parameter is the oversampling setting, 
  // from 0 to 3 (highest res, longest wait).
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.
  double P;
  status = pressure.startPressure(3);//We probably want 0, for speed
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed pressure measurement using the given temp:
    // (If temperature is stable, you can do one temperature measurement 
    // for a number of pressure measurements.)
    // Function returns 1 if successful, 0 if failure.
    status = pressure.getPressure(P,Temp);//sets P to pressure
    if (status != 0)
    {
      // Print out the measurement:
      Serial.print("Pressure: ");
      Serial.print(P,2);
      Serial.println(" mb, ");
    }
    else {
      Serial.println("error retrieving pressure measurement\n");
    }
  }
  else {
    Serial.println("error starting pressure measurement\n");
  }
  return P*100;//P is in millibars, but AccordionMega's code expects pascals
}

