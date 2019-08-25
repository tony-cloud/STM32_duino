/*
  swoViewer.ino use stlink/jlink swo print info demo. huaweiwx@sina.com 2018.12.24

     if we use a stlink/jlink debuger and conected the swo pin, we can print some info to
  stlinkutility/JLinkSWOViewer as serial.

     1 check stlink swo is conected the mcu swopin;
	 2 menu option: SerialSWO
	 3 upload this sketch
	 4 run stlinkutility 
     5 open stlinkutility's serial ware viewer and click the start.
	 
     tested at NUCLEO F401RE
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}
uint32_t cnt = 0;
void loop() {
  // put your main code here, to run repeatedly:
  cnt++;
  Serial.print("hello:");
  Serial.println(cnt);
  delay(1000); 
}
