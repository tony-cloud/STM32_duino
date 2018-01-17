
/*
   RTClock lib  demo  by huaweiwx@sina.com 2017.12
*/
#include <RTClock.h>
RTClock  rtc;

#include <cmdline.h>
char cmdline[256];
int ptr = 0;

#include <Streaming.h>
#include <LED.h>

void setup() {
  Led.Init();
  Led.flash(10, 320, 5);

  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
  Serial.println();
  Serial.println("****************************************");
  Serial.println("*             timer demo               *");
  Serial.println("*  Type help Display list of commands  *");
  Serial.println("****************************************");

  rtc.Init(RTC_CLOCK_SOURCE_LSE);/* can select: RTC_CLOCK_SOURCE_LSE/RTC_CLOCK_SOURCE_LSI*/

  if (rtc) {
    rtc.attachEventInterrupt(&showDataTime);
    rtc.attachAlarmInterrupt(&alarm);
  } else
    Serial.println("\nRTC init false!");
}

// the loop routine runs over and over again forever:
volatile uint8_t  alarmdone = 0;
boolean stringComplete = false;  // whether the string is complete
void loop() {
  //cmdline process
  int nStatus;
  if (stringComplete) {
    if (cmdline[0] > ' ') {
      nStatus = CmdLineProcess(cmdline);
      if (nStatus == CMDLINE_BAD_CMD)
        Serial.println(F("Bad cmd!"));
      else if (nStatus == CMDLINE_TOO_MANY_ARGS)
        Serial.println(F("Too many args!"));
      else if (nStatus != 0)
        Serial << "Cmd rtn err_code:" << nStatus;
    }
    ptr = 0;
    stringComplete = false;
  }

  //led
  if (alarmdone)
    Led.flash(500, 500, 1);
  else
    Led.fade();

  //receiver uart input
#if defined(STM32GENERIC)
  serialEvent();
#endif
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    cmdline[ptr++] = inChar;
    cmdline[ptr] = '\0';
    if ((inChar == '\n') || (inChar == '\r')) {
      stringComplete = true;
    }
  }
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

/*setdt 19 12 8 12 08 58*/
int Cmd_setdt(int argc, char *argv[])
{
  uint8_t sYear, sMonth, sDay, sHour, sMinute, sSecond;

  if (argc == 7) {
    sYear = atoi(argv[1]);
    sMonth = atoi(argv[2]);
    sDay = atoi(argv[3]);
    sHour = atoi(argv[4]);
    sMinute = atoi(argv[5]);
    sSecond = atoi(argv[6]);
    rtc.setDataTime(sYear, sMonth, sDay, sHour, sMinute, sSecond);
  }
  return (0);
}

/* alarm 19 12 8 12 08 58*/
int Cmd_alarm(int argc, char *argv[])
{
  uint8_t sHour, sMinute, sSecond;

  if (argc == 4) {
    sHour = atoi(argv[1]);
    sMinute = atoi(argv[2]);
    sSecond = atoi(argv[3]);
    rtc.setAlarmTime(sHour, sMinute, sSecond);
  }
  return (0);
}

//*****************************************************************************
// This function implements the "help" command.  It prints a simple list of the
// available commands with a brief description.
//*****************************************************************************
int Cmd_help(int argc, char *argv[])
{
  tCmdLineEntry *pEntry;
  pEntry = &g_sCmdTable[0];
  Serial.println(F("\r\nAvailable commands:\r\n------------------\n"));
  while (pEntry->pcCmd)
  {
    Serial.print( pEntry->pcCmd);
    Serial.println(pEntry->pcHelp);
    pEntry++;
  }
  return (0);
}

tCmdLineEntry g_sCmdTable[] =
{
  { "help",   Cmd_help,      " : Display list of commands"} ,
  { "?",      Cmd_help,      "    : alias for help"     } ,
  { "setdt",  Cmd_setdt,       " :  set datatime y-m-d-h-m-s"     } ,
  { "alarm",  Cmd_alarm,     " :  set alarmtime hms"  },
  {  0, 0, 0 }
};
