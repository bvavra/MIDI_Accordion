#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 pressure;

char status;
double Calib_Pressure;
double Pressure;
int Pressure_Delta;

void init_BMP() {
  #ifdef DEBUG
    Serial.println("REBOOTING BMP180");
  #endif
  // Initialize and calibrate the sensor
  if (pressure.begin())
  {
    //get an average reading
    for (int i=0; i<32; i++){
      Calib_Pressure += readPressure();
      delayMicroseconds(500);
    }
    Calib_Pressure = Calib_Pressure/32;
  }
  else //something went wrong - this is usually a connection problem
  {
    #ifdef DEBUG
      Serial.println("BMP180 init fail\n\n");
    #endif
    while(1); // Pause forever.
  }
  #ifdef DEBUG
    Serial.println("BMP180 init success");
  #endif
}

//TODO: this function takes a long time as written (c. 12ms)
//The time spent in the delays could be spent reading the sensors instead.
double readPressure() {
  double Temp, P;
  //We need to read the temperature every time because 
  //wind affects it, which in turn affects the pressure
  status = pressure.startTemperature();
  if (status != 0)
  {
    delay(status);// Wait for the measurement to complete:

    // Retrieve the completed temperature measurement:
    status = pressure.getTemperature(Temp);//sets Temp 
    if (status != 0)
    {
      // Start a pressure measurement:
      status = pressure.startPressure(0);//Passing in 0 for speed
      if (status != 0)
      {
        delay(status);// Wait for the measurement to complete:
    
        // Retrieve the completed pressure measurement using the given temp:
        status = pressure.getPressure(P,Temp);//sets P to pressure (in millibars)
        if (status == 0) {
          #ifdef DEBUG
            Serial.println("error retrieving pressure measurement\n");
          #endif
        }
      }
      else {
        #ifdef DEBUG
          Serial.println("error starting pressure measurement\n");
        #endif
      }
    }
    else {
      #ifdef DEBUG
        Serial.println("error retrieving temperature measurement\n");
      #endif
    }
  }
  else {
    #ifdef DEBUG
      Serial.println("error starting temperature measurement\n");
    #endif
  }
  
  return P*100;//converting from millibars to pascals
}

