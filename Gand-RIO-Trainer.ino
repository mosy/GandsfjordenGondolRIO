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
#include "PCF8574.h"  // https://github.com/xreef/PCF8574_library

PCF8574 pcf8574(0x20);
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
mb.addIsts(1,false,14);
mb.addCoil(1,false,8);
mb.addHreg(1,0,2);
mb.addIreg(1,0,2);
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

	for(int i=0;i<8;i++) 
		{
		pcf8574.pinMode(i, OUTPUT);
		}
	pcf8574.begin();

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


	mb.Ireg(1, analogRead(36));
	mb.Ireg(2, analogRead(39));
	dacWrite(25, mb.Hreg(1));
	dacWrite(26, mb.Hreg(2));

	pcf8574.digitalWrite(0, mb.Coil(1));
	pcf8574.digitalWrite(1, mb.Coil(2));
	pcf8574.digitalWrite(2, mb.Coil(3));
	pcf8574.digitalWrite(3, mb.Coil(4));
	pcf8574.digitalWrite(4, mb.Coil(5));
	pcf8574.digitalWrite(5, mb.Coil(6));
	pcf8574.digitalWrite(6, mb.Coil(7));
	pcf8574.digitalWrite(7, mb.Coil(8));
	
  Serial.println(mb.Ireg(1));
   delay(10);
}
