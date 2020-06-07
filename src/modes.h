#ifndef MODES_H
#define MODES_H

#include <Arduino.h>
#include "interface.h"
#include "mylib.h"
#include <tcs3200.h>
#include <dmx.h>


void man_mode(String k){
    if (k.equals("Resistors")){
        int a = analogRead(25);
        int b = analogRead(26);
        int c = analogRead(27);
        int d = analogRead(33);
        Red = map(a, 0, 4095, 0, 255);
        Green = map(b, 0, 4095, 0, 255);
        Blue = map(c, 0, 4095, 0, 255);
        Single = map(d, 0, 4095, 0, 255);    
        }
    if (k.equals("Color_sensor")){
        EXEC_TIMER_SET(300, 
        {tcs3200 tcs(27, 14, 26, 25, 13);
        Red = tcs.colorRead('r');
        Green = tcs.colorRead('g');
        Blue = tcs.colorRead('b');
        };);
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
        uint32_t lcolor = hexColorToInt(Color);
        Red = GET_LAST_CHANGED(uint8_t, jee.param("Red").toInt(), getColorR(lcolor))
        Green = GET_LAST_CHANGED(uint8_t, jee.param("Green").toInt(), getColorG(lcolor))
        Blue = GET_LAST_CHANGED(uint8_t, jee.param("Blue").toInt(), getColorB(lcolor))
        Color = jee.param("Color");
}

void WORK(String k){
    if (k.equals("MANUAL")){
        man_mode(MANUAL_MODE);
      
    } 
    else if (k.equals("DMX")){
        DMX();
    }
    else if (k.equals("MQTT_serv")){
        MQTT();
        EXEC_TIMER_SET(200, update(););
    }
    else
    {
        EXEC_TIMER_SET(1000, Serial.println("not connection"););

    }
    
}

#endif