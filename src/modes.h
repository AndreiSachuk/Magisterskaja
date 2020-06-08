#ifndef MODES_H
#define MODES_H

#include <Arduino.h>
#include "interface.h"
#include "mylib.h"
#include <tcs3200.h>
#include <dmx.h>
#include <LiquidCrystal.h>
#include <WiFi.h>

LiquidCrystal lcd(23, 22, 21, 19, 18, 5);



void man_mode(String k){
    if (k.equals("Resistors")){
        int a = analogRead(34);
        int b = analogRead(35);
        int c = analogRead(32);
        int d = analogRead(33);
        Red = map(a, 0, 4095, 0, 255);
        Green = map(b, 0, 4095, 0, 255);
        Blue = map(c, 0, 4095, 0, 255);
        Single = map(d, 0, 4095, 0, 255);
        }
    else if (k.equals("Color_sensor")){
        EXEC_TIMER_SET(300, 
        {tcs3200 tcs(27, 14, 26, 25, 13);
        Red = tcs.colorRead('r');
        Green = tcs.colorRead('g');
        Blue = tcs.colorRead('b');
        Single = 0;
        });
}
}

void DMX(){
if(DMX::IsHealthy()){
            Red = DMX::Read(DMX_ch_r);
            Green = DMX::Read(DMX_ch_g);
            Blue = DMX::Read(DMX_ch_b);
            Single = DMX::Read(DMX_ch_s);
        } else {Serial.print("DMX READ FAIL");}
}

void MQTT(){
        Single = jee.param("Single").toInt();
        Color = jee.param("Color");
        uint32_t lcolor = hexColorToInt(Color);
        Red = GET_LAST_CHANGED(uint8_t, jee.param("Red").toInt(), getColorR(lcolor))
        Green = GET_LAST_CHANGED(uint8_t, jee.param("Green").toInt(), getColorG(lcolor))
        Blue = GET_LAST_CHANGED(uint8_t, jee.param("Blue").toInt(), getColorB(lcolor))

}

void WORK(String k){
    if (k.equals("MANUAL")){
        if (MANUAL_MODE.equals(""))
        {
        EXEC_TIMER_SET(300, lcd.clear(););
        lcd.setCursor(2,0);
        lcd.print("MODE: MANUAL");
        lcd.setCursor(4,1);
        lcd.print("PLEASE");
        lcd.setCursor(2,2);
        lcd.print("SELECT OPTION");
        } else 
            {
            EXEC_TIMER_SET(299, lcd.clear(););
            lcd.setCursor(2,0);
            lcd.print("MODE: MANUAL");
            lcd.setCursor(4,1);
            lcd.print("OPTION:");
            lcd.setCursor(0,2);
            lcd.print(MANUAL_MODE);
            man_mode(MANUAL_MODE);
            EXEC_TIMER_SET(300,
                {
                lcd.setCursor(0,3);
                lcd.print("r"+String(Red));    
                lcd.setCursor(4,3);
                lcd.print("g"+String(Green));   
                lcd.setCursor(8,3);
                lcd.print("b"+String(Blue)); 
                lcd.setCursor(12,3);
                lcd.print("s"+String(Single));        
                }   );  
            } 
    }
    else if (k.equals("DMX")){
        DMX();
        EXEC_TIMER_SET(300, lcd.clear(););
            lcd.setCursor(3,0);
            lcd.print("MODE: DMX");
            lcd.setCursor(2,1);
            lcd.print("CHANNEL/VALUE");
            lcd.setCursor(0,2);
            lcd.print("r"+String(DMX_ch_r));    
            lcd.setCursor(4,2);
            lcd.print("/"+String(Red));   
            lcd.setCursor(8,2);
            lcd.print("g"+String(DMX_ch_g)); 
            lcd.setCursor(12,2);
            lcd.print("/"+String(Green));    
            lcd.setCursor(0,3);
            lcd.print("b"+String(DMX_ch_b));    
            lcd.setCursor(4,3);
            lcd.print("/"+String(Blue));   
            lcd.setCursor(8,3);
            lcd.print("s"+String(DMX_ch_s)); 
            lcd.setCursor(12,3);
            lcd.print("/"+String(Single)); 
    }
    else if (k.equals("MQTT_serv")){
        MQTT();
            EXEC_TIMER_SET(300, lcd.clear(););
            lcd.setCursor(3,0);
            lcd.print("MODE: WEB");
            lcd.setCursor(0,1);
            lcd.print("RED:");
            lcd.print(String(Red));    
            lcd.setCursor(8,1);
            lcd.print("GRN:");
            lcd.print(String(Green));
            lcd.setCursor(4,2);
            lcd.print("BLUE: ");
            lcd.print(String(Blue));
            lcd.setCursor(3,3);
            lcd.print("SINGLE: ");
            lcd.print(String(Single));
        EXEC_TIMER_SET(200, update(););
    }
    else if (k.equals(" ")){
        EXEC_TIMER_SET(1000000, lcd.clear(););
        lcd.setCursor(1,0);
        lcd.print("AP: "+ap_ssid);
        lcd.setCursor(0,1);
        lcd.print("IP:192.168.8.100");
        lcd.setCursor(1,2);
        lcd.print("PLEASE CONNECT");
        lcd.setCursor(0,3);
        lcd.print("AND SELECT MODE");
        EXEC_TIMER_SET(1000, Serial.println("SELECT MODE"););
    }
       
}

#endif