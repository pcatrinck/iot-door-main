/*

  for: rfid reading support library
  author: Patrick Dias Catrinck
  date: 08/29/23

*/

#include "Arduino.h"
#include "printh.h"

//  Print hex to serial
void prt_h::printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");  //format output, puts a 0 if it is a single digit hex number
    Serial.print(buffer[i], HEX);
  }
}

//  Print decimal to serial
void prt_h::printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");  //format output, puts a 0 if it is a single digit dec number
    Serial.print(buffer[i], DEC);
  }
}

// Format a string corresponding to card's uid.
String prt_h::getUIDAsString(byte *uidBytes, byte uidSize) {
  String uidStr = "";
  for (byte i = 0; i < uidSize; i++) {
    if (uidBytes[i] < 0x10) {
      uidStr += "0";
    }
    uidStr += String(uidBytes[i], HEX);
  }
  return uidStr;
}