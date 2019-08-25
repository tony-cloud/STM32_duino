/*NUCLEO F401 USE hardware LiquidCrestal_I2C 1602 demo*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD defaulte address to 0x27 for a 16 chars and 2 line(1602) display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("nucleo f401");
}

void loop()
{
	// Do nothing here...
}
