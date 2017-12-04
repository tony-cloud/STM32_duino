/*
  stm32flash - Open Source ST STM32 flash program for *nix
  Copyright (C) 2010 Geoffrey McRae <geoff@spacevs.com>

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
  
  for arduino modify by huaweiwx@sina.com 2017.10
*/


#ifndef _DEVTABLE_H_
#define _DEVTABLE_H_

// #define USE_STM32NAME 

typedef enum {
	F_NO_ME = 1 << 0,	/* Mass-Erase not supported */
	F_OBLL  = 1 << 1,	/* OBL_LAUNCH required */
} flags_t;

typedef struct stm32_dev	stm32_dev_t;

struct stm32_dev {
	uint16_t	id;
#ifdef USE_STM32NAME
	const char	*name;
#endif	
	uint32_t	ram_start, ram_end;
	uint32_t	fl_start, fl_end;
	uint16_t	fl_pps; // pages per sector
	uint32_t	*fl_ps;  // page size
	uint32_t	opt_start, opt_end;
	uint32_t	mem_start, mem_end;
	uint32_t	flags;
};

//extern const stm32_dev_t devices;

#ifdef __cplusplus
extern "C" {
#endif

stm32_dev_t* UTIL_getStmDev(uint16_t id);


#ifdef __cplusplus
} //exter "C" {
#endif

#endif

