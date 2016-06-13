/*  Analog and Digital Read Opto-Interrupter
 *  Author: Brendan Vavra
 *  
 *  This is testing that the opto-interruptor reads a signal from the diode
 *  and that the value changes if the diode is blocked OR 
 *  the digital pin connected to the diode is turned LOW/HIGH
 *  
 *  This prototype also compares timing data between
 *  reading each analog pin with analogRead() vs
 *  reading the entire analog port directly.
 *  
 *    Circuit:
 *    - Opto-interruptor anode to Arduino 5v via 270Ω resistor
 *    - Opto-interruptor cathode to 2N2222A collector
 *    - Opto-interruptor collector to Arduino analog PIN 2
 *    - Opto-interruptor emitter to GND
 *    - 2N2222A to Arduino PIN 9 via 1kΩ resistor
 *    - 2N2222A emitter to GND
 */


int ruptPin = 2;    // select the input pin for the opto-interrupter
int val = -1;       // variable to store the analog value coming from the sensor
byte reg_values = 0;// variable to store the analog port value as a byte

int initial_us = 0; //timing variables
int final_us = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  digitalWrite(9, LOW);

  //Arduino UNO has different port letters than the MEGA,
  //so this check is required for this code to be compatible with both boards.
  #if defined (__AVR_ATmega328P__)//UNO
    DDRC = B00000000;  // PortC as input (for Arduino Uno)
    PORTC = B11111111; // turn on pullup resistors
  #elif defined (__AVR_ATmega2560__)//MEGA
    DDRF = B00000000;  // PortF as input (for Arduino Mega)
    PORTF = B11111111; // turn on pullup resistors
  #endif
}

void loop()
{
  digitalWrite(9, HIGH);
  Serial.print("PIN HIGH: ");
  readInterruptor();

  digitalWrite(9, LOW);
  Serial.print("PIN LOW: ");
  readInterruptor();
}

void readInterruptor()
{
  //Read the individual analog pin using analogRead()
  initial_us = micros();
  val = analogRead(ruptPin); // read the value from the sensor
  final_us = micros();
  Serial.print("Value for analog PIN: ");
  Serial.println(val);
  Serial.print("Time for analogRead(): ");
  Serial.println(final_us-initial_us);//c. 115us per PIN

  //Read the entire analog port directly
  initial_us = micros();
  #if defined (__AVR_ATmega328P__)//UNO
    reg_values = ~PINC;
  #elif defined (__AVR_ATmega2560__)//MEGA
    reg_values = ~PINF;
  #endif
  final_us = micros();
  Serial.print("Value for analog PORT: ");
  Serial.println(reg_values, BIN);
  Serial.print("Time for portRead(): ");
  Serial.println(final_us-initial_us);//c. 4us for all 6 PINs
  Serial.println("");
  delay(2500);
}

