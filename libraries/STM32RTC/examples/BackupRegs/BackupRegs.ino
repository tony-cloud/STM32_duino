/**
  ******************************************************************************
    @file    BackupRegs.ino
    @author  huaweiwx@sina.com
    @version V1.0.0
    @date    12-December-2017
    @brief   Backup register r/w example.

  ******************************************************************************
    @attention

    <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>

    Redistribution and use in source and binary forms, with or without modification,
    are permitted provided that the following conditions are met:
      1. Redistributions of source code must retain the above copyright notice,
         this list of conditions and the following disclaimer.
      2. Redistributions in binary form must reproduce the above copyright notice,
         this list of conditions and the following disclaimer in the documentation
         and/or other materials provided with the distribution.
      3. Neither the name of STMicroelectronics nor the names of its contributors
         may be used to endorse or promote products derived from this software
         without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  ******************************************************************************
*/

#include <STM32RTC.h>
#include <Streaming.h>

/* Get the rtc object */
STM32RTC& rtc = STM32RTC::getInstance();

/* Change these values to set the current initial default time */
const byte seconds = 0;
const byte minutes = 0;
const byte hours = 18;

/* Change these values to set the current initial default date */
/* 19th June 2018 */
const byte day = 19;
const byte month = 5;
const byte year = 18;

void setup()
{
  Serial.begin(115200);
  delay(2000);

  //select clock souce:  RTC_LSI_CLOCK/RTC_LSE_CLOCK/RTC_HSE_CLOCK/RTC_HSI_CLOCK, default RTC_LSI_CLOCK
  //default STM32RTC::RTC_LSI_CLOCK
  rtc.setClockSource(STM32RTC::RTC_LSE_CLOCK);

  rtc.begin(); // initialize RTC 24H format

  //check bkreg and set the data/time
  if (rtc.getRegister(RTC_BKP_DR1) != 0x32F2) {
    setdata();
    settime();
    rtc.setRegister(RTC_BKP_DR1, 0x32F2);
    for (uint32_t i = 2; i < 10; i++) rtc.setRegister(i, i);
#if RTC_BKP_NUMBER > 10U
    for (uint32_t i = 11; i < 43; i++) rtc.setRegister(i + 5, i);
#endif
    Serial << "day and time be setup auto!\n";
  } else {

 //   settime()
#ifdef STM32F1
    setdata();
    Serial << "F1 setdata, time already setup!\n";
#else
    Serial << "time already setup!\n";
#endif
  }

  // you can use also
  //rtc.setTime(hours, minutes, seconds);
  //rtc.setDate(day, month, year);
  //write backup register

  //read backup register
  for (uint32_t i = 1; i < 10; i++)
    Serial << "RTC_BKP_DR" << i << ": " << _HEX(rtc.getRegister(i)) << "\n";
#if RTC_BKP_NUMBER > 10U
  for (uint32_t i = 11; i < 43; i++)
    Serial << "RTC_BKP_DR" << i << ": " << _HEX(rtc.getRegister(i + 5)) << "\n";
#endif
}

void loop()
{
  // Print date...
  print2digits(rtc.getDay());
  Serial.print("/");
  print2digits(rtc.getMonth());
  Serial.print("/");
  print2digits(rtc.getYear());
  Serial.print(" ");

  // ...and time
  print2digits(rtc.getHours());
  Serial.print(":");
  print2digits(rtc.getMinutes());
  Serial.print(":");
  print2digits(rtc.getSeconds());
  Serial.println();
  delay(1000);
}

void print2digits(int number) {
  if (number < 10) {
    Serial.print("0"); // print a 0 before if the number is < than 10
  }
  Serial.print(number);
}


//  set the time
void settime(void) {
  rtc.setHours(hours);
  rtc.setMinutes(minutes);
  rtc.setSeconds(seconds);
}

// Set the date
void setdata(void) {
  rtc.setDay(day);
  rtc.setMonth(month);
  rtc.setYear(year);
}
