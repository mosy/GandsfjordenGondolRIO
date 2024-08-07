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
//#include "PCF8574.h"  // https://github.com/xreef/PCF8574_library

//PCF8574 pcf8574(0x20);
//Modbus Registers Offsets
//Used Pins
const int DI1 = 38; //GPIO0
const int DI2 = 37; //GPIO0
const int DI3 = 36; //GPIO0
const int DI4 = 35; //GPIO0
const int DI5 = 33; //GPIO0
const int DI6 = 34; //GPIO0
const int DI7 = 18; //GPIO0
const int DI8 = 21; //GPIO0
const int DI9 = 16; //GPIO0
const int DI10 = 17; //GPIO0

const int AI1 = 13; //GPIO0
const int AI2 = 14; //GPIO0

const int PT1 = 40; //GPIO0
const int PT2 = 39; //GPIO0

const int DO1 = 1; //GPIO0
const int DO2 = 2; //GPIO0
const int DO3 = 3; //GPIO0
const int DO4 = 4; //GPIO0
const int DO5 = 5; //GPIO0
const int DO6 = 6; //GPIO0
const int DO7m = 7; //GPIO0
const int DO7p = 9; //GPIO0
const int DO8m = 8; //GPIO0
const int DO8p = 11; //GPIO0
const int DO9m = 10; //GPIO0
const int DO9p = 12; //GPIO0


//const int MCW = 2; //GPIO0
//const int MCCW = 3; //GPIO0

// Modbus Registers Offsets
const int TEST_HREG = 1;

IPAddress staticIP(192, 168, 0, 207);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress dns(192,168,0,1);   //optional
//IPAddress secondaryDNS(8, 8, 4, 4); //optional
//ModbusIP object
ModbusIP mb;
  
void setup() {
  Serial.begin(115200);
 
 if (WiFi.config(staticIP, gateway, subnet, dns, dns) == false)
    Serial.println("Configuration failed.");
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
mb.addIsts(1,false,11);
mb.addCoil(1,false,10);
mb.addHreg(1,0,2);
mb.addIreg(1,0,2);




//Set ledPin mode
	pinMode(DI1, INPUT_PULLUP);
	pinMode(DI2, INPUT_PULLUP);
	pinMode(DI3, INPUT_PULLUP);
	pinMode(DI4, INPUT_PULLUP);
	pinMode(DI5, INPUT_PULLUP);
	pinMode(DI6, INPUT_PULLUP);
	pinMode(DI7, INPUT_PULLUP);
	pinMode(DI8, INPUT_PULLUP);
	pinMode(DI9, INPUT_PULLUP);
	pinMode(DI10, INPUT_PULLUP);
	
	pinMode(AI1, INPUT);
	pinMode(AI2, INPUT);

	pinMode(PT1, INPUT);
	pinMode(PT2, INPUT);

	pinMode(DO1, OUTPUT);
	pinMode(DO2, OUTPUT);
	pinMode(DO3, OUTPUT);
	pinMode(DO4, OUTPUT);
	pinMode(DO5, OUTPUT);
	pinMode(DO6, OUTPUT);
	pinMode(DO7m, OUTPUT);
	pinMode(DO7p, OUTPUT);
	pinMode(DO8m, OUTPUT);
	pinMode(DO8p, OUTPUT);
	pinMode(DO9m, OUTPUT);
	pinMode(DO9p, OUTPUT);
	pinMode(15, OUTPUT);

	//pinMode(MCW, OUTPUT);
	//pinMode(MCCW, OUTPUT);
	ledcAttach(DO9m, 1000, 8);
	ledcAttach(DO9p, 1000, 8);

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
	mb.Ists(11, digitalRead(PT2));

	mb.Ireg(1, analogRead(AI1));
	mb.Ireg(2, analogRead(AI2));
//	mb.Ireg(3, analogRead(PT1));
//	mb.Ireg(4, analogRead(PT2));

	digitalWrite(DO1, !mb.Coil(1));
	digitalWrite(DO2, !mb.Coil(2));
	digitalWrite(DO3, !mb.Coil(3));
	digitalWrite(DO4, !mb.Coil(4));
	digitalWrite(DO5, !mb.Coil(5));
	digitalWrite(DO6, !mb.Coil(6));
	digitalWrite(DO7p, mb.Coil(7));
	digitalWrite(DO7m, mb.Coil(8));
	digitalWrite(DO8p, mb.Coil(9));
	digitalWrite(DO8m, mb.Coil(10));
//	digitalWrite(DO9m, mb.Coil(11));
//	digitalWrite(DO9p, mb.Coil(12));
	
	ledcWrite(DO9m, mb.Hreg(1));
	ledcWrite(DO9p, mb.Hreg(2));
	if (WiFi.status() == WL_CONNECTED)
		digitalWrite(15, true);
		else 
		digitalWrite(15, false);
	
//  Serial.println(mb.Hreg(1));
//  Serial.println(mb.Hreg(2));
}
