/*
  stm32flash - Open Source ST STM32 flash program for *nix
  Copyright (C) 2010 Geoffrey McRae <geoff@spacevs.com>
  Copyright (C) 2014-2015 Antonio Borneo <borneo.antonio@gmail.com>

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <Arduino.h>
#include "dev_table.h"
#include "chipInfo.h"

#define SZ_128	0x00000080
#define SZ_256	0x00000100
#define SZ_1K	0x00000400
#define SZ_2K	0x00000800
#define SZ_16K	0x00004000
#define SZ_32K	0x00008000
#define SZ_64K	0x00010000
#define SZ_128K	0x00020000
#define SZ_256K	0x00040000

//for appAdminister
#if defined(STM32F1)  //F0/L0/F1/L1/F3
#  if (FLASH_BANK1_END >  0x0801FFFFU) /*512k flash 64k ram for xC/xE*/
#    ifdef GD32F10X
        const  uint16_t appCodeSegAddr[] = {3,64,2*64,3*64,};
#    else
        const  uint16_t appCodeSegAddr[] = {7,64, 2*64,3*64,4*64,5*64,6*64,7*64,};
#    endif
#  else  /*128k flash 20k ram for x8/xB*/
        const uint16_t appCodeSegAddr[] =  {3,16,3*16,5*16,};
#  endif
#elif defined(STM32F207ZG)
        const uint16_t appCodeSegAddr[] =  {7,128,2*128,3*128,4*128,5*128,6*26,7*128};
#elif defined(STM32F401CC)
        const uint16_t appCodeSegAddr[] =  {2,64,2*64};
#elif defined(STM32F401RE)||defined(STM32F401ZE)||defined(STM32F407ZE)||defined(STM32F407VE)
        const uint16_t appCodeSegAddr[] =  {3,128,2*128,3*128};
#elif defined(STM32F407ZG)||defined(STM32F407VG)
        const uint16_t appCodeSegAddr[] =  {7,128,2*128,3*128,4*128,5*128,6*26,7*128};
#elif defined(STM32F746IG)
        const uint16_t appCodeSegAddr[] =  {3,256,2*256,3*256};
#elif defined(STM32F767ZI)
        const uint16_t appCodeSegAddr[] =  {7,256,2*256,3*256,4*256,5*256,6*26,7*256};
#elif defined(STM32L476RG)
        const uint16_t appCodeSegAddr[] =  {7,128,2*128,3*128,4*128,5*128,6*26,7*128};
#else /*f4/7*/

//# error "please add me!"

#endif

/*
 * Page-size for page-by-page flash erase.
 * Arrays are zero terminated; last non-zero value is automatically repeated
 */

/* fixed size pages */
static uint32_t p_128[] = { SZ_128, 0 };
static uint32_t p_256[] = { SZ_256, 0 };
static uint32_t p_1k[]  = { SZ_1K,  0 };
static uint32_t p_2k[]  = { SZ_2K,  0 };
/* F2 and F4 page size */
static uint32_t f2f4[]  = { SZ_16K, SZ_16K, SZ_16K, SZ_16K, SZ_64K, SZ_128K, 0 };
/* F4 dual bank page size */
static uint32_t f4db[]  = {
	SZ_16K, SZ_16K, SZ_16K, SZ_16K, SZ_64K, SZ_128K, SZ_128K, SZ_128K,
	SZ_16K, SZ_16K, SZ_16K, SZ_16K, SZ_64K, SZ_128K, 0
};

/* F7 page size */
static uint32_t f7[]    = { SZ_32K, SZ_32K, SZ_32K, SZ_32K, SZ_128K, SZ_256K, 0 };


/*
 * Device table, corresponds to the "Bootloader device-dependant parameters"
 * table in ST document AN2606.
 * Note that the option bytes upper range is inclusive!
 */
const stm32_dev_t stm32_devices[] = {
	/* ID     "name"                              SRAM-address-range      FLASH-address-range    PPS  PSize   Option-byte-addr-range  System-mem-addr-range   Flags */
	/* F0 */
#ifdef USE_STM32NAME
	{0x440, "STM32F030x8/F05xxx"              , 0x20000800, 0x20002000, 0x08000000, 0x08010000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFEC00, 0x1FFFF800, 0},
	{0x442, "STM32F030xC/F09xxx"              , 0x20001800, 0x20008000, 0x08000000, 0x08040000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, F_OBLL},
	{0x444, "STM32F03xx4/6"                   , 0x20000800, 0x20001000, 0x08000000, 0x08008000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFEC00, 0x1FFFF800, 0},
	{0x445, "STM32F04xxx/F070x6"              , 0x20001800, 0x20001800, 0x08000000, 0x08008000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFC400, 0x1FFFF800, 0},
	{0x448, "STM32F070xB/F071xx/F72xx"        , 0x20001800, 0x20004000, 0x08000000, 0x08020000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFC800, 0x1FFFF800, 0},
	/* F1 */
	{0x412, "STM32F10xxx Low-density"         , 0x20000200, 0x20002800, 0x08000000, 0x08008000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x410, "STM32F10xxx Medium-density"      , 0x20000200, 0x20005000, 0x08000000, 0x08020000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x414, "STM32F10xxx High-density"        , 0x20000200, 0x20010000, 0x08000000, 0x08080000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x420, "STM32F10xxx Medium-density VL"   , 0x20000200, 0x20002000, 0x08000000, 0x08020000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x428, "STM32F10xxx High-density VL"     , 0x20000200, 0x20008000, 0x08000000, 0x08080000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x418, "STM32F105xx/F107xx"              , 0x20001000, 0x20010000, 0x08000000, 0x08040000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFB000, 0x1FFFF800, 0},
	{0x430, "STM32F10xxx XL-density"          , 0x20000800, 0x20018000, 0x08000000, 0x08100000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFE000, 0x1FFFF800, 0},
	/* F2 */
	{0x411, "STM32F2xxxx"                     , 0x20002000, 0x20020000, 0x08000000, 0x08100000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	/* F3 */
	{0x432, "STM32F373xx/F378xx"              , 0x20001400, 0x20008000, 0x08000000, 0x08040000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, 0},
	{0x422, "STM32F302xB(C)/F303xB(C)/F358xx" , 0x20001400, 0x2000A000, 0x08000000, 0x08040000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, 0},
	{0x439, "STM32F301xx/F302x4(6/8)/F318xx"  , 0x20001800, 0x20004000, 0x08000000, 0x08010000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, 0},
	{0x438, "STM32F303x4(6/8)/F334xx/F328xx"  , 0x20001800, 0x20003000, 0x08000000, 0x08010000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, 0},
	{0x446, "STM32F302xD(E)/F303xD(E)/F398xx" , 0x20001800, 0x20010000, 0x08000000, 0x08080000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, 0},
	/* F4 */
	{0x413, "STM32F40xxx/41xxx"               , 0x20003000, 0x20020000, 0x08000000, 0x08100000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x419, "STM32F42xxx/43xxx"               , 0x20003000, 0x20030000, 0x08000000, 0x08200000,  1, f4db  , 0x1FFEC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x423, "STM32F401xB(C)"                  , 0x20003000, 0x20010000, 0x08000000, 0x08040000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x433, "STM32F401xD(E)"                  , 0x20003000, 0x20018000, 0x08000000, 0x08080000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x458, "STM32F410xx"                     , 0x20003000, 0x20008000, 0x08000000, 0x08020000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x431, "STM32F411xx"                     , 0x20003000, 0x20020000, 0x08000000, 0x08080000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x441, "STM32F412xx"                     , 0x20003000, 0x20020000, 0x08000000, 0x08100000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x463, "STM32F413xx"                     , 0x20003000, 0x20050000, 0x08000000, 0x08180000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x421, "STM32F446xx"                     , 0x20003000, 0x20020000, 0x08000000, 0x08080000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x434, "STM32F469xx"                     , 0x20003000, 0x20060000, 0x08000000, 0x08200000,  1, f4db  , 0x1FFEC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	/* F7 */
	{0x452, "STM32F72xxx/73xxx"               , 0x20004000, 0x20040000, 0x08000000, 0x08080000,  1, f7    , 0x1FFF0000, 0x1FFF001F, 0x1FF00000, 0x1FF0EDC0, 0},
	{0x449, "STM32F74xxx/75xxx"               , 0x20004000, 0x20050000, 0x08000000, 0x08100000,  1, f7    , 0x1FFF0000, 0x1FFF001F, 0x1FF00000, 0x1FF0EDC0, 0},
	{0x451, "STM32F76xxx/77xxx"               , 0x20004000, 0x20080000, 0x08000000, 0x08200000,  1, f7    , 0x1FFF0000, 0x1FFF001F, 0x1FF00000, 0x1FF0EDC0, 0},
	/* L0 */
	{0x425, "STM32L031xx/041xx"               , 0x20001000, 0x20002000, 0x08000000, 0x08008000, 32, p_128 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF01000, 0},
	{0x417, "STM32L05xxx/06xxx"               , 0x20001000, 0x20002000, 0x08000000, 0x08010000, 32, p_128 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF01000, F_NO_ME},
	{0x447, "STM32L07xxx/08xxx"               , 0x20002000, 0x20005000, 0x08000000, 0x08030000, 32, p_128 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF02000, 0},
	/* L1 */
	{0x416, "STM32L1xxx6(8/B)"                , 0x20000800, 0x20004000, 0x08000000, 0x08020000, 16, p_256 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF01000, F_NO_ME},
	{0x429, "STM32L1xxx6(8/B)A"               , 0x20001000, 0x20008000, 0x08000000, 0x08020000, 16, p_256 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF01000, F_NO_ME},
	{0x427, "STM32L1xxxC"                     , 0x20001000, 0x20008000, 0x08000000, 0x08040000, 16, p_256 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF02000, F_NO_ME},
	{0x436, "STM32L1xxxD"                     , 0x20001000, 0x2000C000, 0x08000000, 0x08060000, 16, p_256 , 0x1FF80000, 0x1FF8009F, 0x1FF00000, 0x1FF02000, 0},
	{0x437, "STM32L1xxxE"                     , 0x20001000, 0x20014000, 0x08000000, 0x08080000, 16, p_256 , 0x1FF80000, 0x1FF8009F, 0x1FF00000, 0x1FF02000, F_NO_ME},
	/* L4 */
	{0x415, "STM32L47xxx/48xxx"               , 0x20003100, 0x20018000, 0x08000000, 0x08100000,  1, p_2k  , 0x1FFF7800, 0x1FFFF80F, 0x1FFF0000, 0x1FFF7000, 0},
	{0x435, "STM32L43xxx/44xxx"               , 0x20003100, 0x2000C000, 0x08000000, 0x08040000,  1, p_2k  , 0x1FFF7800, 0x1FFFF80F, 0x1FFF0000, 0x1FFF7000, 0},
	{0x461, "STM32L496xx/4A6xx"               , 0x20003100, 0x20040000, 0x08000000, 0x08100000,  1, p_2k  , 0x1FFF7800, 0x1FFFF80F, 0x1FFF0000, 0x1FFF7000, 0},
	/* These are not (yet) in AN2606: */
	{0x641, "Medium_Density PL"               , 0x20000200, 0x20005000, 0x08000000, 0x08020000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x9a8, "STM32W-128K"                     , 0x20000200, 0x20002000, 0x08000000, 0x08020000,  4, p_1k  , 0x08040800, 0x0804080F, 0x08040000, 0x08040800, 0},
	{0x9b0, "STM32W-256K"                     , 0x20000200, 0x20004000, 0x08000000, 0x08040000,  4, p_2k  , 0x08040800, 0x0804080F, 0x08040000, 0x08040800, 0},
#else
	{0x440, 0x20000800, 0x20002000, 0x08000000, 0x08010000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFEC00, 0x1FFFF800, 0},
	{0x442, 0x20001800, 0x20008000, 0x08000000, 0x08040000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, F_OBLL},
	{0x444, 0x20000800, 0x20001000, 0x08000000, 0x08008000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFEC00, 0x1FFFF800, 0},
	{0x445, 0x20001800, 0x20001800, 0x08000000, 0x08008000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFC400, 0x1FFFF800, 0},
	{0x448, 0x20001800, 0x20004000, 0x08000000, 0x08020000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFC800, 0x1FFFF800, 0},
	/* F1 */
	{0x412, 0x20000200, 0x20002800, 0x08000000, 0x08008000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x410, 0x20000200, 0x20005000, 0x08000000, 0x08020000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x414, 0x20000200, 0x20010000, 0x08000000, 0x08080000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x420, 0x20000200, 0x20002000, 0x08000000, 0x08020000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x428, 0x20000200, 0x20008000, 0x08000000, 0x08080000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x418, 0x20001000, 0x20010000, 0x08000000, 0x08040000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFB000, 0x1FFFF800, 0},
	{0x430, 0x20000800, 0x20018000, 0x08000000, 0x08100000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFE000, 0x1FFFF800, 0},
	/* F2 */
	{0x411, 0x20002000, 0x20020000, 0x08000000, 0x08100000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	/* F3 */
	{0x432, 0x20001400, 0x20008000, 0x08000000, 0x08040000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, 0},
	{0x422, 0x20001400, 0x2000A000, 0x08000000, 0x08040000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, 0},
	{0x439, 0x20001800, 0x20004000, 0x08000000, 0x08010000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, 0},
	{0x438, 0x20001800, 0x20003000, 0x08000000, 0x08010000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, 0},
	{0x446, 0x20001800, 0x20010000, 0x08000000, 0x08080000,  2, p_2k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFD800, 0x1FFFF800, 0},
	/* F4 */
	{0x413, 0x20003000, 0x20020000, 0x08000000, 0x08100000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x419, 0x20003000, 0x20030000, 0x08000000, 0x08200000,  1, f4db  , 0x1FFEC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x423, 0x20003000, 0x20010000, 0x08000000, 0x08040000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x433, 0x20003000, 0x20018000, 0x08000000, 0x08080000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x458, 0x20003000, 0x20008000, 0x08000000, 0x08020000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x431, 0x20003000, 0x20020000, 0x08000000, 0x08080000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x441, 0x20003000, 0x20020000, 0x08000000, 0x08100000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x463, 0x20003000, 0x20050000, 0x08000000, 0x08180000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x421, 0x20003000, 0x20020000, 0x08000000, 0x08080000,  1, f2f4  , 0x1FFFC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	{0x434, 0x20003000, 0x20060000, 0x08000000, 0x08200000,  1, f4db  , 0x1FFEC000, 0x1FFFC00F, 0x1FFF0000, 0x1FFF7800, 0},
	/* F7 */
	{0x452, 0x20004000, 0x20040000, 0x08000000, 0x08080000,  1, f7    , 0x1FFF0000, 0x1FFF001F, 0x1FF00000, 0x1FF0EDC0, 0},
	{0x449, 0x20004000, 0x20050000, 0x08000000, 0x08100000,  1, f7    , 0x1FFF0000, 0x1FFF001F, 0x1FF00000, 0x1FF0EDC0, 0},
	{0x451, 0x20004000, 0x20080000, 0x08000000, 0x08200000,  1, f7    , 0x1FFF0000, 0x1FFF001F, 0x1FF00000, 0x1FF0EDC0, 0},
	/* L0 */
	{0x425, 0x20001000, 0x20002000, 0x08000000, 0x08008000, 32, p_128 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF01000, 0},
	{0x417, 0x20001000, 0x20002000, 0x08000000, 0x08010000, 32, p_128 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF01000, F_NO_ME},
	{0x447, 0x20002000, 0x20005000, 0x08000000, 0x08030000, 32, p_128 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF02000, 0},
	/* L1 */
	{0x416, 0x20000800, 0x20004000, 0x08000000, 0x08020000, 16, p_256 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF01000, F_NO_ME},
	{0x429, 0x20001000, 0x20008000, 0x08000000, 0x08020000, 16, p_256 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF01000, F_NO_ME},
	{0x427, 0x20001000, 0x20008000, 0x08000000, 0x08040000, 16, p_256 , 0x1FF80000, 0x1FF8001F, 0x1FF00000, 0x1FF02000, F_NO_ME},
	{0x436, 0x20001000, 0x2000C000, 0x08000000, 0x08060000, 16, p_256 , 0x1FF80000, 0x1FF8009F, 0x1FF00000, 0x1FF02000, 0},
	{0x437, 0x20001000, 0x20014000, 0x08000000, 0x08080000, 16, p_256 , 0x1FF80000, 0x1FF8009F, 0x1FF00000, 0x1FF02000, F_NO_ME},
	/* L4 */
	{0x415, 0x20003100, 0x20018000, 0x08000000, 0x08100000,  1, p_2k  , 0x1FFF7800, 0x1FFFF80F, 0x1FFF0000, 0x1FFF7000, 0},
	{0x435, 0x20003100, 0x2000C000, 0x08000000, 0x08040000,  1, p_2k  , 0x1FFF7800, 0x1FFFF80F, 0x1FFF0000, 0x1FFF7000, 0},
	{0x461, 0x20003100, 0x20040000, 0x08000000, 0x08100000,  1, p_2k  , 0x1FFF7800, 0x1FFFF80F, 0x1FFF0000, 0x1FFF7000, 0},
	/* These are not (yet) in AN2606: */
	{0x641, 0x20000200, 0x20005000, 0x08000000, 0x08020000,  4, p_1k  , 0x1FFFF800, 0x1FFFF80F, 0x1FFFF000, 0x1FFFF800, 0},
	{0x9a8, 0x20000200, 0x20002000, 0x08000000, 0x08020000,  4, p_1k  , 0x08040800, 0x0804080F, 0x08040000, 0x08040800, 0},
	{0x9b0, 0x20000200, 0x20004000, 0x08000000, 0x08040000,  4, p_2k  , 0x08040800, 0x0804080F, 0x08040000, 0x08040800, 0},	
#endif
	{0x0}
};

stm32_dev_t* UTIL_getStmDev(uint16_t id){
	for(uint8_t i=0; i< sizeof(stm32_devices) / sizeof(stm32_devices[0]); i++){
		if(stm32_devices[i].id == id){
			return (stm32_dev_t*)&stm32_devices[i];
		}
	}
	return (stm32_dev_t*)0;
}


#if defined(STM32F030C6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444
  
#elif defined(STM32F030C8)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F030CC)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F030F4)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F030K6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F030R8)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F030RC)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F070C6)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445
 
#elif defined(STM32F070CB)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F070F6)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F070RB)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F031C4)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F031C6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F031E6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F031F4)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F031F6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F031G4)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F031G6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F031K4)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F031K6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F051C4)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx 
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F051C6)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx 
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F051C8)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx 
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F051K4)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx 
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F051K6)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx 
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F051K8)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx 
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F051R4)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx 
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F051R6)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx 
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F051R8)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx 
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F051T8)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx 
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F071C8)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx   
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F071CB)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx   
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F071RB)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx   
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F071V8)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx   
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F071VB)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx   
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F091CB)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx  
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F091CC)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx  
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F091RB)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx  
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F091RC)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx  
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F091VB)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx  
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F091VC)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx  
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F042C4)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F042C6)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F042F4)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F042F6)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F042G4)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F042G6)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F042K4)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F042K6)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F042T6)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F072C8)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx  
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F072CB)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx  
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F072R8)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F072RB)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F072V8)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F072VB)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F038C6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F038E6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F038F6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F038G6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F038K6)
  #define CHIO_ID 0x444 //STM32F03xx4/6
  #define CHIP_INFO CHIP_ID444

#elif defined(STM32F048C6)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F048G6)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F048T6)
  #define CHIO_ID 0x445 //STM32F04xxx/F070x6
  #define CHIP_INFO CHIP_ID445

#elif defined(STM32F058C8)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F058R8)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F058T8)
  #define CHIO_ID 0x440 //STM32F030x8/F05xxx
  #define CHIP_INFO CHIP_ID440

#elif defined(STM32F078CB)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F078RB)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F078VB)
  #define CHIO_ID 0x448 //STM32F070xB/F071xx/F72xx
  #define CHIP_INFO CHIP_ID448

#elif defined(STM32F098CC)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F098RC)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx  
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F098VC)
  #define CHIO_ID 0x442 //STM32F030xC/F09xxx  
  #define CHIP_INFO CHIP_ID442

#elif defined(STM32F100C4)
  #define CHIO_ID 0x412  //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F100C6)
  #define CHIO_ID 0x412  //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F100C8)
  #define CHIO_ID 0x420 //STM32F10xxx Medium-density VL
  #define CHIP_INFO CHIP_ID420

#elif defined(STM32F100CB)
  #define CHIO_ID 0x420 //STM32F10xxx Medium-density VL
  #define CHIP_INFO CHIP_ID420

#elif defined(STM32F100R4)
  #define CHIO_ID 0x412  //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F100R6)
  #define CHIO_ID 0x412  //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F100R8)
  #define CHIO_ID 0x420 //STM32F10xxx Medium-density VL
  #define CHIP_INFO CHIP_ID420

#elif defined(STM32F100RB)
  #define CHIO_ID 0x420 //STM32F10xxx Medium-density VL
  #define CHIP_INFO CHIP_ID420

#elif defined(STM32F100RC)
  #define CHIO_ID 0x428 //STM32F10xxx High-density VL
  #define CHIP_INFO CHIP_ID428

#elif defined(STM32F100RD)
  #define CHIO_ID 0x428 //STM32F10xxx High-density VL
  #define CHIP_INFO CHIP_ID428

#elif defined(STM32F100RE)
  #define CHIO_ID 0x428 //STM32F10xxx High-density VL
  #define CHIP_INFO CHIP_ID428

#elif defined(STM32F100V8)
  #define CHIO_ID 0x420 //STM32F10xxx Medium-density VL
  #define CHIP_INFO CHIP_ID420

#elif defined(STM32F100VB)
  #define CHIO_ID 0x420 //STM32F10xxx Medium-density VL
  #define CHIP_INFO CHIP_ID420

#elif defined(STM32F100VC)
  #define CHIO_ID 0x428 //STM32F10xxx High-density VL
  #define CHIP_INFO CHIP_ID428

#elif defined(STM32F100VD)
  #define CHIO_ID 0x428 //STM32F10xxx High-density VL
  #define CHIP_INFO CHIP_ID428

#elif defined(STM32F100VE)
  #define CHIO_ID 0x428 //STM32F10xxx High-density VL
  #define CHIP_INFO CHIP_ID428

#elif defined(STM32F100ZC)
  #define CHIO_ID 0x428 //STM32F10xxx High-density VL
  #define CHIP_INFO CHIP_ID428

#elif defined(STM32F100ZD)
  #define CHIO_ID 0x428 //STM32F10xxx High-density VL
  #define CHIP_INFO CHIP_ID428

#elif defined(STM32F100ZE)
  #define CHIO_ID 0x428 //STM32F10xxx High-density VL
  #define CHIP_INFO CHIP_ID428

#elif defined(STM32F101C4)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F101C6)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F101C8)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F101CB)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F101R4)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F101R6)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F101R8)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F101RB)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F101RC)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101RD)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101RE)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101RF)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101RG)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101T4)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F101T6)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F101T8)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F101TB)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F101V8)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F101VB)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F101VC)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101VD)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101VE)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101VF)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101VG)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101ZC)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101ZD)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101ZE)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101ZF)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F101ZG)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F102C4)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F102C6)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F102C8)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F102CB)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F102R4)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F102R6)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F102R8)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F102RB)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F103C4)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F103C6)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F103C8)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F103CB)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F103R4)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F103R6)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F103R8)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F103RB)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F103RC)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F103RD)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F103RE)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F103RF)
  #define CHIO_ID 0x430 //STM32F10xxx XL-density
  #define CHIP_INFO CHIP_ID430

#elif defined(STM32F103RG)
  #define CHIO_ID 0x430 //STM32F10xxx XL-density
  #define CHIP_INFO CHIP_ID430

#elif defined(STM32F103T4)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F103T6)
  #define CHIO_ID 0x412 //STM32F10xxx Low-density
  #define CHIP_INFO CHIP_ID412

#elif defined(STM32F103T8)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F103TB)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F103V8)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F103VB)
  #define CHIO_ID 0x410 //STM32F10xxx Medium-density" 
  #define CHIP_INFO CHIP_ID410

#elif defined(STM32F103VC)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F103VD)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F103VE)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F103VF)
  #define CHIO_ID 0x430 //STM32F10xxx XL-density
  #define CHIP_INFO CHIP_ID430

#elif defined(STM32F103VG)
  #define CHIO_ID 0x430 //STM32F10xxx XL-density
  #define CHIP_INFO CHIP_ID430

#elif defined(STM32F103ZC)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F103ZD)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F103ZE)
  #define CHIO_ID 0x414 //STM32F10xxx High-density
  #define CHIP_INFO CHIP_ID414

#elif defined(STM32F103ZF)
  #define CHIO_ID 0x430 //STM32F10xxx XL-density
  #define CHIP_INFO CHIP_ID430

#elif defined(STM32F103ZG)
  #define CHIO_ID 0x430 //STM32F10xxx XL-density
  #define CHIP_INFO CHIP_ID430

#elif defined(STM32F105R8)
  #define CHIO_ID 0x418 //STM32F105xx/F107xx
  #define CHIP_INFO CHIP_ID418

#elif defined(STM32F105RB)
  #define CHIO_ID 0x418 //STM32F105xx/F107xx
  #define CHIP_INFO CHIP_ID418

#elif defined(STM32F105RC)
  #define CHIO_ID 0x418 //STM32F105xx/F107xx
  #define CHIP_INFO CHIP_ID418

#elif defined(STM32F105V8)
  #define CHIO_ID 0x418 //STM32F105xx/F107xx
  #define CHIP_INFO CHIP_ID418

#elif defined(STM32F105VB)
  #define CHIO_ID 0x418 //STM32F105xx/F107xx
  #define CHIP_INFO CHIP_ID418

#elif defined(STM32F105VC)
  #define CHIO_ID 0x418 //STM32F105xx/F107xx
  #define CHIP_INFO CHIP_ID418

#elif defined(STM32F107RB)
  #define CHIO_ID 0x418 //STM32F105xx/F107xx
  #define CHIP_INFO CHIP_ID418

#elif defined(STM32F107RC)
  #define CHIO_ID 0x418 //STM32F105xx/F107xx
  #define CHIP_INFO CHIP_ID418

#elif defined(STM32F107VB)
  #define CHIO_ID 0x418 //STM32F105xx/F107xx
  #define CHIP_INFO CHIP_ID418

#elif defined(STM32F107VC)
  #define CHIO_ID 0x418 //STM32F105xx/F107xx
  #define CHIP_INFO CHIP_ID418

#elif defined(STM32F205RB)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205RC)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205RE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205RF)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205RG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205VB)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205VC)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205VE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205VF)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205VG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205ZC)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205ZE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205ZF)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F205ZG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F215RE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F215RG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F215VE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F215VG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F215ZE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F215ZG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207IC)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207IE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207IF)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207IG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207VC)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207VE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207VF)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207VG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207ZC)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207ZE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207ZF)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F207ZG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F217IE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F217IG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F217VE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F217VG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F217ZE)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F217ZG)
  #define CHIO_ID 0x411  //STM32F2xxxx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F301C6)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F301C8)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F301K6)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F301K8)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F301R6)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F301R8)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F302C6)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F302C8)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID411

#elif defined(STM32F302CB)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422

#elif defined(STM32F302CC)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422
 
#elif defined(STM32F302K6)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID439

#elif defined(STM32F302K8)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID439

#elif defined(STM32F302R6)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID439

#elif defined(STM32F302R8)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID439

#elif defined(STM32F302RB)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422

#elif defined(STM32F302RC)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422

#elif defined(STM32F302RD)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F302RE)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F302VB)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422

#elif defined(STM32F302VC)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422

#elif defined(STM32F302VD)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F302VE)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F302ZD)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F302ZE)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F303C6)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F303C8)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F303CB)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422

#elif defined(STM32F303CC)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422

#elif defined(STM32F303K6)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F303K8)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F303R6)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F303R8)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F303RB)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422

#elif defined(STM32F303RC)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422

#elif defined(STM32F303RD)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F303RE)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F303VB)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422

#elif defined(STM32F303VC)
  #define CHIO_ID 0x422 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID422

#elif defined(STM32F303VD)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F303VE)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F303ZD)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F303ZE)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F334C4)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F334C6)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F334C8)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F334K4)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F334K6)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F334K8)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F334R6)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F334R8)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F373C8)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F373CB)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F373CC)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F373R8)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F373RB)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F373RC)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F373V8)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F373VB)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F373VC)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F318C8)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID439

#elif defined(STM32F318K8)
  #define CHIO_ID 0x439 //STM32F301xx/F302x4(6/8)/F318xx
  #define CHIP_INFO CHIP_ID439

#elif defined(STM32F328C8)
  #define CHIO_ID 0x438 //STM32F303x4(6/8)/F334xx/F328xx
  #define CHIP_INFO CHIP_ID438

#elif defined(STM32F358CC)
  #define CHIO_ID 0x458 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID458

#elif defined(STM32F358RC)
  #define CHIO_ID 0x458 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID458

#elif defined(STM32F358VC)
  #define CHIO_ID 0x458 //STM32F302xB(C)/F303xB(C)/F358xx
  #define CHIP_INFO CHIP_ID458

#elif defined(STM32F378CC)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F378RC)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F378VC)
  #define CHIO_ID 0x432 //STM32F373xx/F378xx
  #define CHIP_INFO CHIP_ID432

#elif defined(STM32F398VE)
  #define CHIO_ID 0x446 //STM32F302xD(E)/F303xD(E)/F398xx
  #define CHIP_INFO CHIP_ID446

#elif defined(STM32F401CB)
  #define CHIO_ID 0x423 //STM32F401xB(C)
  #define CHIP_INFO CHIP_ID423

#elif defined(STM32F401CC)
  #define CHIO_ID 0x423 //STM32F401xB(C)
  #define CHIP_INFO CHIP_ID423

#elif defined(STM32F401CD)
  #define CHIO_ID 0x433 //STM32F401xD(E)
  #define CHIP_INFO CHIP_ID433

#elif defined(STM32F401CE)
  #define CHIO_ID 0x433 //STM32F401xD(E)
  #define CHIP_INFO CHIP_ID433

#elif defined(STM32F401RB)
  #define CHIO_ID 0x423 //STM32F401xB(C)
  #define CHIP_INFO CHIP_ID423

#elif defined(STM32F401RC)
  #define CHIO_ID 0x423 //STM32F401xB(C)
  #define CHIP_INFO CHIP_ID423

#elif defined(STM32F401RD)
  #define CHIO_ID 0x433 //STM32F401xD(E)
  #define CHIP_INFO CHIP_ID433

#elif defined(STM32F401RE)
  #define CHIO_ID 0x433 //STM32F401xD(E)
  #define CHIP_INFO CHIP_ID433

#elif defined(STM32F401VB)
  #define CHIO_ID 0x423 //STM32F401xB(C)
  #define CHIP_INFO CHIP_ID423

#elif defined(STM32F401VC)
  #define CHIO_ID 0x423 //STM32F401xB(C)
  #define CHIP_INFO CHIP_ID423

#elif defined(STM32F401VD)
  #define CHIO_ID 0x433 //STM32F401xD(E)
  #define CHIP_INFO CHIP_ID433

#elif defined(STM32F401VE)
  #define CHIO_ID 0x433 //STM32F401xD(E)
  #define CHIP_INFO CHIP_ID433

#elif defined(STM32F405OE)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F405OG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F405RG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F405VG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F405ZG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F415OG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F415RG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F415VG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F415ZG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F407IE)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F407IG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F407VE)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F407VG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F407ZE)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F407ZG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F417IE)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F417IG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F417VE)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F417VG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F417ZE)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F417ZG)
  #define CHIO_ID 0x413 //STM32F40xxx/41xxx
  #define CHIP_INFO CHIP_ID413

#elif defined(STM32F410C8)
  #define CHIO_ID 0x458 //STM32F410xx
  #define CHIP_INFO CHIP_ID458

#elif defined(STM32F410CB)
  #define CHIO_ID 0x458 //STM32F410xx
  #define CHIP_INFO CHIP_ID458

#elif defined(STM32F410R8)
  #define CHIO_ID 0x458 //STM32F410xx
  #define CHIP_INFO CHIP_ID458

#elif defined(STM32F410RB)
  #define CHIO_ID 0x458 //STM32F410xx
  #define CHIP_INFO CHIP_ID458

#elif defined(STM32F410T8)
  #define CHIO_ID 0x458 //STM32F410xx
  #define CHIP_INFO CHIP_ID458

#elif defined(STM32F410TB)
  #define CHIO_ID 0x458 //STM32F410xx
  #define CHIP_INFO CHIP_ID458

#elif defined(STM32F411CC)
  #define CHIO_ID 0x431 //STM32F411xx
  #define CHIP_INFO CHIP_ID431

#elif defined(STM32F411CE)
  #define CHIO_ID 0x431 //STM32F411xx
  #define CHIP_INFO CHIP_ID431

#elif defined(STM32F411RC)
  #define CHIO_ID 0x431 //STM32F411xx
  #define CHIP_INFO CHIP_ID431

#elif defined(STM32F411RE)
  #define CHIO_ID 0x431 //STM32F411xx
  #define CHIP_INFO CHIP_ID431

#elif defined(STM32F411VC)
  #define CHIO_ID 0x431 //STM32F411xx
  #define CHIP_INFO CHIP_ID431

#elif defined(STM32F411VE)
  #define CHIO_ID 0x431 //STM32F411xx
  #define CHIP_INFO CHIP_ID431

#elif defined(STM32F412CE)
  #define CHIO_ID 0x441  //STM32F412xx
  #define CHIP_INFO CHIP_ID441

#elif defined(STM32F412CG)
  #define CHIO_ID 0x441  //STM32F412xx
  #define CHIP_INFO CHIP_ID441

#elif defined(STM32F412RE)
  #define CHIO_ID 0x441  //STM32F412xx
  #define CHIP_INFO CHIP_ID441

#elif defined(STM32F412RG)
  #define CHIO_ID 0x441  //STM32F412xx
  #define CHIP_INFO CHIP_ID441

#elif defined(STM32F412VE)
  #define CHIO_ID 0x441  //STM32F412xx
  #define CHIP_INFO CHIP_ID441

#elif defined(STM32F412VG)
  #define CHIO_ID 0x441  //STM32F412xx
  #define CHIP_INFO CHIP_ID441

#elif defined(STM32F412ZE)
  #define CHIO_ID 0x441  //STM32F412xx
  #define CHIP_INFO CHIP_ID441

#elif defined(STM32F412ZG)
  #define CHIO_ID 0x441  //STM32F412xx
  #define CHIP_INFO CHIP_ID441

#elif defined(STM32F413CG)
  #define CHIO_ID 0x463 //STM32F413xx
  #define CHIP_INFO CHIP_ID463

#elif defined(STM32F413CH)
  #define CHIO_ID 0x463 //STM32F413xx
  #define CHIP_INFO CHIP_ID463

#elif defined(STM32F413MG)
  #define CHIO_ID 0x463 //STM32F413xx
  #define CHIP_INFO CHIP_ID463

#elif defined(STM32F413MH)
  #define CHIO_ID 0x463 //STM32F413xx
  #define CHIP_INFO CHIP_ID463

#elif defined(STM32F413RG)
  #define CHIO_ID 0x463 //STM32F413xx
  #define CHIP_INFO CHIP_ID463

#elif defined(STM32F413RH)
  #define CHIO_ID 0x463 //STM32F413xx
  #define CHIP_INFO CHIP_ID463

#elif defined(STM32F413VG)
  #define CHIO_ID 0x463 //STM32F413xx
  #define CHIP_INFO CHIP_ID463

#elif defined(STM32F413VH)
  #define CHIO_ID 0x463 //STM32F413xx
  #define CHIP_INFO CHIP_ID463

#elif defined(STM32F413ZG)
  #define CHIO_ID 0x463 //STM32F413xx
  #define CHIP_INFO CHIP_ID463

#elif defined(STM32F413ZH)
  #define CHIO_ID 0x463 //STM32F413xx
  #define CHIP_INFO CHIP_ID463

#elif defined(STM32F423CH)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F423MH)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F423RH)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F423VH)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F423ZH)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F427AG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F427AI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F427IG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F427II)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F427VG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F427VI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F427ZG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F427ZI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F437AI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F437IG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F437II)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F437VG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F437VI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F437ZG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F437ZI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429AG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429AI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429BE)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429BG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429BI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429IE)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429IG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429II)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429NE)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429NG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429NI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429VE)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429VG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429VI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429ZE)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429ZG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F429ZI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F439AI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F439BG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F439BI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F439IG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F439II)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F439NG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F439NI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F439VG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F439VI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F439ZG)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F439ZI)
  #define CHIO_ID 0x419 //STM32F42xxx/43xxx
  #define CHIP_INFO CHIP_ID419

#elif defined(STM32F446MC)
  #define CHIO_ID 0x421 //STM32F446xx
  #define CHIP_INFO CHIP_ID421

#elif defined(STM32F446ME)
  #define CHIO_ID 0x421 //STM32F446xx
  #define CHIP_INFO CHIP_ID421

#elif defined(STM32F446RC)
  #define CHIO_ID 0x421 //STM32F446xx
  #define CHIP_INFO CHIP_ID421

#elif defined(STM32F446RE)
  #define CHIO_ID 0x421 //STM32F446xx
  #define CHIP_INFO CHIP_ID421

#elif defined(STM32F446VC)
  #define CHIO_ID 0x421 //STM32F446xx
  #define CHIP_INFO CHIP_ID421

#elif defined(STM32F446VE)
  #define CHIO_ID 0x421 //STM32F446xx
  #define CHIP_INFO CHIP_ID421

#elif defined(STM32F446ZC)
  #define CHIO_ID 0x421 //STM32F446xx
  #define CHIP_INFO CHIP_ID421

#elif defined(STM32F446ZE)
  #define CHIO_ID 0x421 //STM32F446xx
  #define CHIP_INFO CHIP_ID421

#elif defined(STM32F469AE)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469AG)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469AI)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469BE)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469BG)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469BI)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469IE)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469IG)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469II)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469NE)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469NG)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469NI)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469VE)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469VG)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469VI)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469ZE)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469ZG)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F469ZI)
  #define CHIO_ID 0x434 //STM32F469xx
  #define CHIP_INFO CHIP_ID434

#elif defined(STM32F479AG)

#elif defined(STM32F479AI)

#elif defined(STM32F479BG)

#elif defined(STM32F479BI)

#elif defined(STM32F479IG)

#elif defined(STM32F479II)

#elif defined(STM32F479NG)

#elif defined(STM32F479NI)

#elif defined(STM32F479VG)

#elif defined(STM32F479VI)

#elif defined(STM32F479ZG)

#elif defined(STM32F479ZI)

#elif defined(STM32F722IC)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F722IE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F722RC)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F722RE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F722VC)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F722VE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F722ZC)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F722ZE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F732IE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F732RE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F732VE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F732ZE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F723IC)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F723IE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F723VC)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F723VE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F723ZC)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F723ZE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F733IE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F733VE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F733ZE)
  #define CHIO_ID 0x452 //STM32F72xxx/73xxx
  #define CHIP_INFO CHIP_ID452

#elif defined(STM32F745IE)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F745IG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F745VE)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F745VG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F745ZE)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F745ZG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F765BG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F765BI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F765IG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F765II)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F765NG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F765NI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F765VG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F765VI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F765ZG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F765ZI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F746BE)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F746BG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F746IE)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F746IG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F746NE)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F746NG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F746VE)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F746VG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F746ZE)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F746ZG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F756BG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F756IG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F756NG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F756VG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F756ZG)
  #define CHIO_ID 0x449 //STM32F74xxx/75xxx
  #define CHIP_INFO CHIP_ID449

#elif defined(STM32F767BG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F767BI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F767IG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F767II)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F767NG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F767NI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F767VG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F767VI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F767ZG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F767ZI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F777BI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F777II)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F777NI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F777VI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F777ZI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F768AI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F778AI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F769AG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F769AI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F769BG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F769BI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F769IG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F769II)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F769NG)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F769NI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F779AI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F779BI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F779II)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32F779NI)
  #define CHIO_ID 0x451 //STM32F76xxx/77xxx
  #define CHIP_INFO CHIP_ID451

#elif defined(STM32L011D3)

#elif defined(STM32L011D4)

#elif defined(STM32L011E3)

#elif defined(STM32L011E4)

#elif defined(STM32L011F3)

#elif defined(STM32L011F4)

#elif defined(STM32L011G3)

#elif defined(STM32L011G4)

#elif defined(STM32L011K3)

#elif defined(STM32L011K4)

#elif defined(STM32L021D4)

#elif defined(STM32L021F4)

#elif defined(STM32L021G4)

#elif defined(STM32L021K4)

#elif defined(STM32L031C4)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L031C6)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L031E4)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L031E6)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L031F4)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L031F6)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L031G4)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L031G6)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L031K4)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L031K6)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L041C4)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L041C6)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L041E6)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L041F6)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L041G6)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L041K6)
  #define CHIO_ID 0x425 //STM32L031xx/041xx
  #define CHIP_INFO CHIP_ID425

#elif defined(STM32L051C6)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx"
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L051C8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx"
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L051K6)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx"
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L051K8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx"
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L051R6)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx"
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L051R8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx"
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L051T6)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx"
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L051T8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx"
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L071CB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L071CZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L071C8)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L071KB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L071KZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L071K8)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L071RB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L071RZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L071VB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L071VZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L071V8)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L081CZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L081KZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L052C6)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L052C8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L052K6)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L052K8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L052R6)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L052R8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L052T6)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L052T8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L062K8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L072CB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L072CZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L072KB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L072KZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L072RB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L072RZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L072VB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L072VZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L072V8)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L082CZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L082KB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L082KZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L053C6)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L053C8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L053R6)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L053R8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L063C8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L063R8)
  #define CHIO_ID 0x417 //STM32L05xxx/06xxx
  #define CHIP_INFO CHIP_ID417

#elif defined(STM32L073CB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L073CZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L073RB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L073RZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L073VB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L073VZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L073V8)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L083CB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L083CZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L083RB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L083RZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L083VB)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L083VZ)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L083V8)
  #define CHIO_ID 0x447 //STM32L07xxx/08xxx
  #define CHIP_INFO CHIP_ID447

#elif defined(STM32L100C6)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L100R8)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L100RB)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L100RC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L151C6)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L151C8)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L151CB)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L151CC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L151QC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L151QD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L151QE)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L151R6)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L151R8)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L151RB)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L151RC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L151RD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L151RE)
  #define CHIO_ID 0x437 //STM32L1xxxE
  #define CHIP_INFO CHIP_ID437

#elif defined(STM32L151UC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L151V8)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L151VB)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L151VC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L151VD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L151VE)
  #define CHIO_ID 0x437 //STM32L1xxxE
  #define CHIP_INFO CHIP_ID437

#elif defined(STM32L151ZC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L151ZD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L151ZE)
  #define CHIO_ID 0x437 //STM32L1xxxE
  #define CHIP_INFO CHIP_ID437

#elif defined(STM32L152C6)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L152C8)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L152CB)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L152CC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L152QC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L152QD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L152QE)
  #define CHIO_ID 0x437 //STM32L1xxxE
  #define CHIP_INFO CHIP_ID437

#elif defined(STM32L152R6)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L152R8)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L152RB)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L152RC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L152RD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L152RE)
  #define CHIO_ID 0x437 //STM32L1xxxE
  #define CHIP_INFO CHIP_ID437

#elif defined(STM32L152V8)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L152VB)
  #define CHIO_ID 0x416 //STM32L1xxx6(8/B)
  #define CHIP_INFO CHIP_ID416

#elif defined(STM32L152VC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L152VD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L152VE)
  #define CHIO_ID 0x437 //STM32L1xxxE
  #define CHIP_INFO CHIP_ID437

#elif defined(STM32L152ZC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L152ZD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L152ZE)
  #define CHIO_ID 0x437 //STM32L1xxxE
  #define CHIP_INFO CHIP_ID437

#elif defined(STM32L162QD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L162RC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L162RD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L162RE)
  #define CHIO_ID 0x437 //STM32L1xxxE
  #define CHIP_INFO CHIP_ID437

#elif defined(STM32L162VC)
  #define CHIO_ID 0x427 //STM32L1xxxC
  #define CHIP_INFO CHIP_ID427

#elif defined(STM32L162VD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L162VE)
  #define CHIO_ID 0x437 //STM32L1xxxE
  #define CHIP_INFO CHIP_ID437

#elif defined(STM32L162ZD)
  #define CHIO_ID 0x436 //STM32L1xxxD
  #define CHIP_INFO CHIP_ID436

#elif defined(STM32L162ZE)
  #define CHIO_ID 0x437 //STM32L1xxxE
  #define CHIP_INFO CHIP_ID437

#elif defined(STM32L431CB)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L431CC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L431KB)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L431KC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L431RB)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L431RC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L431VC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L451CC)

#elif defined(STM32L451CE)

#elif defined(STM32L451RC)

#elif defined(STM32L451RE)

#elif defined(STM32L451VC)

#elif defined(STM32L451VE)

#elif defined(STM32L471QE)
  #define CHIO_ID 0x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L471QG)
  #define CHIO_ID 0x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L471RE)
  #define CHIO_ID 0x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L471RG)
  #define CHIO_ID 0x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L471VE)
  #define CHIO_ID 0x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L471VG)
  #define CHIO_ID 0x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L471ZE)
  #define CHIO_ID 0x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L471ZG)
  #define CHIO_ID 0x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L432KB)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L432KC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L442KC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L452CC)
 
#elif defined(STM32L452CE)
 
#elif defined(STM32L452RC)
 
#elif defined(STM32L452RE)
 
#elif defined(STM32L452VC)
 
#elif defined(STM32L452VE)
 
#elif defined(STM32L462CE)

#elif defined(STM32L462RE)
 
#elif defined(STM32L462VE)
 
#elif defined(STM32L433CB)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L433CC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L433RB)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L433RC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L433VC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L443CC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L443RC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L443VC)
  #define CHIO_ID 0x435 //STM32L43xxx/44xxx
  #define CHIP_INFO CHIP_ID435

#elif defined(STM32L475RC)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L475RE)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L475RG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L475VC)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L475VE)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L475VG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L485JC)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L485JE)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476JE)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476JG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476ME)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476MG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476QE)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476QG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476RC)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476RE)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476RG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476VC)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476VE)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476VG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476ZE)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L476ZG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L486JG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L486QG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L486RG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L486VG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L486ZG)
  #define CHIO_ID 00x415 //STM32L47xxx/48xxx
  #define CHIP_INFO CHIP_ID415

#elif defined(STM32L496AE)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L496AG)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L496QE)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L496QG)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L496RE)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L496RG)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L496VE)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L496VG)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L496ZE)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L496ZG)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L4A6AG)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L4A6QG)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L4A6RG)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L4A6VG)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#elif defined(STM32L4A6ZG)
  #define CHIO_ID 0x461 //STM32L496xx/4A6xx" 
  #define CHIP_INFO CHIP_ID461

#else 
#error   UNKNOWN CHIP PLEASE FIXED ME
#endif
