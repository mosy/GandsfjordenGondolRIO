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
const int DI1 = 18; //GPIO0
const int DI2 = 21; //GPIO0
const int DI3 = 33; //GPIO0
const int DI4 = 34; //GPIO0
const int DI5 = 35; //GPIO0
const int DI6 = 36; //GPIO0
const int DI7 = 37; //GPIO0
const int DI8 = 38; //GPIO0
const int DI9 = 39; //GPIO0
const int DI10 = 40; //GPIO0

const int AI1 = 17; //GPIO0
const int AI2 = 16; //GPIO0


const int DO1 = 11; //GPIO0
const int DO2 = 10; //GPIO0
const int DO3 = 9; //GPIO0
const int DO4 = 8; //GPIO0


const int MCW = 2; //GPIO0
const int MCCW = 3; //GPIO0

// Modbus Registers Offsets
const int TEST_HREG = 1;

IPAddress staticIP(192, 168, 0, 201);
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
mb.addIsts(1,false,10);
mb.addCoil(1,false,4);
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

	pinMode(DO1, OUTPUT);
	pinMode(DO2, OUTPUT);
	pinMode(DO3, OUTPUT);
	pinMode(DO4, OUTPUT);
	pinMode(15, OUTPUT);

	//pinMode(MCW, OUTPUT);
	//pinMode(MCCW, OUTPUT);
	ledcSetup(0, 1000, 8);
	ledcSetup(1, 1000, 8);
	ledcAttachPin(MCW, 0);
	ledcAttachPin(MCCW, 1);

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

	mb.Ireg(1, analogRead(AI1));
	mb.Ireg(2, analogRead(AI2));

	digitalWrite(DO1, mb.Coil(1));
	digitalWrite(DO2, mb.Coil(2));
	digitalWrite(DO3, mb.Coil(3));
	digitalWrite(DO4, mb.Coil(4));
	
	ledcWrite(0, mb.Hreg(1));
	ledcWrite(1, mb.Hreg(2));
	if (WiFi.status() == WL_CONNECTED)
		digitalWrite(15, true);
		else 
		digitalWrite(15, false);
	
//  Serial.println(mb.Hreg(1));
//  Serial.println(mb.Hreg(2));
}
