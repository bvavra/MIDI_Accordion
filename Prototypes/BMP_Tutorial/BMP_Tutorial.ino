/*
  Barometric Pressure Sensor
  Author: Brendan Vavra

  This sketch shows how to use the BMP180 to read changes in air pressure
  and convert the values to MIDI velocity.

  Based off SparkFun's BMP library examples

  Circuit:
  - BMP180 Vcc to Arduino 3.3V
  - BMP180 GND to Arduino GND
  - BMP180 SDA to Arduino SDA (A4 for Uno, 20 for Mega)
  - BMP180 SCL to Arduino SCL (A5 for Uno, 21 for Mega)

  From the doc page: 
  https://learn.sparkfun.com/tutorials/bmp180-barometric-pressure-sensor-hookup-
  "Note that it is safe to connect the SCA and SDL pins to an 
  I2C port on a 5V Arduino, as the pullup resistors on the 
  BMP180 board will keep the voltage below 3.6V."

  Blowing lightly on the sensor should change the pressure reading
  and, hence, the velocity.
*/
#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 pressure;

char status;
double Calib_Pressure, Pressure;
int Pressure_Delta;

void setup() {
  Serial.begin(9600);

  Serial.println("REBOOT");
  // Initialize the sensor 
  //(it is important to get calibration values stored on the device).
  if (pressure.begin())
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

void loop() {
  Serial.println("=====================");
  Pressure = readPressure();
  Serial.print("Calib_Pressure: ");
  Serial.println(Calib_Pressure);
  Pressure_Delta = abs(Pressure - Calib_Pressure);
  Serial.print("Pressure delta: ");
  Serial.println(Pressure_Delta);
  Pressure_Delta = constrain(Pressure_Delta, 10, 127);
  Serial.print("Velocity value: ");
  Serial.println(Pressure_Delta);
  delay(1000);
}

double readPressure() {
  double Temp, P;
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
      //Serial.print("Temperature: ");
      //Serial.print((9.0/5.0)*Temp+32.0,2);//Temp is in C - converting to F
      //Serial.println(" deg F");
      
      // Start a pressure measurement:
      // The parameter is the oversampling setting, 
      // from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.
      status = pressure.startPressure(0);//We probably want 0, for speed
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
          Serial.print(" mb, ");
          Serial.print(P*0.0295333727,2);
          Serial.println(" inHg");
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

