#ifndef INTERFACE_H
#define INTERFACE_H

#include "JeeUI2.h" 
extern jeeui2 jee;
#include <Arduino.h>
bool toBool(String);
void parameters();
void update();
void interface();
uint32_t hexColorToInt(String);

extern uint8_t Red;
extern uint8_t Green;
extern uint8_t Blue;
extern int Single;
extern String MANUAL_MODE;
extern String MODE;
extern String Color;

extern uint8_t DMX_ch_r;
extern uint8_t DMX_ch_g;
extern uint8_t DMX_ch_b;
extern uint8_t DMX_ch_s;

#endif