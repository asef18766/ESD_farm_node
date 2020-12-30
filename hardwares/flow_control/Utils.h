#pragma once
#include <Arduino.h>
inline bool DelayAsync(unsigned long &time_buf, int ms)
{
   unsigned long cur = millis();
   if (cur >= time_buf + ms)
   {
      time_buf = cur;
      return true;
   }
   return false;
}
