/*

  for: rfid reading support library
  author: Patrick Dias Catrinck
  date: 08/29/23

*/


#ifndef print_help
#define print_help

#include "Arduino.h"

class prt_h
{
    public:
      void printHex(byte *buffer, byte bufferSize);
      void printDec(byte *buffer, byte bufferSize);
      String getUIDAsString(byte *uidBytes, byte uidSize);
};

#endif











