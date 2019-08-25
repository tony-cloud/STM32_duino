/*
   jlinkRTT.ino use J-Link RTT Viewer Terminals by huaweiwx@sina.com 2018.11.25

   1 jlinkRTT is pre-define instance of JLINKRTT  class.
   2 Serial communication Menu option selected JlinkRTT to set default Serial use jlnkRTT.
   3 run the JLinkRTTViewer.exe  from the path:C:\Program Files\SEGGER\JLink_V614b\JLinkRTTViewer.exe
   4 at Transmit Text window you can keyin string and click 'Enter' for send
*/

#include "JlinkRTT.h"
#define mySerial jlinkRTT

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);

  // mySerial.begin(); /*compatible with Serial , jlinkRTT do nothing */
  setStdPrintDev(&mySerial, STDERR_FILENO); /* debug and error output infomation  redirect from Serial to mySerial */
}

int count = 0;
void loop() {
  count++;

  Serial.print("This is Serial output! count = ");
  Serial.println(count);
 
  // put your main code here, to run repeatedly:
  mySerial.print("This is jlinkRTT output! count = ");
  mySerial.println(count);

  debug("This is debug output: cnt = %d\r\n",count);

  digitalToggle(LED_BUILTIN);
  delay(1000);
}
