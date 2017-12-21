/*
   RTClock lib alarm  demo  by huaweiwx@sina.com 2017.12
   for L0/1/4  F2/3/4/7
   F1 un complated.
*/

#include <LED.h>
#include <RTClock.h>

RTClock  rtc;

void setup() {
  Led.Init();
  Led.flash(10, 320, 5);

  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);

  rtc.Init(RTC_CLOCK_SOURCE_LSE);/* can select: RTC_CLOCK_SOURCE_LSE/RTC_CLOCK_SOURCE_LSI*/

  if (rtc) {


    /*--------------------------------------------------------------------------------------*/
    rtc.setDataTime(2017, 12, 19, 16, 25, 10);
    /*    Run once only When  there is a backup battery and used  RTC_CLOCK_SOURCE_LSE option.
          当选择低频晶振且装有后备电池时仅需运行一次
      --------------------------------------------------------------------------------------*/

    rtc.attachEventInterrupt(&showDataTime);

    //test alarm
    rtc.setAlarmTime(16, 25, 30);
    rtc.attachAlarmInterrupt(&alarm);
  }
  else
    Serial.println("\nRTC init false!");

  Serial.println("\nSnoring...");
}

// the loop routine runs over and over again forever:
volatile uint8_t  alarmdone = 0;
void loop() {
  if (alarmdone)
    Led.flash(100, 100, 1);
  else
    Led.flash(500, 500, 1);
}

const char* weekStr[7] = {
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday",
  "Saturday",
  "Sunday",
};

void showDataTime(void)
{
  rtc.getDataTime();
  Serial << "data: " << rtc.pCalendar->year << "-"  <<  rtc.pCalendar->month << "-" <<  rtc.pCalendar->day ;
  Serial << "   time: " <<  rtc.pCalendar->hour << ":"  <<  rtc.pCalendar->minute << ":" <<  rtc.pCalendar->second << "  " <<  weekStr[ rtc.pCalendar->week - 1] << "\n";
}

void alarm(void) {
  Serial << "!!! alarm!!!!\n";
  alarmdone = 1;
}
