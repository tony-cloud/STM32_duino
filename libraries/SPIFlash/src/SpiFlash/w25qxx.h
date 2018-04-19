#ifndef __W25QXX_H__
#define __W25QXX_H__

#include <SPI.h>


//W25Xϵ��/Qϵ��оƬ�б�
#define W25Q40 	0XEF12  /*WINBOND*/
#define W25Q80 	0XEF13 	/*WINBOND*/
#define W25Q16 	0XEF14	/*WINBOND*/
#define W25Q32 	0XEF15	/*WINBOND*/
#define W25Q64 	0XEF16	/*WINBOND*/
#define W25Q128	0XEF17	/*WINBOND*/

#define M25P64	0x2016  /*MICRON*/
#define M25P128	0x2017  /*MICRON*/

#define SST25VF032  0xBF4A /*SST*/

#define GD25Q40    0xC812	  /*GIGA*/   

#define AT45DB161  0x1F2600 /*AT*/

#define MX25L16  0xC214   /*MACRONIX*/
#define MX25L32  0xC215   /*MACRONIX*/
#define MX25L64  0xC216   /*MACRONIX*/
#define MX25L128 0xC217   /*MACRONIX*/

#ifdef __cplusplus

#define  W25QXX_BUFFERSIZE 4096

typedef struct {
    uint8_t cs_pin;
	uint8_t	aBuf[W25QXX_BUFFERSIZE];	
    uint8_t	ID[5];  //����W25QXXоƬID
	uint8_t inited = 0;
} W25QXX_TypeDef;


class SPIFLASH : public SPIClass 
{
  public:
	SPIFLASH();
    SPIFLASH(uint8_t mosi, uint8_t miso, uint8_t sck);
	SPIFLASH(SPI_TypeDef *instance);
    void begin(uint8_t cs = 0xff);
	uint16_t readID(void);  	    	//��ȡFLASH ID
    uint32_t capacity(void);
	uint8_t	 readSR(void);        		//��ȡ״̬�Ĵ��� 
    void writeSR(uint8_t sr);  			//д״̬�Ĵ���
    void writeEnable(void);  			//дʹ�� 
    void writeDisable(void);			//д����
    void read 		 (uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   //��ȡflash
    void write		 (uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//д��flash
    void writeNoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
    void eraseChip(void);    	  	//��Ƭ����
    void eraseSector(uint32_t Dst_Addr);	//��������
    void waitBusy(void);           	//�ȴ�����
    void powerDown(void);        	//�������ģʽ
    void WAKEUP(void);				//����
	W25QXX_TypeDef *pdata =&sdata;
  private:   
	void jedecDeviceID(uint8_t *buf);
	void writePage(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
	W25QXX_TypeDef sdata;
};

#endif  //__cplusplus
#endif  //__W25QXX_H















