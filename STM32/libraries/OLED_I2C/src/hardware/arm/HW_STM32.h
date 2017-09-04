
#include "stdio.h"
#include "stdlib.h"

void OLED_I2C::_convert_float(char *buf, double num, int width, byte prec)
{
	char format[10];
	
	sprintf(format, "%%%i.%if", width, prec);
	sprintf(buf, format, num);
}


void OLED_I2C::_initTWI()
{
 
}

void OLED_I2C::update()
{
	//noInterrupts();
	_sendTWIcommand(SSD1306_SET_COLUMN_ADDR);
	_sendTWIcommand(0);
	_sendTWIcommand(127);

	_sendTWIcommand(SSD1306_SET_PAGE_ADDR);
	_sendTWIcommand(0);
	_sendTWIcommand(7);
#if 0
	if (_use_hw)					// Send TWI Start
	{
         HWIRE.beginTransmission(SSD1306_ADDR);
        WIRE_WRITE(SSD1306_DATA_CONTINUE);
        /*
		// Set slave address and number of internal address bytes.
		twi->TWI_MMR = (1 << 8) | (SSD1306_ADDR << 16);
		// Set internal address bytes
		twi->TWI_IADR = SSD1306_DATA_CONTINUE;
		// Send start address
         */
       
        
	}
	else
#endif
	{
		_sendStart(SSD1306_ADDR<<1);
		_waitForAck();
		_writeByte(SSD1306_DATA_CONTINUE);
		_waitForAck();
	}
	for (int b=0; b<buf_size; b++)		// Send data
#if 0	
		if (_use_hw)
		{
            /*
			twi->TWI_THR = scrbuf[b];
			while ((twi->TWI_SR & TWI_SR_TXRDY) != TWI_SR_TXRDY) {};
             */
            static byte aa=scrbuf[b];
            WIRE_WRITE(aa);
          
		}
		else
#endif
			{
			_writeByte(scrbuf[b]);
			_waitForAck();
		}

#if 0
	if (_use_hw)					// Send TWI Stop
	{
        HWIRE.endTransmission();
        /*
		// Send STOP condition
		twi->TWI_CR = TWI_CR_STOP;
		while ((twi->TWI_SR & TWI_SR_TXCOMP) != TWI_SR_TXCOMP) {};
         */
	}
	else
#endif
		_sendStop();
	//interrupts();
}

void OLED_I2C::_sendTWIcommand(uint8_t value)
{
#if 0
	if (_use_hw)
	{
        HWIRE.beginTransmission(SSD1306_ADDR);
        WIRE_WRITE(SSD1306_COMMAND);
        WIRE_WRITE(value);
        HWIRE.endTransmission();
        /*
		// Set slave address and number of internal address bytes.
		twi->TWI_MMR = (1 << 8) | (SSD1306_ADDR << 16);
		// Set internal address bytes
		twi->TWI_IADR = SSD1306_COMMAND;

		twi->TWI_THR = value;
		while ((twi->TWI_SR & TWI_SR_TXRDY) != TWI_SR_TXRDY) {};

		// Send STOP condition
		twi->TWI_CR = TWI_CR_STOP;
		while ((twi->TWI_SR & TWI_SR_TXCOMP) != TWI_SR_TXCOMP) {};
         */
	}
	else
#endif
		{
		_sendStart(SSD1306_ADDR<<1);
		_waitForAck();
		_writeByte(SSD1306_COMMAND);
		_waitForAck();
		_writeByte(value);
		_waitForAck();
		_sendStop();
	}
}
