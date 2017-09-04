// --------------------------------------
//  at24cxx_rw_wire.ino
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    http://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
//
// modify by huawei huaweiwx@sina.com 2017.2.21
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//
#include <Wire.h>

TwoWire mywire(I2C1);

//my vct6 board config:
#define EE_SCL PE5 //PB6
#define EE_SDA PE6 //PB7
#define   EE_DISK0 0x50    //Address of AT24LC512 A2A1A0=000
//#define EE_DISK1 0x51    //Address of AT24LCXX  A2A1A0=001
//#define EE_DISK2 0x52      //Address of FM24LC04  A2A1  =010 page0
//#define EE_DISK3 0x53      //Address of FM24LC04  A2A1  =011 page1

uint8_t adrlen;

void setup() {
  Serial1.begin(115200);
  mywire.begin();
  Serial1.println("\nAT24CXX RW");
 }

void loop() {
#ifdef EE_DISK0
  adrlen = 16;
  for (uint16_t i = 0; i < 16; i++) {
    for (uint16_t j = 0; j < 16; j++) {
      Serial1 << _HEX(readEEPROM(EE_DISK0, i * 16 + j)) << "  ";
    }
    Serial1 << "\n";
  }
  Serial1 << "disk @000 ok\n\n";
#endif

#ifdef EE_DISK1
  adrlen = 16;
  for (uint16_t i = 0; i < 16; i++) {
    for (uint16_t j = 0; j < 16; j++) {
      Serial1 << _HEX(readEEPROM(EE_DISK1, i * 16 + j)) << " ";
    }
    Serial1 << "\n";
  }
  Serial1 << "disk @001 ok\n\n";
#endif

#ifdef EE_DISK2
  adrlen = 8;
  for (uint16_t i = 0; i < 16; i++) {
    for (uint16_t j = 0; j < 16; j++) {
      Serial1 << _HEX(readEEPROM(EE_DISK2, i * 16 + j)) << "  ";
    }
    Serial1 << "\n";
  }
  Serial1 << "disk @010 ok\n\n";
#endif

#ifdef EE_DISK3
  adrlen = 8;
  for (uint16_t i = 0; i < 16; i++) {
    for (uint16_t j = 0; j < 16; j++) {
      Serial1 << _HEX(readEEPROM(EE_DISK3, i * 16 + j)) << "  ";
    }
    Serial1 << "\n";
  }
  Serial1 << "\ndisk @011 ok\n";
#endif
  delay(5000);           // wait 5 seconds for next scan
}

void writeEEPROM(uint16_t dev, unsigned int eeaddress, byte data )
{
  mywire.beginTransmission(dev);
  if(adrlen > 8)
     mywire.write((int)(eeaddress >> 8));   // MSB
  mywire.write((int)(eeaddress & 0xFF)); // LSB
  mywire.write(data);
  mywire.endTransmission();

  delay(5);
}

byte readEEPROM(uint16_t dev, uint16_t eeaddress )
{
  byte rdata = 0xFF;

  mywire.beginTransmission(dev);
  if(adrlen > 8)
      mywire.write((int)(eeaddress >> 8));   // MSB
  mywire.write((int)(eeaddress & 0xFF)); // LSB
  mywire.endTransmission();

  mywire.requestFrom(dev, 1);

  //  if (mywire.available())
  rdata = mywire.read();
  return rdata;
}


