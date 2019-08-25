/*
  swoDebugOut.ino use stlink/jlink swo print debug info demo. huaweiwx@sina.com 2018.12.24

     if we use a stlink/jlink debuger and conected the swo pin, we can print some info to
  stlinkutility/JLinkSWOViewer as serial.

   SerialSWO is the predefine instance of SWOclass

   1 check stlink swo is conected the mcu swopin;
	 2 menu option: Serial as default app output
	 3 upload this sketch
	 4 run stlinkutility
   5 open stlinkutility's serial ware viewer and click the start.

     tested at NUCLEO F401RE
*/

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);   /* This is  the default stdout device */

  setStdPrintDev(&SerialSWO, STDERR_FILENO); /* set the SerialSWO as stderr output device */
//  SerialSWO.begin(115200);  /*compatible with Serial , SerialSWO do nothing */
}

uint32_t cnt = 0;
void loop() {
  digitalToggle(LED_BUILTIN);   // turn the LED on (HIGH is the voltage level)
  cnt++;
  debug("This is debug output! cnt = %d\n", cnt);
  SerialSWO.printf("This SWO output! cnt = %d\n", cnt);
  Serial.printf("This is Serial output! %d\n", cnt);
  delay(1000);                  // wait for a second
}

