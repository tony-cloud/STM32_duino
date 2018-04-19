//IO��������  PB3
#include <Arduino.h>
#include "util/delay.h"
#if __has_include("bsp.h")
#  include "bsp.h"
#endif

#ifndef DS18B20_DQ_PIN
#define  DS18B20_DQ_PIN 0xFF
#endif

#define DS18B20_IO_IN   pinMode(ds18b02DqPin,INPUT_PULLUP)
#define DS18B20_IO_OUT  pinMode(ds18b02DqPin,OUTPUT)

////IO��������	PB3										   
#define	DS18B20_DQ_OUT(x) digitalWrite(ds18b02DqPin,x) //���ݶ˿�	PB3
#define	DS18B20_DQ_IN()   digitalRead(ds18b02DqPin)  //���ݶ˿�	PB3 

#include "DS18B20.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK MiniSTM32������
//DS18B20��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/4/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
  

//��λDS18B20
static uint8_t ds18b02DqPin = DS18B20_DQ_PIN;
void DS18B20_SetPin(uint8_t pin)	   
{                 
	ds18b02DqPin = pin;
}

void DS18B20_Rst(void)	   
{                 
	DS18B20_IO_OUT; //SET PA0 OUTPUT
    DS18B20_DQ_OUT(LOW); //����DQ
    _delay_us(750);    //����750us
    DS18B20_DQ_OUT(HIGH); //DQ=1 
	_delay_us(15);     //15US
}
//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
uint8_t DS18B20_Check(void) 	   
{   
	uint8_t retry=0;
	DS18B20_IO_IN;//SET PA0 INPUT	 
    while (DS18B20_DQ_IN()&&retry<200)
	{
		retry++;
		_delay_us(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!DS18B20_DQ_IN()&&retry<240)
	{
		retry++;
		_delay_us(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}
//��DS18B20��ȡһ��λ
//����ֵ��1/0
uint8_t DS18B20_ReadBit(void) 			 // read one bit
{
    uint8_t data;
	DS18B20_IO_OUT;//SET PA0 OUTPUT
    DS18B20_DQ_OUT(LOW); 
	_delay_us(2);
    DS18B20_DQ_OUT(HIGH); 
	DS18B20_IO_IN;//SET PA0 INPUT
	_delay_us(12);
	if(DS18B20_DQ_IN())data=1;
    else data=0;	 
    _delay_us(50);           
    return data;
}
//��DS18B20��ȡһ���ֽ�
//����ֵ������������
uint8_t DS18B20_ReadByte(void)	/*read one byte*/
{        
    uint8_t j,dat;
    dat=0;
	for (volatile uint8_t i=1;i<=8;i++) 
	{
        j=DS18B20_ReadBit();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}
//дһ���ֽڵ�DS18B20
//dat��Ҫд����ֽ�
void DS18B20_WriteByte(uint8_t dat)     
 {             
    uint8_t testb;
	DS18B20_IO_OUT;//SET PB3 OUTPUT;
    for (volatile uint8_t j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_DQ_OUT(LOW);// Write 1
            _delay_us(2);                            
            DS18B20_DQ_OUT(HIGH);
            _delay_us(60);             
        }
        else 
        {
            DS18B20_DQ_OUT(LOW);// Write 0
            _delay_us(60);             
            DS18B20_DQ_OUT(HIGH);
            _delay_us(2);                          
        }
    }
}

//��ʼ�¶�ת��
void DS18B20_Start(void)// ds1820 start convert
{   						               
    DS18B20_Rst();	   
	DS18B20_Check();	 
    DS18B20_WriteByte(0xcc);// skip rom
    DS18B20_WriteByte(0x44);// convert
} 
//��ʼ��DS18B20��IO�� DQ ͬʱ���DS�Ĵ���
//����1:������
//����0:����

//JTAGģʽ����,��������JTAG��ģʽ
//mode:jtag,swdģʽ����;00/ȫʹ��;01/ʹ��SWD;10/ȫ�ر�;	   
//#define JTAG_SWD_ENABLE    0X00		  
//#define SWD_ENABLE         0X01
//#define JTAG_SWD_DISABLE   0X02
//void JTAG_Set(uint8_t mode)
//{
//	u32 temp;
//	temp=mode;
//	temp<<=25;
//	RCC->APB2ENR|=1<<0;     //��������ʱ��	   
//	AFIO->MAPR&=0XF8FFFFFF; //���MAPR��[26:24]
//	AFIO->MAPR|=temp;       //����jtagģʽ
//}
     	 
uint8_t DS18B20_Init(void)
{
    DS18B20_IO_OUT;
	DS18B20_DQ_OUT(HIGH);
	DS18B20_Rst();
	return DS18B20_Check();
}

//��ds18b20�õ��¶�ֵ
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-550~1250�� 
int DS18B20_GetTemp(void)
{
    uint8_t temp;
    uint8_t TL,TH;
	int32_t tem;
    DS18B20_Start ();                    // ds1820 start convert
    DS18B20_Rst();
    DS18B20_Check();	 
    DS18B20_WriteByte(0xcc);// skip rom
    DS18B20_WriteByte(0xbe);// convert	    
    TL=DS18B20_ReadByte(); // LSB   
    TH=DS18B20_ReadByte(); // MSB  
	    	  
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;//�¶�Ϊ��  
    }else temp=1;//�¶�Ϊ��	  	  
    tem=TH; //��ø߰�λ
    tem<<=8;    
    tem+=TL;//��õװ�λ
    tem=(int32_t)tem*625/1000;    //ת��     
	if(temp)return tem;  //�����¶�ֵ*10
	else return -tem;    
}
















