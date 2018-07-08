/* EXIT template 
 * huaweiwx@sina.com 2017.12.26
 */

#define pbIn BUTTON
#define led LED_BUILTIN

bool state=LOW;

void setup()
{
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  
  digitalWrite(pbIn,HIGH);
  pinMode(pbIn,INPUT);
  attachInterrupt(pbIn, pbIncallback, CHANGE);
}

void loop()                    
{
    digitalWrite(led,state);  
}

void pbIncallback()
{
  state = !state;
}
