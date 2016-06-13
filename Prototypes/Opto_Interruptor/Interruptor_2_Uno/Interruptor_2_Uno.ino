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
    digitalWrite(9, LOW);
    pinMode(10,OUTPUT);
    digitalWrite(10, LOW);
    
    DDRC = B00000000;// PortC as input (for Arduino Uno)
    PORTC = B11111111;// turn on pullup resistors
}

void loop()
{
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    Serial.print("PIN 9: ");
    Serial.println(digitalRead(9));
    Serial.print("PIN 10: ");
    Serial.println(digitalRead(10));
    readInterruptor();
    delay(2000);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    Serial.print("PIN 9: ");
    Serial.println(digitalRead(9));
    Serial.print("PIN 10: ");
    Serial.println(digitalRead(10));
    readInterruptor();//we should not be able to read this when it's turned off
    delay(2000);
}

void readInterruptor()
{
    //time how long it takes to read the entire port directly
    initial_us = micros();
    reg_values = ~PINC;
    final_us = micros();
    Serial.print("Value for analog PORT: ");
    Serial.println(reg_values, BIN);
    //Serial.print("Time for portRead(): ");
    //Serial.println(final_us-initial_us);//c. 4us for all 6 PINs
    
    //time how long it takes to do an analogRead
    initial_us = micros();
    val = analogRead(ruptPin); // read the value from the sensor
    final_us = micros();
    Serial.print("Value for analog PIN: ");
    Serial.println(val); // print the sensor value to the serial monitor
    //Serial.print("Time for analogRead(): ");
    //Serial.println(final_us-initial_us);//c. 115us per PIN
    Serial.println("===");
}

