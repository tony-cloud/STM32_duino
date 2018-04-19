#include <Arduino.h>
#include "wireSoft.h"

//////////////////////////////////////////////////////////////////////////////////	 
//IIC software simulate driver by huaweiwx@sina.com 2017.6.28	   
////////////////////////////////////////////////////////////////////////////////// 

TwoWireSoft::TwoWireSoft(){
}

TwoWireSoft::TwoWireSoft(uint8_t sda,uint8_t scl){
		this->setPins(sda,scl);
}

void TwoWireSoft::setPins(uint8_t sda,uint8_t scl){
		pdev->sda = sda;
		pdev->scl = scl;
}


//��ʼ��IIC
void TwoWireSoft::begin(void)
{			
  pinMode(pdev->sda,OUTPUT_OD);
  pinMode(pdev->scl,OUTPUT);
  digitalWrite(pdev->scl,HIGH);
  digitalWrite(pdev->sda,HIGH);
}

//����IIC��ʼ�ź�
void TwoWireSoft::start(void)
{
	pinMode(pdev->sda,OUTPUT_OD);     //sda�����
	digitalWrite(pdev->sda,HIGH);	  	  
	digitalWrite(pdev->scl,HIGH);
	delayMicroseconds(4);
 	digitalWrite(pdev->sda,LOW);//START:when CLK is high,DATA change form high to low 
	delayMicroseconds(4);
	digitalWrite(pdev->scl,LOW);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void TwoWireSoft::stop(void)
{
	pinMode(pdev->sda,OUTPUT_OD);//sda�����
	digitalWrite(pdev->scl,LOW);
	digitalWrite(pdev->sda,LOW);//STOP:when CLK is high DATA change form low to high
 	delayMicroseconds(4);
	digitalWrite(pdev->scl,HIGH); 
	digitalWrite(pdev->sda,HIGH);//����I2C���߽����ź�
	delayMicroseconds(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t TwoWireSoft::waitAck(void)
{
	uint8_t ucErrTime=0;
	pinMode(pdev->sda,INPUT);      //SDA����Ϊ����  
	digitalWrite(pdev->sda,HIGH);delayMicroseconds(1);	   
	digitalWrite(pdev->scl,HIGH);delayMicroseconds(1);	 
	while(digitalRead(pdev->sda))
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			this->stop();
			return 1;
		}
	}
	digitalWrite(pdev->scl,LOW);//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void TwoWireSoft::ack(void)
{
	digitalWrite(pdev->scl,LOW);
	pinMode(pdev->sda,OUTPUT_OD);
	digitalWrite(pdev->sda,LOW);
	delayMicroseconds(2);
	digitalWrite(pdev->scl,HIGH);
	delayMicroseconds(2);
	digitalWrite(pdev->scl,LOW);
}
//������ACKӦ��		    
void TwoWireSoft::nAck(void)
{
	digitalWrite(pdev->scl,LOW);
	pinMode(pdev->sda,OUTPUT_OD);
	digitalWrite(pdev->sda,HIGH);
	delayMicroseconds(2);
	digitalWrite(pdev->scl,HIGH);
	delayMicroseconds(2);
	digitalWrite(pdev->scl,LOW);
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void TwoWireSoft::sendByte(uint8_t txd)
{                        
    uint8_t t;   
	pinMode(pdev->sda,OUTPUT_OD); 	    
    digitalWrite(pdev->scl,LOW);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        digitalWrite(pdev->sda,(txd&0x80)>>7);
        txd<<=1; 	  
		delayMicroseconds(2);   //��TEA5767��������ʱ���Ǳ����
		digitalWrite(pdev->scl,HIGH);
		delayMicroseconds(2); 
		digitalWrite(pdev->scl,LOW);	
		delayMicroseconds(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
uint8_t TwoWireSoft::readByte(unsigned char ack)
{
	unsigned char i,receive=0;
	pinMode(pdev->sda,INPUT);//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        digitalWrite(pdev->scl,LOW); 
        delayMicroseconds(2);
		digitalWrite(pdev->scl,HIGH);
        receive<<=1;
        if(digitalRead(pdev->sda))receive++;   
		delayMicroseconds(1); 
    }					 
    if (!ack)
        this->nAck();//����nACK
    else
        this->ack(); //����ACK   
    return receive;
}



























