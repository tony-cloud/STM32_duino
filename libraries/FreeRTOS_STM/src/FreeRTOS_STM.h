#ifndef  _FREERTOSSTM_H_
#define  _FREERTOSSTM_H_
#include "FreeRTOS/Source/include/FreeRTOS.h"
#include "FreeRTOS/Source/include/task.h"
#include "FreeRTOS/Source/include/queue.h"
#include "FreeRTOS/Source/include/semphr.h"
#include "basic_io_arm.h"

#ifdef __cplusplus
extern "C" {
#endif

 void vApplicationIdleHook( void );
 void vApplicationTickHook( void );
#ifdef __cplusplus
} //extern "C" {
#endif

#endif //_FREERTOSSTM_H_