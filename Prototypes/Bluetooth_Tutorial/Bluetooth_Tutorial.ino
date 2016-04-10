/*
  Bluetooth Serial Output
  Author: Brendan Vavra

  This is a simple counter to test sending data over a wireless Bluetooth connection.

  Circuit:
  - Bluetooth TX to Arduino RX
  - Bluetooth RX to Arduino TX (with voltage divider)
  - Bluetooth GND to Arduino GND
  - Bluetooth Vcc to Arduino 3.3V

  If everything is connected properly, you should be able to see the serial output
  using a terminal emulator such as TeraTerm: https://en.osdn.jp/projects/ttssh2/releases/
  
  Detailed instructions for connecting an HC-05 Bluetooth transceiver can be found here:
  http://www.instructables.com/id/Cheap-2-Way-Bluetooth-Connection-Between-Arduino-a/
*/
int counter = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  counter++;
  Serial.print("Arduino counter: ");
  Serial.println(counter);
  delay(500);
}
