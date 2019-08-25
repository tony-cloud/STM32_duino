/* 
   Serial Port usage and naming example.
   Most of the STM32 microcontrollers have more than one serial port.
   The STM32GENERIC Arduino framwork allows you to access this ports.

   A menu option named Serial is equivalent to the following physical or virtual serial port:
    SerialUSB                 virtual serial USB port
    SerialUART1               physical serial interface   
    SerialUART2               physical serial interface
    ...                       ...
    
    The SerialUARTx are in the data sheets sometimes called USARTx/UARTx or LEUSARTx.
    Check the datasheed of your on board microcontroller to which pins this  USARTx/UARTx or LEUSARTx. are connected.
 
    ! Do it in advance before programming the routine to avoid software induced short cuts !
    April 2017, ChrisMicro
 */

//#define Serial SerialUART2 
//#define Serial SerialUART3

void setup() 
{
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);
  delay(1000);
  Serial.println("Serial Port Example,Press any key to being");
  while (!Serial.available()){ //wait for usb_serial input a char; 
   digitalToggle(LED_BUILTIN);
   delay(100);
  }
  Serial.println("just counting up");
}

int Counter=0;

void loop() 
{
  Serial.println(Counter); 
  Counter++;
  delay(1000);
}

