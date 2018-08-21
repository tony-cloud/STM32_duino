/**
  ******************************************************************************
    @file    simpleRTCAlarm.ino
    @author  WI6LABS
    @version V1.0.0
    @date    12-December-2017
    @brief   Simple RTC with alarm example.

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

/* Get the rtc object */
STM32RTC& rtc = STM32RTC::getInstance();

/* get compute datetime to set the current initial time */
const byte seconds = BUILD_SEC;
const byte minutes = BUILD_MIN;
const byte hours = BUILD_HOUR;

/* get compute datetime to set the current initial date */
const byte days = BUILD_DAY;
const byte months = BUILD_MONTH;
const byte years = (BUILD_YEAR) % 100;

void setup()
{
  Serial.begin(115200);
  delay(1000); /* wait for serial ready */
  
  Serial.println("Alarm in 10 seconds...");
  rtc.setClockSource(STM32RTC::RTC_LSE_CLOCK);
  rtc.begin(); // initialize RTC 24H format

  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(days, months, years);

  rtc.attachInterrupt(alarmMatch);
  rtc.setAlarmDay(days);
  rtc.setAlarmTime(hours, minutes, seconds + 10);
  rtc.enableAlarm(rtc.MATCH_DHHMMSS);
}

void loop()
{

}

void alarmMatch(void *data)
{
  UNUSED(data);
  rtc.setAlarmEpoch( rtc.getEpoch() + 10);
  Serial.println("Alarm Match! Next alarm in 10 seconds...");
}
