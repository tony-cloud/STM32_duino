//#include <FreeRTOS_ARDUINO.h>

#ifdef STM32GENERIC
#  include <FreeRTOS_STM.h>

#elif defined(__AVR__)
#  include <FreeRTOS_AVR.h

#else
#  error "!!unsupport this device!!"
#endif