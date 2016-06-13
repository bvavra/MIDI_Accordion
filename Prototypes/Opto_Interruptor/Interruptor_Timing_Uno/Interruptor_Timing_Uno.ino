/* Analog Read Interrupter
*/

int ruptPin = 2; //input pin for the interrupter
int val = -1; //analog value coming from the sensor
byte reg_values = 0;
int initial_us = 0;
int final_us = 0;

void setup()
{
    Serial.begin(9600); // set up Serial library at 9600 bps
    pinMode(9,OUTPUT);
    digitalWrite(9, HIGH);
    
    DDRC = B00000000;// PortC as input (for Arduino Uno)
    PORTC = B11111111;// turn on pullup resistors
}

void loop()
{
    Serial.print("Value should be read: ");
    readInterruptor();
    delay(1000);
    digitalWrite(9, LOW);
    Serial.print("Value should NOT be read: ");
    readInterruptor();//we should not be able to read this when it's turned off
    delay(1000);
    digitalWrite(9, HIGH);
}

void readInterruptor()
{
    Serial.print("Value for digital PIN: ");
    Serial.println(digitalRead(9)); // print the sensor value to the serial monitor
    //time how long it takes to do an analogRead
    initial_us = micros();
    val = analogRead(ruptPin); // read the value from the sensor
    final_us = micros();
    Serial.print("Value for analog PIN: ");
    Serial.println(val); // print the sensor value to the serial monitor
    Serial.print("Time for analogRead(): ");
    Serial.println(final_us-initial_us);//c. 115us per PIN

    //time how long it takes to read the entire port directly
    initial_us = micros();
    reg_values = ~PINC;
    final_us = micros();
    Serial.print("Value for analog PORT: ");
    Serial.println(reg_values, BIN);
    Serial.print("Time for portRead(): ");
    Serial.println(final_us-initial_us);//c. 4us for all 6 PINs
    Serial.println("");
}

