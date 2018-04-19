#ifndef __DS18B20_H
#define __DS18B20_H 

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */ 

void DS18B20_SetPin(uint8_t pin);
uint8_t DS18B20_Init(void);			//��ʼ��DS18B20
int DS18B20_GetTemp(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_WriteByte(uint8_t dat);//д��һ���ֽ�
uint8_t DS18B20_ReadByte(void);		//����һ���ֽ�
uint8_t DS18B20_ReadBit(void);		//����һ��λ
uint8_t DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20    


#ifdef __cplusplus
 } // extern "C"
//C++ function here 
class DS18B20Class
{
   public:	
        DS18B20Class(){};
		void setPin(uint8_t pin){DS18B20_SetPin(pin);};
		uint8_t Init(void){return DS18B20_Init();}; 
		int getTemp(void){return DS18B20_GetTemp();};	//��ȡ�¶�
		void  start(void){DS18B20_Start();};		//��ʼ�¶�ת��
		void  writeByte(uint8_t dat){DS18B20_WriteByte(dat);};//д��һ���ֽ�
		uint8_t  readByte(void){return DS18B20_ReadByte();};		//����һ���ֽ�
		uint8_t  readBit(void){return DS18B20_ReadBit();};		//����һ��λ
		uint8_t  check(void){return DS18B20_Check();};			//����Ƿ����DS18B20
		void  rst(void){DS18B20_Rst();};			//��λDS18B20    
	private:
}; 
#endif /* __cplusplus */

#endif