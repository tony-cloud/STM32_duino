/*
  dtostrf - Emulation for dtostrf function from avr-libc
  Copyright (c) 2013 Arduino.  All rights reserved.
  Written by Cristian Maglie <c.maglie@bug.st>

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
*/

/*
  * arm gcc does not support the %f format in sprintf.
  *	modify for stm32 arduino by huaweiwx@sina.com 2018.1.10
 */

#include <stdio.h>

/* 
char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
  char fmt[20];
  sprintf(fmt, "%%%d.%df", width, prec); 
  sprintf(sout, fmt, val);
  return sout;
}
*/

char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {

	char fmt[33];
	if(prec >9) prec = 9;
    sprintf(fmt, "%%%dd.%%0%dd",width-prec,prec);
	
 	int mul = 1;
	for(uint8_t i =0; i<prec; i++) mul *=10; /* powf(10, prec) */
	
	int32_t frac = (val - (int32_t)val) * mul;
	if(frac <0) frac = -frac;
	
	sprintf(sout, fmt, (int32_t)val, frac);
	return sout;
}


