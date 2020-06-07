#ifndef MYLIB_H
#define MYLIB_H

#include <Arduino.h>

#define COMBINE1(X,Y) X##Y  // helper macro
#define COMBINE(X,Y) COMBINE1(X,Y)
#define EXEC_TIMER_SET_NM(Tname,Tafter,Tcode) \
{                                             \
  static uint32_t Tname = millis()+Tafter;    \
  if(Tname < millis()){                       \
    Tname = millis()+Tafter;                  \
    {Tcode}                                   \
  }                                           \
}
#define EXEC_TIMER_SET(Tafter,Tcode) EXEC_TIMER_SET_NM(COMBINE(__FUNCTION__,__LINE__),Tafter,Tcode)


//Конвертнуть из строки в бул
bool toBool(String s);


//Конвертим #****** в цвета
#define getColor(r,g,b) (r|g<<8|b<<16)
#define getColorR(v) (v&0xFF)
#define getColorG(v) ((v>>8)&0xFF)
#define getColorB(v) ((v>>16)&0xFF)

uint32_t hexColorToInt(String s);

#define LOG_DEBUG_VARIABLE(VAR_NAME) {Serial.println(String(#VAR_NAME)+":"+String(VAR_NAME));}

#define GET_LAST_CHANGED(TYPE_NAME, IN_X1, IN_X2)\
([](TYPE_NAME inX1, TYPE_NAME inX2) -> TYPE_NAME {\
  static TYPE_NAME x1 = inX1;\
  static TYPE_NAME x2 = inX2;\
  static TYPE_NAME def = inX1;\
\
  if(x1 != inX1){\
    def = inX1;\
    x1 = inX1;\
    return inX1;\
  }\
  if(x2 != inX2){\
    def = inX2;\
    x2 = inX2;\
    return inX2;\
  }\
\
  return def;\
})(IN_X1, IN_X2);

#endif