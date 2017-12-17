
#ifndef _RTCLOCK_H_
#define _RTCLOCK_H_

#ifdef STM32F4
	#define RTC_ASYNCH_PREDIV       (0x7f)   // /* 0U 31U 1ms /(127+1)*(255+1) = 32768 1s*/
	#define RTC_SYNCH_PREDIV        (0xff)    //
	#define RTC_ASYNCH_PREDIV_HSE   (99)   // 99U 
	#define RTC_SYNCH_PREDIV_HSE    (99)    // 1000 hz
	#define RCC_RTCCLKSOURCE_1MHZ   ((uint32_t)((uint32_t)RCC_BDCR_RTCSEL | (uint32_t)((HSE_VALUE/1000000U) << 16U)))	  
#endif

typedef enum RTC_clockSouce {
RTC_CLOCK_SOURCE_NO_CLK,
RTC_CLOCK_SOURCE_LSE,
RTC_CLOCK_SOURCE_LSI,
RTC_CLOCK_SOURCE_HSE,
}RTC_clockSouce;

/* USER CODE BEGIN Includes */
typedef struct
{
  uint16_t year;
  uint8_t  month;
  uint8_t  day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t  week;
} RTC_calendar_TypeDef;

#ifdef __cplusplus


class RTClock {
 public:
 	RTClock(){
	};
	void Init(uint32_t source);
	HAL_StatusTypeDef
		setDataTime(uint16_t syear, uint8_t smon, uint8_t sday, uint8_t hour, uint8_t min, uint8_t sec),
		setAlarmTime(uint8_t hour, uint8_t min, uint8_t sec,uint8_t week=0),
	void getDataTime(void);
	uint8_t getWeek(uint16_t year, uint8_t month, uint8_t day);
	
	void writeBackupReg(uint32_t BackupRegister, uint32_t Data);
	uint32_t readBackupReg(uint32_t BackupRegister);
	
	operator bool(){
         return (this->status)?true:false;
	};

	void attachEventInterrupt(void(*callback)(void)); 
	void detachEventInterrupt(void);
	
    void attachAlarmInterrupt(void(*callback)(void)); 
	void detachAlarmInterrupt(void);
	
    void attachTamperInterrupt(void(*callback)(void)); 
	void detachTamperInterrupt(void);

	RTC_calendar_TypeDef *pCalendar =&calendar;
	
 private:
	rtcSource(uint32_t source);
    uint8_t status = false;
	RTC_calendar_TypeDef calendar;
};

#endif //__cplusplus

#endif //_RTCLOCK_H_
