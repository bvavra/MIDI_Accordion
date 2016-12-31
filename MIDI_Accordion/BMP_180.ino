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
*  2 - We're waiting for a temp reading but it's not ready yet
*  3 - Temp reading is ready so we can start pressure reading
*  4 - We're waiting for pressure reading but it's not ready yet
*  5 - pressure reading is ready and we can get our new expression value.
*/
int get_expression(int prev_expression) {
  int expression = prev_expression;

  if(need_temp_reading) {//States 1-3
    if(temp_started && !temp_ready){//2 - We're waiting for a temp reading but it's not ready yet
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
    if(pressure_ready) {//5 - pressure reading is ready and we can get our new expression value.
      pressureStatus = bmp_180.getPressure(P,Temp);
      expression = get_expression_from_pressure(P*100);//converting millibars to pascals
      reset_flags();
    }
  }

  return expression;
}


//Algorithm used to map pressure deltas into MIDI velocity
//Tweaks may need to be made for each accordion based on where the BMP_180 was placed 
//and how much air flows through the accordion when keys are pressed.
int get_expression_from_pressure(double Pressure) {
  int expression;
  //minimum amount of pressure change required to form a sound
  int pressure_low_limit = 7;

  //This formula was taken from Jason's code.
  //It provides a more realistic sounding output than a linear mapping,
  //but as written it doesn't have a very large dynamic range (0 to ~50)
  //and requires a lot of physical force to make what seems like small volume changes.
  if (Pressure <= Calib_Pressure){ //Pulling bellows out
    expression = int(float((pow((Calib_Pressure - Pressure),1.4)+280)/45));   
  }
  else if (Pressure > Calib_Pressure){ //Pushing bellows in
    expression = int(float((pow((Pressure - Calib_Pressure),1.4)+280)/40));           
  } 
  if (expression < pressure_low_limit){ 
    expression = 0; 
  }

  //The above formula yields a very soft output in a small dynamic range.
  //I improved upon it by doing the following:

  //Multipying by a constant to widen the dynamic range.
  //This allows smaller bellow movements to better impact dynamic output
  //so that the player doesn't have to squeeze as hard to acheive a louder sound.
  //However, as this value increases changes in dynamics become more choppy,
  //so a sweet spot needs to be found.  Values between 1.5 and 3 seem to work well.
  expression *= 1.8;
  
  //I decided I would rather have a non-zero value for the minimum velocity,
  //so I'm shifting the entire output up by a constant.
  //Although it's less realistic, it helps to compensate for 
  //having to push the bellows harder than a normal accordion.
  //This also pushes up the dynamic range so that it's 
  //actually feasible to hit a velocity of 127.
  //I've played around with values between 50 and 60 - still need to try others.
  expression += 55;
  //but now it's possible to exceed 127, so we need to cap it.
  if (expression > 127){
    expression = 127;
  }

  return expression;
}
