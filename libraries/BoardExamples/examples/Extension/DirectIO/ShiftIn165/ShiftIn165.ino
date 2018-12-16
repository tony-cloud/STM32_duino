/*
  74165  serial input demo
  huaweiwx@sina.com 2018.9.28
*/


#define OUT_PIN   PB2
#define CLK_PIN   PB3
#define nPL_PIN   PB4
//#define nCE_PIN PB5   //connet to GND

ClockedInput<>  sinp165(OUT_PIN, CLK_PIN);
OutputPin       readCLK(nPL_PIN);

#ifdef nCE_PIN
OutputPin outputEnable(nCE_PIN);
#endif

uint8_t read165(void) {
  readCLK.pulse();    //getdate
  uint8_t val = sinp165; //shiftin
}

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);  /*set param: 115200bps 8N1*/
  
#ifdef nCE_PIN
  outputEnable = LOW;
#endif
}

void loop() {
  Serial.println(read165(),HEX);
  
  digitalToggle(LED_BUILTIN);
  delay(1000);
}
