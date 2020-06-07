#include "mylib.h"

bool toBool(String s){
  if(s.equals("true")||s.equals("1")||s.equals("TRUE"))return true;
  if(s.equals("false")||s.equals("0")||s.equals("FALSE"))return false;
  return false;
}

uint32_t hexColorToInt(String s){
    //#ff00ee
    // 012345
    if (s.equals("null"))
    return 0;
    s = s.substring(1);
    s.toLowerCase();
    String hex="0123456789abcdef";

    uint8_t r = (hex.indexOf(s.charAt(0)))*16+hex.indexOf(s.charAt(1));
    uint8_t g = (hex.indexOf(s.charAt(2)))*16+hex.indexOf(s.charAt(3));
    uint8_t b = (hex.indexOf(s.charAt(4)))*16+hex.indexOf(s.charAt(5));
    return getColor(r,g,b);
}