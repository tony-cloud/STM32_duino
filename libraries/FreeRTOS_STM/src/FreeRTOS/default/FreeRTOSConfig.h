/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

	***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
	***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
	the FAQ page "My application does not run, what could be wrong?".  Have you
	defined configASSERT()?

	http://www.FreeRTOS.org/support - In return for receiving this top quality
	embedded software for free we request you assist our global community by
	participating in the support forum.

	http://www.FreeRTOS.org/training - Investing in training allows your team to
	be as productive as possible as early as possible.  Now you can receive
	FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
	Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

#ifndef _FREERTOS_CONFIG_DEFAULT_H_
#define _FREERTOS_CONFIG_DEFAULT_H_

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *--------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */   	      
/* Section where include file can be added */
/* USER CODE END Includes */ 

/* Ensure stdint is only used by the compiler, and not the assembler. */
#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
   #include <stdint.h>
   extern uint32_t SystemCoreClock;
#endif

#ifndef portTickUSE_TIMx
#  ifdef TIM7
#    define portTickUSE_TIMx 7
#  else
#    define portTickUSE_TIMx 0
#  endif
#endif

#ifndef portUSE_HEAP
	#define  portUSE_HEAP  3
#endif

#ifndef configUSE_PREEMPTION
#  define configUSE_PREEMPTION                   1
#endif
#ifndef configSUPPORT_STATIC_ALLOCATION
#  define configSUPPORT_STATIC_ALLOCATION        0
#endif
#ifndef configSUPPORT_DYNAMIC_ALLOCATION
#  define configSUPPORT_DYNAMIC_ALLOCATION       1
#endif

#ifndef configUSE_IDLE_HOOK
#  define configUSE_IDLE_HOOK                    0
#endif

#ifndef  configUSE_TICK_HOOK
#  define configUSE_TICK_HOOK                    0
#endif

#ifndef configCPU_CLOCK_HZ
#define configCPU_CLOCK_HZ                       ( SystemCoreClock )
#endif

#ifndef configTICK_RATE_HZ
#define configTICK_RATE_HZ                       ((TickType_t)1000)
#endif

#ifndef configMAX_PRIORITIES
#define configMAX_PRIORITIES                     ( 7 )
#endif

#ifndef configMINIMAL_STACK_SIZE
#define configMINIMAL_STACK_SIZE                 ((uint16_t)128)
#endif

#ifndef configTOTAL_HEAP_SIZE
#ifdef RAM_LENGTH
#define configTOTAL_HEAP_SIZE                    (RAM_LENGTH/8)
#else
#define configTOTAL_HEAP_SIZE                    ((size_t)(8*1024))
#endif
#endif

#ifndef configMAX_TASK_NAME_LEN
#define configMAX_TASK_NAME_LEN                  ( 16 )
#endif

#ifndef configUSE_16_BIT_TICKS
#define configUSE_16_BIT_TICKS                   0
#endif

#ifndef configUSE_MUTEXES
#define configUSE_MUTEXES                        1
#endif

#ifndef configQUEUE_REGISTRY_SIZE
#define configQUEUE_REGISTRY_SIZE                8
#endif

/* Co-routine definitions. */
#ifndef configUSE_CO_ROUTINES
#define configUSE_CO_ROUTINES                    0
#endif

#ifndef configMAX_CO_ROUTINE_PRIORITIES
#define configMAX_CO_ROUTINE_PRIORITIES          ( 2 )
#endif


/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#ifndef INCLUDE_vTaskPrioritySet
#define INCLUDE_vTaskPrioritySet            1
#endif

#ifndef INCLUDE_uxTaskPriorityGet
#define INCLUDE_uxTaskPriorityGet           1
#endif

#ifndef INCLUDE_vTaskDelete
#define INCLUDE_vTaskDelete                 1
#endif

#ifndef INCLUDE_vTaskCleanUpResources
#define INCLUDE_vTaskCleanUpResources       0
#endif

#ifndef INCLUDE_vTaskSuspend
#define INCLUDE_vTaskSuspend                1
#endif


#ifndef INCLUDE_vTaskDelayUntil
#  define INCLUDE_vTaskDelayUntil           0
#endif

#ifndef INCLUDE_vTaskDelay
#define INCLUDE_vTaskDelay                  1
#endif

#ifndef INCLUDE_xTaskGetSchedulerState
#define INCLUDE_xTaskGetSchedulerState      1
#endif

/* Cortex-M specific definitions. */
#ifdef __NVIC_PRIO_BITS
 /* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
 #define configPRIO_BITS         __NVIC_PRIO_BITS
#else
 #define configPRIO_BITS         4
#endif

#if configPRIO_BITS > 3
/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   15

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY  5
#else
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY   3
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY  3
#endif

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#ifndef configKERNEL_INTERRUPT_PRIORITY
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#endif

/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#ifndef configMAX_SYSCALL_INTERRUPT_PRIORITY
# define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#endif

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
/* USER CODE BEGIN 1 */   
#ifndef configASSERT
#  define configASSERT( x ) if ((x) == 0) {taskDISABLE_INTERRUPTS(); for( ;; );} 
#endif
/* USER CODE END 1 */

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#ifndef vPortSVCHandler
#define vPortSVCHandler     SVC_Handler
#endif
#ifndef xPortPendSVHandler
#define xPortPendSVHandler  PendSV_Handler
#endif
#ifndef xPortSysTickHandler
#define xPortSysTickHandler HAL_SYSTICK_Callback
#endif

/* IMPORTANT: This define MUST be commented when used with STM32Cube firmware, 
              to prevent overwriting SysTick_Handler defined within STM32Cube HAL */
/* #define xPortSysTickHandler SysTick_Handler */

/* USER CODE BEGIN Defines */   	      
/* Section where parameter definitions can be added (for instance, to override default ones in FreeRTOS.h) */
/* USER CODE END Defines */ 

#endif /* FREERTOS_CONFIG_H */
