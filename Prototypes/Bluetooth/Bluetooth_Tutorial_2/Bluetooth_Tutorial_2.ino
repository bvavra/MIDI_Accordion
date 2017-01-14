/*
  Bluetooth HC-05 AT Command Mode
  Author: Brendan Vavra

  This is a program to set AT commands on the HC-05 Bluetooth transceiver.
  Made with the help of these links:
  http://www.instructables.com/id/Modify-The-HC-05-Bluetooth-Module-Defaults-Using-A/?ALLSTEPS
  http://www.martyncurrey.com/arduino-with-hc-05-bluetooth-module-at-mode/

  Circuit:
  - Bluetooth TX to Arduino PIN 10
  - Bluetooth RX to Arduino PIN 11 (via voltage divider)
  - Bluetooth GND to Arduino GND
  - Bluetooth Vcc to Arduino 3.3V
  - Bluetooth KEY to Arduino PIN 9 (via voltage divider)

  HC-05 AT COMMANDS
  AT : Ceck the connection.
  AT+NAME : See default name
  AT+ADDR : See default address
  AT+VERSION : See version
  AT+UART : See baudrate
  AT+ROLE: See role of bt module(1=master/0=slave)
  AT+RESET : Reset and exit AT mode
  AT+ORGL : Restore factory settings
  AT+PSWD: See default password

  To change device name from the default HC-05 to let's say MYBLUE enter: "AT+NAME=MYBLUE"
  To change default security code from 1234 to 2987 enter: "AT+PSWD=2987"
  To change HC-05 baud rate from default 9600 to 115200, 1 stop bit, 0 parity enter: "AT+UART=115200,1,0"

  Required for MIDI Accordion:
  - Setting baud rate to 115200
    AT+UART=115200,1,0
  Optional:
  - Setting device name (this is displayed under list of connected Bluetooth devices)
    AT+NAME=MIDI ACCORDION
  - Setting password
*/

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // Setting soft RX | TX pins

void setup()
{
  Serial.begin(9600);
  // This pin will pull the HC-05 pin 34 (KEY pin) HIGH to switch module to AT mode
  pinMode(9, OUTPUT);  
  digitalWrite(9, HIGH);
  Serial.println("Enter AT commands:");
  BTSerial.begin(38400);  // HC-05 baud rate in AT command mode
}

void loop()
{
  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
  {
    Serial.write(BTSerial.read());
  }

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
  {
    BTSerial.write(Serial.read());
  }
}
