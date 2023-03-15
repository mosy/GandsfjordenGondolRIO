/*
  Modbus-Arduino Example - Test Holding Register (Modbus IP ESP8266)
  Configure Holding Register (offset 100) with initial value 0xABCD
  You can get or set this holding register
  Original library
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino

  Current version
  (c)2017 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

//#ifdef ESP8266
// #include <ESP8266WiFi.h>
//#else //ESP32
 #include <WiFi.h>
//#endif
#include <ModbusIP_ESP8266.h>
#include "arduino_secrets.h"

//Modbus Registers Offsets
//Used Pins
const int DI1 = 34; //GPIO0
const int DI2 = 35; //GPIO0
const int DI3 = 32; //GPIO0
const int DI4 = 33; //GPIO0
const int DI5 = 27; //GPIO0
const int DI6 = 14; //GPIO0
const int DI7 = 12; //GPIO0
const int DI8 = 13; //GPIO0
const int DI9 = 15; //GPIO0
const int DI10 = 2; //GPIO0
const int DI11 = 4; //GPIO0
const int DI12 = 5; //GPIO0
const int DI13 = 18; //GPIO0
const int DI14 = 19; //GPIO0

// Modbus Registers Offsets
const int TEST_HREG = 1;


//ModbusIP object
ModbusIP mb;
  
void setup() {
  Serial.begin(115200);
 
  //WiFi.begin("your_ssid", "your_password");
  WiFi.begin(SECRET_SSID, SECRET_PASS);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  mb.server();
  mb.addHreg(TEST_HREG, 0x000A);
      //Set ledPin mode
    pinMode(DI1, INPUT);
    pinMode(DI2, INPUT);
    pinMode(DI3, INPUT_PULLUP);
    pinMode(DI4, INPUT_PULLUP);
    pinMode(DI5, INPUT_PULLUP);
    pinMode(DI6, INPUT_PULLUP);
    pinMode(DI7, INPUT_PULLUP);
    pinMode(DI8, INPUT_PULLUP);
    pinMode(DI9, INPUT_PULLUP);
    pinMode(DI10, INPUT_PULLUP);
    pinMode(DI11, INPUT_PULLUP);
    pinMode(DI12, INPUT_PULLUP);
    pinMode(DI13, INPUT_PULLUP);
    pinMode(DI14, INPUT_PULLUP);
    // Add SWITCH_ISTS register - Use addIsts() for digital inputs
	mb.addIsts(1,false,14);
	mb.addHreg(1, 0,2);
//	mb.addCoil(1,false,8);
}
 
void loop() {
   //Call once inside loop() - all magic here
   mb.task();
    //Attach DI1 to SWITCH_ISTS register
	mb.Ists(1, !digitalRead(DI1));
	mb.Ists(2, !digitalRead(DI2));
	mb.Ists(3, !digitalRead(DI3));
	mb.Ists(4, !digitalRead(DI4));
	mb.Ists(5, !digitalRead(DI5));
	mb.Ists(6, !digitalRead(DI6));
	mb.Ists(7, !digitalRead(DI7));
	mb.Ists(8, !digitalRead(DI8));
	mb.Ists(9, !digitalRead(DI9));
	mb.Ists(10, !digitalRead(DI10));
	mb.Ists(11, !digitalRead(DI11));
	mb.Ists(12, !digitalRead(DI12));
	mb.Ists(13, !digitalRead(DI13));
	mb.Ists(14, !digitalRead(DI14));


	mb.Hreg(1, analogRead(36));
	mb.Hreg(2, analogRead(39));
	
/*
        potValue = analogRead(potPin);
	digitalWrite(DO1, mb.Coil(1));
	digitalWrite(DO2, mb.Coil(2));
	digitalWrite(DO3, mb.Coil(3));
	digitalWrite(DO4, mb.Coil(4));
	digitalWrite(DO5, mb.Coil(5));
	digitalWrite(DO6, mb.Coil(6));
	digitalWrite(DO7, mb.Coil(7));
	digitalWrite(DO8, mb.Coil(8));
	*/
   delay(10);

}
