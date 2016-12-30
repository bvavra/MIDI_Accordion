#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 bmp_180;

double Temp, P;
int tempStatus;
int pressureStatus;
double Calib_Pressure;
double Pressure;
int Pressure_Delta;

void init_BMP() {
  Serial.println("REBOOTING BMP180");
  // Initialize and calibrate the sensor
  if (bmp_180.begin())
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
    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
  Serial.println("BMP180 init success");
  reset_flags();
}

//This is only used to calibrate the BMP on startup.
double readPressure() {
  //We need to read the temperature every time because 
  //wind affects it, which in turn affects the pressure
  tempStatus = bmp_180.startTemperature();
  if (tempStatus != 0)
  {
    delay(tempStatus);// Wait for the measurement to complete:

    // Retrieve the completed temperature measurement:
    tempStatus = bmp_180.getTemperature(Temp);//sets Temp 
    if (tempStatus != 0)
    {
      // Start a pressure measurement:
      pressureStatus = bmp_180.startPressure(0);//Passing in 0 for speed
      if (pressureStatus != 0)
      {
        delay(pressureStatus);// Wait for the measurement to complete:
    
        // Retrieve the completed pressure measurement using the given temp:
        pressureStatus = bmp_180.getPressure(P,Temp);//sets P to pressure (in millibars)
        if (pressureStatus == 0) {
          Serial.println("error retrieving pressure measurement\n");
        }
      }
      else {
        Serial.println("error starting pressure measurement\n");
      }
    }
    else {
      Serial.println("error retrieving temperature measurement\n");
    }
  }
  else {
    Serial.println("error starting temperature measurement\n");
  }
  
  return P*100;//converting from millibars to pascals
}

int temp_wait_ms = 0; 
int pressure_wait_ms = 0;
unsigned long temp_init_ms = 0; 
unsigned long temp_final_ms = 0; 
unsigned long pressure_init_ms = 0;
unsigned long pressure_final_ms = 0;

/*if we're entering this function, we're in one of the following states:
* 1 - We just entered and need a temp reading
* 2 - We're waiting for a temp reading but it's not ready yet
* 3 - Temp reading is ready so we can start pressure reading
* 4 - We're waiting for pressure reading but it's not ready yet
* 5 - pressure reading is ready and we can get our new expression value.
*/
bool need_temp_reading = true;
bool temp_started = false;
bool temp_ready = false;
bool pressure_started = false;
bool pressure_ready = false;

void reset_flags(){
  need_temp_reading = true;
  temp_started = false;
  temp_ready = false;
  pressure_started = false;
  pressure_ready = false;
  temp_wait_ms = 0; 
  pressure_wait_ms = 0;
  temp_init_ms = 0; 
  temp_final_ms = 0; 
  pressure_init_ms = 0;
  pressure_final_ms = 0;
}

//this is a bit more verbose than it needs to be, but it's a lot easier to read...
int get_expression(int prev_expression) {
  int expression = prev_expression;

  if(need_temp_reading) {//States 1-3
    if(temp_started && !temp_ready){//2 - We're waiting for a temp reading but it's not ready yet
      //Serial.println("2 - We're waiting for a temp reading but it's not ready yet");
      temp_final_ms = millis();
      temp_wait_ms = temp_wait_ms + (temp_final_ms - temp_init_ms);
      temp_init_ms = millis();
      if(temp_wait_ms > tempStatus){
        temp_ready = true;
      }
    }
    if(!temp_started){//1 - We just entered and need a temp reading
      //Serial.println("1 - We just entered and need a temp reading");
      temp_init_ms = millis();
      tempStatus = bmp_180.startTemperature();
      temp_started = true;
    }
    if(temp_ready){//3 - Temp reading is ready so we can start pressure reading
      //Serial.println("3 - Temp reading is ready so we can start pressure reading");
      tempStatus = bmp_180.getTemperature(Temp);
      need_temp_reading = false;
      pressure_init_ms = millis();
      pressureStatus = bmp_180.startPressure(0);
      pressure_started = true;
    }
  }
  else if(pressure_started) {//States 4-5
    if(!pressure_ready) {//4 - We're waiting for pressure reading but it's not ready yet
      //Serial.println("4 - We're waiting for pressure reading but it's not ready yet");
      pressure_final_ms = millis();
      pressure_wait_ms = pressure_wait_ms + (pressure_final_ms - pressure_init_ms);
      pressure_init_ms = millis();
      if(pressure_wait_ms > tempStatus){
        pressure_ready = true;
      }
    }
    if(pressure_ready) {//5 - pressure reading is ready and we can get our new expression value.
      //Serial.println("5 - pressure reading is ready and we can get our new expression value.");
      pressureStatus = bmp_180.getPressure(P,Temp);
      expression = get_expression_from_pressure(P*100);//converting millibars to pascals
      reset_flags();
    }
  }
  else{
    Serial.println("Logical error - we shouldn't be here...");
    while(1); // Pause forever.
  }

  return expression;
}


int get_expression_from_pressure(double Pressure) {
  int expression;
  //minimum amount of pressure change required to form a sound
  int pressure_low_limit = 10;//default=10
  //maximum amount of pressure change to register
  //Any change higher than this is reported as 127 velocity.
  //Increasing this number allows for more expression, but a quieter sounding accordion
  //Decreasing this number lets the accordion get louder with less air, but also less expression.
  int pressure_high_limit = 120;//default=120
  
  Pressure_Delta = abs(Pressure - Calib_Pressure);

  // setting up minimal pressure to start a sound
  if (Pressure_Delta <= pressure_low_limit){
    expression = 0;
  }
  else { 
    //map() works if we want the correlation between pressure and velocity to be linear,
    //which may not be ideal.  I'll have to play a bit and see how this feels.
    //Both Dmitry and Jason use exponential functions, so I may end up switching to that.
    //Also, Jason applies different weights for pushing the bellows in or out,
    //so we may decide to something like that as well.
    expression = map(Pressure_Delta, pressure_low_limit, pressure_high_limit, 0, 127);
    if (expression > 127){
      expression = 127;
    } 
  }

  return expression;
}
