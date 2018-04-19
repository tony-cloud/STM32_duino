#include <Arduino.h>

#include "at24cxx.h"

#ifndef AT24CXX_SDA
# define   AT24CXX_SDA SDA
#endif

#ifndef AT24CXX_SCL
# define   AT24CXX_SCL SCL
#endif


EXTEEPROM::EXTEEPROM(uint16_t _dev)
       :TwoWireSoft(){

	   pdata->dev = _dev;
	   
       this->setPins(AT24CXX_SDA,AT24CXX_SCL);
 
#ifdef AT24CXX_A2A1A0
       pdata->adr = (0x50 | AT24CXX_A2A1A0)<<1;   //0x50|A2A1A0
#else
       pdata->adr = 0x50<<1 ; //A2A1A0=0      
#endif
       pdata->ctrl = 0;	
}

EXTEEPROM::EXTEEPROM (uint8_t sda,uint8_t scl)
       :TwoWireSoft(sda,scl){
       pdata->ctrl = 0;	
}

void EXTEEPROM::setPins(uint8_t sda,uint8_t scl){
       TwoWireSoft::setPins(sda,scl);
}

//��ʼ��IIC�ӿ�

uint8_t EXTEEPROM::begin(uint8_t _devAdr)
{
    if (_devAdr >= 0xA0)  //rw addr
		pdata->adr = _devAdr;
    if (_devAdr >= 0x50)   //dev addr
       pdata->adr = (_devAdr<<1);  //0x5x
	else if(_devAdr > 0)        //a2a1a0 adr else use default rw addr;
       pdata->adr = (0x50 | _devAdr)<<1;
   
	TwoWireSoft::begin();
	return ((pdata->ctrl)?this->check():0);
}

uint8_t EXTEEPROM::begin(int _devAdr)
{
    return EXTEEPROM::begin((uint8_t)_devAdr);
}

//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
uint8_t EXTEEPROM::readOneByte(uint16_t ReadAddr)
{				  
	uint8_t temp=0;		  	    																 
    TwoWireSoft::start();  
	if((pdata->dev)>AT24C16)
	{
		TwoWireSoft::sendByte(pdata->adr);	   //����д����
		TwoWireSoft::waitAck();
		TwoWireSoft::sendByte(ReadAddr>>8);//���͸ߵ�ַ	    
	}else TwoWireSoft::sendByte((pdata->adr)+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	   
	TwoWireSoft::waitAck(); 
    TwoWireSoft::sendByte(ReadAddr%256);   //���͵͵�ַ
	TwoWireSoft::waitAck();	    
	TwoWireSoft::start();  	 	   
	TwoWireSoft::sendByte((pdata->adr)+1);           //�������ģʽ			   
	TwoWireSoft::waitAck();	 
    temp=TwoWireSoft::readByte(0);		   
    TwoWireSoft::stop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void EXTEEPROM::writeOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
    TwoWireSoft::start();  
	if((pdata->dev)>AT24C16)
	{
		TwoWireSoft::sendByte(pdata->adr);	    //����д����
		TwoWireSoft::waitAck();
		TwoWireSoft::sendByte(WriteAddr>>8);//���͸ߵ�ַ	  
	}else TwoWireSoft::sendByte((pdata->adr)+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 	 
	TwoWireSoft::waitAck();	   
    TwoWireSoft::sendByte(WriteAddr%256);   //���͵͵�ַ
	TwoWireSoft::waitAck(); 	 										  		   
	TwoWireSoft::sendByte(DataToWrite);     //�����ֽ�							   
	TwoWireSoft::waitAck();  		    	   
    TwoWireSoft::stop();//����һ��ֹͣ���� 
	delay(10);	 
}
//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void EXTEEPROM::writeLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)
{  	
	uint8_t t;
	for(t=0;t<Len;t++)
	{
		this->writeOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
uint32_t EXTEEPROM::readLenByte(uint16_t ReadAddr,uint8_t Len)
{  	
	uint8_t t;
	uint32_t temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=this->readOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}

//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
uint8_t EXTEEPROM::check(void)
{
	uint8_t temp;
	temp=this->readOneByte((pdata->dev));//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		this->writeOneByte((pdata->dev),0X55);
	    temp=this->readOneByte((pdata->dev));	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void EXTEEPROM::read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=this->readOneByte(ReadAddr++);	
		NumToRead--;
	}
} 
 
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void EXTEEPROM::write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
	while(NumToWrite--)
	{
		this->writeOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}








