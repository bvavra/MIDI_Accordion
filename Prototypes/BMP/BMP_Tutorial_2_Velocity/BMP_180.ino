#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 bmp_180;

void init_BMP() {
  Serial.println("REBOOT");
  // Initialize the sensor 
  //(it is important to get calibration values stored on the device).
  if (bmp_180.begin())
  {
    Serial.println("BMP180 init success");

    for (int i=0; i<32; i++){
      Calib_Pressure += readPressure();
      delayMicroseconds(500);
    }
    Calib_Pressure = Calib_Pressure/32;
  }
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
}

int tempStatus;
int pressureStatus;

double readPressure() {
  double Temp, P;
  //We need to read the temperature every time because wind can affect it,
  //which in turn affects the pressure
  tempStatus = bmp_180.startTemperature();
  if (tempStatus != 0)
  {
    Serial.print("Temp status: ");
    Serial.println(tempStatus);
    // Wait for the measurement to complete:
    delay(tempStatus);

    // Retrieve the completed temperature measurement:
    // Function returns 1 if successful, 0 if failure.
    tempStatus = bmp_180.getTemperature(Temp);//sets temperature
    if (tempStatus != 0)
    {
      // Print out the measurement:
      //Serial.print("Temperature: ");
      //Serial.print((9.0/5.0)*Temp+32.0,2);//Temp is in C - converting to F
      //Serial.println(" deg F");

      // Start a pressure measurement:
      // The parameter is the oversampling setting, 
      // from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.
      
      pressureStatus = bmp_180.startPressure(0);//We probably want 0, for speed
      if (pressureStatus != 0)
      {
        Serial.print("Pressure status: ");
        Serial.println(pressureStatus);
        // Wait for the measurement to complete:
        delay(pressureStatus);
    
        // Retrieve the completed pressure measurement using the given temp:
        // (If temperature is stable, you can do one temperature measurement 
        // for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.
        pressureStatus = bmp_180.getPressure(P,Temp);//sets P to pressure
        if (pressureStatus != 0)
        {
          // Print out the measurement:
          //Serial.print("Pressure: ");
          //Serial.print(P,2);
          //Serial.println(" mb, ");
        }
        else {
          Serial.println("error retrieving pressure measurement\n");
        }
      }
      else {
        Serial.println("error starting pressure measurement\n");
      }
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
  
  return P*100;//P is in millibars, but AccordionMega's code expects pascals
}

