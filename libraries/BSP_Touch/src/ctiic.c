#include <Arduino.h>
#if __has_include("bsp.h")
#  include "bsp.h"
#endif
#include "ctiic.h"

#if defined(CT_SCL_PIN) && defined(CT_SDA_PIN)
   	   		   
//IO��������
#define CT_SDA_IN   pinMode(CT_SDA_PIN,INPUT)
#define CT_SDA_OUT  pinMode(CT_SDA_PIN,OUTPUT)

//IO��������	 
#define CT_IIC_SCL(x)    digitalWrite(CT_SCL_PIN,x) 			 /*SCL*/
#define CT_IIC_SDA(x)    digitalWrite(digitalWrite(CT_SDA_PIN,x) /*SDA*/
#define CT_READ_SDA      digitalRead(CT_SDA_PIN)  			//����SDA 

//////////////////////////////////////////////////////////////////////////////////

//���ݴ���оƬIIC�ӿڳ�ʼ��
void CT_IIC_Init(void)
{					     
 	pinMode(CT_SCL_PIN,OUTPUT);
 	pinMode(CT_SDA_PIN,OUTPUT);
	digitalWrite(CT_SCL_PIN,HIGH);
	digitalWrite(CT_SDA_PIN,HIGH);	 
}

//����IIC��ʼ�ź�
void CT_IIC_Start(void)
{
	CT_SDA_OUT;     //sda�����
	CT_IIC_SDA(HIGH);	  	  
	CT_IIC_SCL(HIGH);
	delay_us(10);
 	CT_IIC_SDA(LOW);//START:when CLK is high,DATA change form high to low 
	delay_us(10);
	CT_IIC_SCL(LOW);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void CT_IIC_Stop(void)
{
	CT_SDA_OUT;//sda�����
	CT_IIC_SCL(HIGH);
	delay_us(10);
	CT_IIC_SDA(LOW);//STOP:when CLK is high DATA change form low to high
	delay_us(10);
	CT_IIC_SDA(HIGH);//����I2C���߽����ź�
	delay_us(10);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t CT_IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	CT_SDA_IN;      //SDA����Ϊ����  
	CT_IIC_SDA(HIGH);delay_us(1);	   
	CT_IIC_SCL(HIGH);delay_us(1);	 
	while(CT_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		} 
	}
	CT_IIC_SCL(LOW);//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void CT_IIC_Ack(void)
{
	CT_IIC_SCL(LOW);
	CT_SDA_OUT();
	CT_IIC_SDA(LOW);
	delay_us(10);
	CT_IIC_SCL(HIGH);
	delay_us(10);
	CT_IIC_SCL(LOW);
}
//������ACKӦ��		    
void CT_IIC_NAck(void)
{
	CT_IIC_SCL(LOW);
	CT_SDA_OUT();
	CT_IIC_SDA(HIGH);
	delay_us(10);
	CT_IIC_SCL(HIGH);
	delay_us(10);
	CT_IIC_SCL(LOW);
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void CT_IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	CT_SDA_OUT(); 	    
    CT_IIC_SCL(LOW);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        CT_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	      
		CT_IIC_SCL(HIGH);
		delay_us(10);
		CT_IIC_SCL(LOW);	
		delay_us(10);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t CT_IIC_Read_Byte(unsigned char ack)
{
	uint8_t i,receive=0;
 	CT_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        CT_IIC_SCL(LOW); 	    	   
		delay_us(30);
		CT_IIC_SCL(HIGH);  
		receive<<=1;
		if(CT_READ_SDA)receive++;   
	}	  				 
	if (!ack)CT_IIC_NAck();//����nACK
	else CT_IIC_Ack(); //����ACK   
 	return receive;
}


#endif //define(CT_SCL_PIN)&&define(CT_SDA_PIN)


























