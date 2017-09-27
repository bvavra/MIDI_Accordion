/*
  Joystick Reader
  Author: Brendan Vavra

  This sketch shows how to use a joystick potentiometer.

  The circuit is as follows:
  - Joystick Pot Left to GND
  - Joystick Pot Right to 5V
  - Joystick Pot Middle to Analog
*/

int potPin = 2;    // select the input pin for the potentiometer
int val = 0;       // variable to store the value coming from the sensor
int oldVal = 0;
int startVal = 0;

void setup() {
  Serial.begin(9600);
  startVal = analogRead(potPin);
  Serial.print("Starting value for analog PIN: ");
  Serial.println(startVal);
}

void loop() {
  val = analogRead(potPin);    // read the value from the sensor
  if(val != oldVal) {
    Serial.print("Value for analog PIN: ");
    Serial.println(val);
    oldVal = val;
  }
}
