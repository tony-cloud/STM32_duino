#include <Arduino.h>
#include "softWire.h"

//////////////////////////////////////////////////////////////////////////////////	 
//IIC software simulate driver by huaweiwx@sina.com 2017.6.28	   
////////////////////////////////////////////////////////////////////////////////// 

TwoWireSoft::TwoWireSoft(){
}

TwoWireSoft::TwoWireSoft(uint8_t scl,uint8_t sda){
		pdev>sdapin = sda;
		pdev>sclpin = scl;
}

void TwoWireSoft::setSDA(uint8_t sda){
		pdev>sdapin = sda;
}

void TwoWireSoft::setSCL(uint8_t scl){
		pdev>sclpin = scl;
}


//初始化IIC
void TwoWireSoft::begin(void)
{			
  pinMode(pdev>sdapin,OUTPUT);
  pinMode(pdev>sclpin,OUTPUT);
  digitalWrite(pdev>sclpin,HIGH);
  digitalWrite(pdev>sdapin,HIGH);
}

//产生IIC起始信号
void TwoWireSoft::start(void)
{
	pinMode(pdev>sdapin,OUTPUT);     //sda线输出
	digitalWrite(pdev>sdapin,HIGH);	  	  
	digitalWrite(pdev>sclpin,HIGH);
	delayMicroseconds(4);
 	digitalWrite(pdev>sdapin,LOW);//START:when CLK is high,DATA change form high to low 
	delayMicroseconds(4);
	digitalWrite(pdev>sclpin,LOW);//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void TwoWireSoft::stop(void)
{
	pinMode(pdev>sdapin,OUTPUT);//sda线输出
	digitalWrite(pdev>sclpin,LOW);
	digitalWrite(pdev>sdapin,LOW);//STOP:when CLK is high DATA change form low to high
 	delayMicroseconds(4);
	digitalWrite(pdev>sclpin,HIGH); 
	digitalWrite(pdev>sdapin,HIGH);//发送I2C总线结束信号
	delayMicroseconds(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t TwoWireSoft::waitAck(void)
{
	uint8_t ucErrTime=0;
	pinMode(pdev>sdapin,INPUT);      //SDA设置为输入  
	digitalWrite(pdev>sdapin,HIGH);delayMicroseconds(1);	   
	digitalWrite(pdev>sclpin,HIGH);delayMicroseconds(1);	 
	while(digitalRead(pdev>sdapin))
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			this->stop();
			return 1;
		}
	}
	digitalWrite(pdev>sclpin,LOW);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void TwoWireSoft::ack(void)
{
	digitalWrite(pdev>sclpin,LOW);
	pinMode(pdev>sdapin,OUTPUT);
	digitalWrite(pdev>sdapin,LOW);
	delayMicroseconds(2);
	digitalWrite(pdev>sclpin,HIGH);
	delayMicroseconds(2);
	digitalWrite(pdev>sclpin,LOW);
}
//不产生ACK应答		    
void TwoWireSoft::nAck(void)
{
	digitalWrite(pdev>sclpin,LOW);
	pinMode(pdev>sdapin,OUTPUT);
	digitalWrite(pdev>sdapin,HIGH);
	delayMicroseconds(2);
	digitalWrite(pdev>sclpin,HIGH);
	delayMicroseconds(2);
	digitalWrite(pdev>sclpin,LOW);
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void TwoWireSoft::sendByte(uint8_t txd)
{                        
    uint8_t t;   
	pinMode(pdev>sdapin,OUTPUT); 	    
    digitalWrite(pdev>sclpin,LOW);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        digitalWrite(pdev>sdapin,(txd&0x80)>>7);
        txd<<=1; 	  
		delayMicroseconds(2);   //对TEA5767这三个延时都是必须的
		digitalWrite(pdev>sclpin,HIGH);
		delayMicroseconds(2); 
		digitalWrite(pdev>sclpin,LOW);	
		delayMicroseconds(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t TwoWireSoft::readByte(unsigned char ack)
{
	unsigned char i,receive=0;
	pinMode(pdev>sdapin,INPUT);//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        digitalWrite(pdev>sclpin,LOW); 
        delayMicroseconds(2);
		digitalWrite(pdev>sclpin,HIGH);
        receive<<=1;
        if(digitalRead(pdev>sdapin))receive++;   
		delayMicroseconds(1); 
    }					 
    if (!ack)
        this->nAck();//发送nACK
    else
        this->ack(); //发送ACK   
    return receive;
}



























