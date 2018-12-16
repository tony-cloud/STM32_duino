/* EXIT rotaryEncoder template
   huaweiwx@sina.com 2018.6.16
*/
#include "util/bitband.h"

#define DAT  PA3
#define CLK  PA2
#define SELE  PA4
#define LED LED_BUILTIN


BB_PIN dat(DAT);
BB_PIN clk(CLK);
BB_PIN sele(SELE);

BB_PIN led(LED);

int changed = 0;
int   count = 0;

void setup() {
  Serial.begin(115200);

  dat.mode(INPUT);
  clk.mode(INPUT);
  sele.mode(INPUT);

  led.mode(OUTPUT);

  clk.attach(RoteStateChanged, FALLING);

  //dat.attach(datPinChanged, FALLING);
  //sele.attach(SELEState, FALLING);
}

void loop() {
  if (changed) {
    changed = 0;
    Serial.println(count);
  } else if (sele.read() == 0) {
    count = 0;
    Serial.println("STOP COUNT = 0");
    delay (2000);
  }
}

//                           _______
//               Pin1 ______|       |___ Pin1(dat)
// negative <---         _______                    --> positive
//               Pin2 __|       |_______ Pin2(clk)

void RoteStateChanged() { //When CLK  FALLING READ DAT
  if  (dat)  {  // When DAT = HIGH IS FORWARD
    count++;
    led = 1;
  } else   {                 // When DAT = LOW IS BackRote
    count--;
    led = 0;
  }
  changed = 1;
}

