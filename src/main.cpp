#include <Arduino.h>
#include "JeeUI2.h" 
#include "mylib.h"
#include "leds_stat.h"
#include "modes.h"
#include <tcs3200.h> 
#include <WiFi.h> 
#include <analogWrite.h>
#include <SoftwareSerial.h>
#include "interface.h"  

#define LED_PIN 2
#define RX 15                        
#define TX 4                        


SoftwareSerial swSer(TX, RX, false, 256);
byte data[5];  
jeeui2 jee; 

void mqttCallback(String topic, String payload);
void onConnect();
void Radio();
void led(bool);
void sendData();
void led_single(int);
void man_mode(String);
void showRgb(uint8_t, uint8_t, uint8_t);

void setup() {
	DMX::Initialize();
	lcd.begin(16, 4);
	lcd.setCursor(0,1);
	lcd.print("STARTING SYSTEM");
	lcd.setCursor(3,2);
	lcd.print("STARTING AP");
	analogWriteResolution(LED_PIN, 12);
	Serial.begin(115200);
	swSer.begin(9600);
	WiFi.softAPConfig(IPAddress(192,168,8,100), IPAddress(192,168,8,1), IPAddress(255,255,255,0));
	jee.mqtt("mqtt.by", 1883, "developer", "8kjdtz6d", mqttCallback, onConnect,  true); 
	jee.udp(); 
	jee.led(10, false); 
	jee.ap(5000); 
	parameters(); 
	jee.ui(interface); 
	jee.update(update); 
	jee.begin(true); 
	update(); 
}

void loop() {
	jee.handle(); // цикл, необходимый фреймворку
	analogWrite(LED_PIN, Single);
	EXEC_TIMER_SET(100,showRgb(Red, Green, Blue); delay(10););
	EXEC_TIMER_SET(100,Radio();)
	WORK(MODE);
}



void Radio() {                       
    	data[0] = Red;
		data[1] = Green;
		data[2] = Blue;
		data[3] = Single;         
		swSer.write(0xAA);  
		swSer.write(0xBB);            
		swSer.write(data, sizeof(data));
		swSer.write('\n');        
}                                   

void onConnect(){ 
  	Serial.println("Connected to mqtt");
}

void mqttCallback(String topic, String payload){ 
  	Serial.println("Message [" + topic + " - " + payload + "] ");
}


