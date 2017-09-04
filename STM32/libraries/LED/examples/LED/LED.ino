#include <LED.h>

//Led Led1 Led2 is predefined in LED.h

void setup() {
  //  put your setup code here, to run once:
  Led.Init();

#if BOARD_NR_LED>1
  Led1.Init();
#endif

#if BOARD_NR_LED>2
  Led2.Init();
#endif
}

void loop() {
  // put your main code here, to run repeatedly:

  Led.flash(10, 990, 1);   

#if BOARD_NR_LED>1
  Led1.flash(10, 490, 2);
#endif

#if BOARD_NR_LED>2
  Led2.flash(10, 320, 3);
#endif
}
