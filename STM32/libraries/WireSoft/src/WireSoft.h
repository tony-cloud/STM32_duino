/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 LeafLabs LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file Wire.h
 * @author Trystan Jones <crenn6977@gmail.com>
 * @brief Wire library, uses the WireBase to create the primary interface
 *        while keeping low level interactions invisible to the user.
 */

/*
 * Library updated by crenn to follow new Wire system.
 * Code was derived from the original Wire for maple code by leaflabs and the
 * modifications by gke and ala42.
 */

#ifndef _WIRESOFT_H_
#define _WIRESOFT_H_

#if __has_include("configs/i2cEepromConfig.h")
#  include "configs/i2cEepromConfig.h"
#endif

#include "WireBase.h"


#define SOFT_STANDARD 27
#define SOFT_FAST 0


//#define I2C_DELAY(x) {uint32 time=micros(); while(time>(micros()+x));}
#define I2C_DELAY(x) do{for(int i=0;i<x;i++) {asm volatile("nop");}}while(0)

#define BUFFER_LENGTH 32


class TwoWireSoft : public WireBase {
 public:
    uint8_t	i2c_delay;
    uint8_t	scl_pin;
    uint8_t	sda_pin;
	
    void setPins(uint8_t sda,uint8_t scl){
		 sda_pin = sda;
	     scl_pin = scl;
		};
    /*
     * Sets the SCL line to HIGH/LOW and allow for clock stretching by slave
     * devices
     */
    void sclPin(bool);

    /*
     * 
     */
    void sdaPin(bool);//Sets the SDA line to HIGH/LOW

    /*
     * Creates a Start condition on the bus
     */
    void i2c_start();

    /*
     * Creates a Stop condition on the bus
     */
    void  i2c_stop();

    /*
     * Gets an ACK condition from a slave device on the bus
     */
    bool i2c_get_ack();

    /*
     * Creates a ACK condition on the bus
     */
    void i2c_send_ack();

    /*
     * Creates a NACK condition on the bus
     */
    void i2c_send_nack();

    /*
     * Shifts in the data through SDA and clocks SCL for the slave device
     */
    uint8_t i2c_shift_in();

    /*
     * Shifts out the data through SDA and clocks SCL for the slave device
     */
    void i2c_shift_out(uint8_t);
	
	

	
 protected:
    /*
     * Processes the incoming I2C message defined by WireBase
     */
    uint8_t process();
 public:
    /*
     * Accept pin numbers for SCL and SDA lines. Set the delay needed
     * to create the timing for I2C's Standard Mode and Fast Mode.
     */
    TwoWireSoft(uint8_t sda=SDA, uint8_t scl=SCL, uint8_t delay=SOFT_STANDARD);

    /*
     * Sets pins SDA and SCL to OUPTUT_OPEN_DRAIN, joining I2C bus as
     * master. This function overwrites the default behaviour of
     * .begin(uint8_t) in WireBase
     */
    void begin(uint8_t = 0x00);

    /*
     * Sets pins SDA and SCL to INPUT
     */
	void end();	
	
    /*
     * If object is destroyed, set pin numbers to 0.
     */
    ~TwoWireSoft();
};

extern TwoWireSoft WireSoft;

#endif // _WIRE_H_

