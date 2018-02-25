/*
  LED.cpp - LED library
  huaweiwx@sina.com 2017.  All right reserved.

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
#include "LED.h"

#ifdef LED_BUILTIN
LEDClass<LED_BUILTIN, bitRead(LED_MASK,0)>Led;
#endif

#ifdef LED1_BUILTIN
LEDClass<LED1_BUILTIN, bitRead(LED_MASK,1)>Led1;
#endif

#ifdef LED2_BUILTIN
LEDClass<LED2_BUILTIN, bitRead(LED_MASK,2)>Led2;
#endif

#ifdef LED3_BUILTIN
LEDClass<LED3_BUILTIN, bitRead(LED_MASK,3)>Led3;
#endif

#ifdef LED4_BUILTIN
LEDClass<LED4_BUILTIN, bitRead(LED_MASK,4)>Led4;
#endif

#ifdef LED5_BUILTIN
LEDClass<LED5_BUILTIN, bitRead(LED_MASK,5)>Led5;
#endif

#ifdef LED6_BUILTIN
LEDClass<LED6_BUILTIN, bitRead(LED_MASK,6)>Led6;
#endif

#ifdef LED7_BUILTIN
LEDClass<LED7_BUILTIN, bitRead(LED_MASK,7)>Led7;
#endif

