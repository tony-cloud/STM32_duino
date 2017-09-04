#ifndef __FLASH_STM32_H__
#define __FLASH_STM32_H__

#if defined(STM32F4)||defined(STM32F7)
#  include "STM32F4FlashBlock.h"
#  define STM32EmbeddedFlashBlock  STM32F4EmbeddedFlashBlock
#else //F0 1 2 3 L0 1 4
#  define STM32EmbeddedFlashBlock  STM32F1EmbeddedFlashBlock
#  include "STM32F1FlashBlock.h"
#endif

#include "FlashVariables.h"
#include "FlashBlockDevice.h"
#include "MassStorage.h"
#include "FlashBlockFat.h"


#endif
