#include "mylib.h"

bool toBool(String s){
  if(s.equals("true")||s.equals("1")||s.equals("TRUE"))return true;
  if(s.equals("false")||s.equals("0")||s.equals("FALSE"))return false;
  return false;
}