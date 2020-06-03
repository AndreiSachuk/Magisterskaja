#ifndef MYLIB_H
#define MYLIB_H

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
bool toBool(String s){
  if(s.equals("true")||s.equals("1")||s.equals("TRUE"))return true;
  if(s.equals("false")||s.equals("0")||s.equals("FALSE"))return false;
  return false;
}

#endif