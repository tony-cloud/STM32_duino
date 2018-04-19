void setup() {
  SerialUSB.begin(115200);
  Serial1.begin(115200);
  while (!SerialUSB);
  for (;;) {
    if (SerialUSB.available()) {
      uint8_t c = SerialUSB.read();
      Serial1.write(c);
    }
    if (Serial1.available()) {
      uint8_t c = Serial1.read();
      SerialUSB.write(c);
    }
  }
}
void loop() {}
