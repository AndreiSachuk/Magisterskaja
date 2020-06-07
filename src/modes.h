#ifndef MODES_H
#define MODES_H

#include <Arduino.h>
#include "interface.h"
#include "mylib.h"
#include <tcs3200.h>
#include <dmx.h>


void man_mode(String k){
    if (k=="Resistors"){
        int a = analogRead(25);
        int b = analogRead(26);
        int c = analogRead(27);
        int d = analogRead(33);
        Red = map(a, 0, 4095, 0, 255);
        Green = map(b, 0, 4095, 0, 255);
        Blue = map(c, 0, 4095, 0, 255);
        Single = map(d, 0, 4095, 0, 255);    
        }
    if (k=="Color_sensor"){
        EXEC_TIMER_SET(1000, 
        {tcs3200 tcs(27, 14, 26, 25, 13);
        Red = tcs.colorRead('r');
        Green = tcs.colorRead('g');
        Blue = tcs.colorRead('b');
        jee.var("Red", String(Red)); 
        jee.var("Green", String(Green)); 
        jee.var("Blue", String(Blue)); };);
        EXEC_TIMER_SET(500,Serial.println(String(Red)+" "+String(Green)+" "+String(Blue) ););
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

void WORK(String k){
    if (k=="MANUAL"){
        man_mode(MANUAL_MODE);
        EXEC_TIMER_SET(200,update(););
    } else if (k=="DMX"){
        //DMX();
        EXEC_TIMER_SET(200,update(););
    }
    else
    {
        EXEC_TIMER_SET(1000, Serial.println("not connection"););

    }
    
}

#endif