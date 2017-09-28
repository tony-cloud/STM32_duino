#include <LED.h>

//Led Led1 Led2 is predefined in LED.h

void setup() {
  //  put your setup code here, to run once:
  for(uint8_t i=0;i<BOARD_NR_LED;i++)
     LEDs[i].Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  for(uint8_t i=0;i<BOARD_NR_LED;i++)
     LEDs[i].flash(10, 240, i+1);
}
