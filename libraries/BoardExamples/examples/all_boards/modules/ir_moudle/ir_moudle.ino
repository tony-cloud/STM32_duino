

#define IR_VCC PA0
#define GND_PIN PA1
#define IR_DO  PA4
#define IR_AO  PB0

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
#ifdef GND_PIN
  pinMode(GND_PIN, OUTPUT);
  digitalWrite(GND_PIN, LOW);
#endif
#ifdef VCC_PIN
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(VCC_PIN, HIGH);
#endif

  pinMode(IR_DO, INPUT);
  pinMode(IR_AO, INPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_BUILTIN, digitalRead(IR_DO));
  Serial.print("D0=");
  Serial.print(digitalRead(IR_DO));
  Serial.print("  A0=");
  Serial.println(analogRead(IR_AO));
  delay(1000);
}
