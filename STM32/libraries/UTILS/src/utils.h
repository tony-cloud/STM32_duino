
#ifndef _ULMYUTILS_H_
#define _ULMYUTILS_H_


#ifdef __cplusplus
extern "C" {
#endif

uint8_t  UTIL_toDigit(char x);
int32_t  UTIL_num(char* str);
uint8_t  UTIL_isHexStr(char* str);
uint32_t UTIL_hexNum(char* str);
uint32_t UTIL_getNum(char* str);

uint8_t	 UTIL_maskToPin(uint32_t mask); 
uint32_t UTIL_Str2PortPin(char* str);

#ifdef __cplusplus
}  //extern "C" {
#endif

#include "Bootloader.h"
#include "dev_table.h"
#endif
