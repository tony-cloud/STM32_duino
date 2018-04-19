/*
  EXTEEPROM.cpp - EXTEEPROM library
  Copyright (c) 2006 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  modify by huawewi huaweiwx@sina.com 2017.2.18
*/

/******************************************************************************
 * Includes
 ******************************************************************************/
 
#include "Arduino.h"
#include "at24cxx.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/

/******************************************************************************
 * Constructors
 ******************************************************************************/

/******************************************************************************
 * User API
 ******************************************************************************/
EXTEEPROM::EXTEEPROM(uint8_t sda, uint8_t scl, uint8_t delay):TwoWire(sda,scl,delay){
	 TwoWire::begin();
}

void EXTEEPROM::begin(uint8_t devAdr, uint16_t devType)
{
	 this->_devAdr  = devAdr;
     this->_devType = devType;
}

uint8_t EXTEEPROM::read(uint16_t address)
{
	  uint8_t reading; 
	  TwoWire::beginTransmission(_devAdr);    // transmit to device #80(0x50)

      if(_devType > AT24C16)	              //for 16bit address 
		 TwoWire::write(byte(address>>8));     // high address
      TwoWire::write(byte(address & 0xff));   //low address
      TwoWire::endTransmission(); 			// stop transmitting
      			       
      TwoWire::requestFrom(_devAdr, 1);    	// request 1 bytes from slave device #80(0x50)      
      delay(2);
      // receive reading from sensor
      if( TwoWire::available() >=1)    	// if two bytes were received      
        reading = TwoWire::read();  		// receive high byte (overwrites previous reading)                       
      return reading; 
}

void EXTEEPROM::write(uint16_t address, uint8_t value)
{
	TwoWire::beginTransmission(_devAdr); // transmit to device #80(0x50)

    if(_devType > AT24C16)	  
		TwoWire::write(address>>8); 		// high address
    TwoWire::write(address & 0xff);  			// low address
	
    TwoWire::write(value);  				// data
    TwoWire::endTransmission();
}

EXTEEPROM:: ~EXTEEPROM(){};



//EXTEEPROMClass EXTEEPROM;
