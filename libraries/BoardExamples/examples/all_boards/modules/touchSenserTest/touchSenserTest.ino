
//#define VCC_PIN
#define GND_PIN PB_8
//#define SENSER_PIN PB_9

void setup() {
#ifdef GND_PIN
  pinMode(GND_PIN, OUTPUT);
  digitalWrite(GND_PIN, LOW); /*GND*/
#endif
#ifdef VCC_PIN
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(VCC_PIN, HIGH); /*VCC.*/
  delay(1000);     /*wait for eeprom power ready*/
#endif
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SENSER_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(SENSER_PIN))
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);
}