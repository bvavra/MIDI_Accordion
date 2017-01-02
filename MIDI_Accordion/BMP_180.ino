#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 bmp_180;

double Temp, P;
int tempStatus;
int pressureStatus;
double Calib_Pressure;

void init_BMP() {
  #ifdef DEBUG
    Serial.println("REBOOTING BMP180");
  #endif
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
    #ifdef DEBUG
      Serial.println("BMP180 init fail\n\n");
    #endif
    while(1); // Pause forever.
  }
  #ifdef DEBUG
    Serial.println("BMP180 init success");
  #endif
  reset_flags();
}

//This is only used to calibrate the BMP on startup because it takes about 12ms
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

int temp_wait_ms = 0; 
int pressure_wait_ms = 0;
unsigned long temp_init_ms = 0; 
unsigned long temp_final_ms = 0; 
unsigned long pressure_init_ms = 0;
unsigned long pressure_final_ms = 0;

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

/* If we're entering this function, we're in one of the following states:
*  1 - We just entered and need a temp reading
*  2 - We're waiting for temp reading but it's not ready yet
*  3 - Temp reading is ready so we can start pressure reading
*  4 - We're waiting for pressure reading but it's not ready yet
*  5 - pressure reading is ready and we can get our new expression
*/
int get_expression(int prev_expression) {
  int expression = prev_expression;

  if(need_temp_reading) {//States 1-3
    if(temp_started && !temp_ready){//2 - We're waiting for temp reading but it's not ready yet
      temp_final_ms = millis();
      temp_wait_ms = temp_wait_ms + (temp_final_ms - temp_init_ms);
      temp_init_ms = millis();
      if(temp_wait_ms > tempStatus){
        temp_ready = true;
      }
    }
    if(!temp_started){//1 - We just entered and need a temp reading
      temp_init_ms = millis();
      tempStatus = bmp_180.startTemperature();
      temp_started = true;
    }
    if(temp_ready){//3 - Temp reading is ready so we can start pressure reading
      tempStatus = bmp_180.getTemperature(Temp);
      need_temp_reading = false;
      pressure_init_ms = millis();
      pressureStatus = bmp_180.startPressure(0);
      pressure_started = true;
    }
  }
  else if(pressure_started) {//States 4-5
    if(!pressure_ready) {//4 - We're waiting for pressure reading but it's not ready yet
      pressure_final_ms = millis();
      pressure_wait_ms = pressure_wait_ms + (pressure_final_ms - pressure_init_ms);
      pressure_init_ms = millis();
      if(pressure_wait_ms > tempStatus){
        pressure_ready = true;
      }
    }
    if(pressure_ready) {//5 - pressure reading is ready and we can get our new expression
      pressureStatus = bmp_180.getPressure(P,Temp);
      expression = get_expression_from_pressure(P*100);//converting millibars to pascals
      reset_flags();
    }
  }

  return expression;
}

//Minimum amount of pressure change required to cause a change in volume.
int pressure_low_limit = 15;
//I decided to use a non-zero value for the minimum velocity.
//Although being able to sound without moving is not realistic, 
//it helps to compensate for having to push the bellows harder.
//Also, working with a smaller range allows for smoother dynamics
//because larger changes in pressure will cause smaller changes in volume.
int min_velocity = 55;

//Algorithm used to map pressure deltas into MIDI velocity
//Tweaks may need to be made for each accordion based on where the BMP_180 was placed 
//and how much air flows through the accordion when keys are pressed.
int get_expression_from_pressure(double Pressure) {
  int expression;
  float Pressure_Delta = abs(Pressure - Calib_Pressure);
  #ifdef BLUETOOTH
    //Uncomment this while sending MIDI data via Bluetooth to get
    //pressure delta output on the serial port while playing music.
//    if (Pressure_Delta > pressure_low_limit){ 
//      Serial.print("Pressure_Delta: ");
//      Serial.println(int(Pressure_Delta));
//    }
  #endif

  //I derived this formula from a graphing calculator (https://www.desmos.com/) 
  //I started with a cubic function: y=m(x-c)^3+nx+b
  //I set the constants until the contour fell in line with 
  //the expected pressure range and MIDI velocity output (0<x<250,0<y<127).
  //From there I tweaked values and play tested them until
  //I got something that sounded and felt right.
  //This function may need to be tweaked for different accordions and playing styles.
  expression = int(0.000014*pow(Pressure_Delta-162,3) + 0.01*Pressure_Delta)+99;

  //If the pressure delta is below the defined limit, set it to the minimum velocity.
  //This works best when the mapping function hits the coordinate where
  //x = pressure_low_limit and y = min_velocity
  if (Pressure_Delta < pressure_low_limit){ 
    expression = min_velocity;
  }
  if (expression > 127){
    expression = 127;
  }

  return expression;
}
