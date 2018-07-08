
extern void testmain(void);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(2000);
  testmain();
}

void loop() {
  // put your main code here, to run repeatedly:
}
