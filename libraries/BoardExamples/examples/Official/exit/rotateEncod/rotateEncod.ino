/* EXIT rotaryEncoder template
   huaweiwx@sina.com 2018.6.16
*/

#define CLK  PA2
#define DAT  PA3
#define SELE  PA4

#define LED LED_BUILTIN

int COUNT = 0;

void setup()
{
  Serial.begin(115200);

  pinMode(CLK, INPUT);
  pinMode(DAT, INPUT);
  pinMode(SELE, INPUT);

  pinMode(LED, OUTPUT);

  attachInterrupt(CLK, RoteStateChanged, FALLING);
  // attachInterrupt(SELE, SELEState, FALLING);
}

void loop()
{
  if  (!(digitalRead(SELE)))
  {
    COUNT = 0;
    Serial.println("STOP COUNT = 0");
    delay (2000);
  }
  Serial.println(COUNT);
}

//-------------------------------------------
void RoteStateChanged() //When CLK  FALLING READ DAT
{
  if  (digitalRead(DAT)) // When DAT = HIGH IS FORWARD
  {
    COUNT++;
    digitalWrite(LED, HIGH);
  }
  else                   // When DAT = LOW IS BackRote
  {
    COUNT--;
    digitalWrite(LED, LOW);
  }
}

