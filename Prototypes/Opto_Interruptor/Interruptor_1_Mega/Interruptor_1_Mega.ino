/* Analog and Digital Read Interrupter
 *  Author: Brendan Vavra
 *  
 *  This is testing that the interruptor reads a signal from the diode
 *  and that the value changes if the diode is blocked OR 
 *  the digital pin connected to the diode is turned LOW/HIGH
 *  
 */
byte reg_values = 0;
int ruptPin = 2; // select the input pin for the interrupter
int val = -1; // variable to store the analog value coming from the sensor

void setup()
{
    Serial.begin(9600);
    pinMode(9,OUTPUT);
    digitalWrite(9, HIGH);

//    DDRK = B00000000;// PortF as input (for Arduino Mega)
//    PORTK = B11111111;// turn on pullup resistors
    DDRF = B00000000;// PortF as input (for Arduino Mega)
    PORTF = B11111111;// turn on pullup resistors
}

void loop()
{
    digitalWrite(9, HIGH);
    delay(1);
    val = analogRead(ruptPin); // read the value from the sensor
    reg_values = ~PINF;
    Serial.print("PIN HIGH: ");
    Serial.println(val); // print the sensor value to the serial monitor
    Serial.println(reg_values, BIN);
    Serial.println("");
    delay(1500);

//    digitalWrite(9, LOW);
//    delay(1);
//    val = analogRead(ruptPin); // read the value from the sensor
//    reg_values = ~PINF;
//    Serial.print("PIN LOW: ");
//    Serial.println(val); // print the sensor value to the serial monitor
//    Serial.println(reg_values, BIN);
//    Serial.println("");
//    delay(2000);

}
