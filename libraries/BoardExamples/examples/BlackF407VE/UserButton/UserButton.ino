/*
  show user button state with LEDs
  
  Black407VE has 3 user buttons and 2 LEDs

  hardware:
    Black407VE ( STM32F407VE )
    http://wiki.stm32duino.com/images/5/5c/STM32_F4VE_SCHEMATIC.PDF

  May 2017, ChrisMicro
*/

/*
  #define BUTTON PA0 // wakeup, active high
  #define BUTTON1 PE3 // active low
  #define BUTTON2 PE4 // active low
*/

#define LED  LED_BUILTIN     // same as LED_BUILTIN, active low
#define LED1 LED1_BUILTIN     // active low

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);

  pinMode(BUTTON, INPUT_PULLDOWN);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);  
}

void loop()
{
  // leds are active low
  digitalWrite(LED, LOW); // led on
  digitalWrite(LED1, LOW); // led on


  // BUTTON is active high
  if  ( digitalRead(BUTTON ) != 0 ) digitalWrite(LED, HIGH); // led off

  // BUTTON and BUTTON1 are active low
  if  ( digitalRead( BUTTON2 ) == 0 ) digitalWrite(LED1, HIGH); // led off
  if  ( digitalRead( BUTTON1 ) == 0 )
  {
    digitalWrite(LED, HIGH); // led off
    digitalWrite(LED1, HIGH); // led off

  }
  
  delay(100);
}
