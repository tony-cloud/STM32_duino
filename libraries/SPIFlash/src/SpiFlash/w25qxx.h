#ifndef __W25QXX_H__
#define __W25QXX_H__

#include <Arduino.h>

//user board &spiflashconfig file
#if __has_include("bsp.h")
#  include "bsp.h"
#endif

#if __has_include("configs/spiFlashConfig.h")
#  include "configs/spiFlashConfig.h"
#endif

#include <SPI.h>
#include <SoftSPI.h>

//user unconfig spiflash use variant.h define
#ifndef  SPIFLASH_MOSI
# define SPIFLASH_MOSI	MOSI
#endif
#ifndef	SPIFLASH_MISO
#define SPIFLASH_MISO	MISO
#endif
#ifndef	SPIFLASH_SCK
#define SPIFLASH_SCK	SCK
#endif
#ifndef	SPIFLASH_CS
#define SPIFLASH_CS		SS
#endif

#ifndef SPIFLASH_SPEED_Mhz
#define SPIFLASH_SPEED_Mhz 20
#endif

////////////////////////////////////////////////////////////////////////////////// 
//command list ָ���
#define W25X_WriteStatusReg		0x01 
#define W25X_PageProgram		0x02 
#define W25X_ReadData			0x03 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteEnable		0x06 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9
#define W25X_DummyByte          0xA5 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F
 
#define CHIP_Unlock             0x98    /*mx25x128 unlock*/ 
//IDO
#define ID0_SPANSION	0x01
#define ID0_MICRON		0x20
#define ID0_MACRONIX	0xC2
#define IDO_GIGA	 	0xC8
#define ID0_SST			0xBF
#define ID0_WINBOND		0xEF

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


template<const int mosiPin, const int misoPin, const int sckPin, const int csPin>
class SOFT_SPIFLASH
{
  public:
    SOFT_SPIFLASH() {};

    void begin() {
      cs.config(OUTPUT, HIGH);
      spi.begin();
	  this->jedecDeviceID(&ID[0]);
    }

    uint32_t readID(void) {         //��ȡFLASH ID
      uint32_t tmp = 0;
      cs = 0;
      spi.transfer(W25X_ManufactDeviceID); //���Ͷ�ȡID����
      spi.transfer(W25X_DummyByte); //���Ͷ�ȡID����
      spi.transfer(W25X_DummyByte); //���Ͷ�ȡID����
      spi.transfer(0x00); //���Ͷ�ȡID����

      tmp |= spi.transfer(0x00) << 8;
      tmp |= spi.transfer(0x00);
      cs = 1;
      return tmp;
    }
	
    void jedecDeviceID(uint8_t *buf){
      cs = 0;
	  spi.transfer(W25X_JedecDeviceID);//���Ͷ�ȡJedecDeviceID 0x9F����	    
	  buf[0] = spi.transfer(0x00); 	    
	  buf[1] = spi.transfer(0x00);
	  buf[2] = spi.transfer(0x00);
	  if (buf[0] == ID0_SPANSION) {
//	  	buf[3] = spi.transfer(W25X_DummyByte); // ID-CFI
//	  	buf[4] = spi.transfer(0x00); // sector size
	  	buf[3] = spi.transfer(0x00); // ID-CFI
	  	buf[4] = spi.transfer(0x00); // sector size
	  }	
      cs = 1;
    }   		    

    uint32_t capacity(void){
		uint32_t n = 1048576; // unknown chips, default to 1 MByte
		if (ID[2] >= 0x10 && ID[2] <= 0x1F) {
			n = 1ul << ID[2];
		} else if (ID[2] >= 0x20 && ID[2] <= 0x25) {
			n = 1ul << (ID[2] - 6);
		} else	if ((ID[0]==0 && ID[1]==0 && ID[2]==0) || 
			(ID[0]==255 && ID[1]==255 && ID[2]==255)) {
			n = 0;
		}
		return n;
	}

    uint8_t  readSR(void) {           //��ȡ״̬�Ĵ���
      uint8_t byte = 0;
      cs = 0;                         //ʹ������
      spi.transfer(W25X_ReadStatusReg);    //���Ͷ�ȡ״̬�Ĵ�������
      byte = spi.receive();          //��ȡһ���ֽ�
      cs = 1;                         //ȡ��Ƭѡ
      return byte;
    }

    void writeSR(uint8_t sr) {      //д״̬�Ĵ���
      cs = 0;                         //ʹ������
      spi.transfer(W25X_WriteStatusReg);   //����дȡ״̬�Ĵ�������
      spi.transfer(sr);                    //д��һ���ֽ�
      cs = 1;                         //ȡ��Ƭѡ
    }

    void writeEnable(void) {      //дʹ��
      cs = 0;
      spi.transfer(W25X_WriteEnable);        //����дʹ��
      cs = 1;        //ȡ��Ƭѡ
    }

    void writeDisable(void) {     //д����
      cs = 0;
      spi.transfer(W25X_WriteDisable);        //����дʹ��
      cs = 1;        //ȡ��Ƭѡ
    }

    void read(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead) { //��ȡflash
      cs = 0;        //ʹ������
      spi.transfer(W25X_ReadData);         //���Ͷ�ȡ����
      spi.transfer((uint8_t)((ReadAddr) >> 16)); //����24bit��ַ
      spi.transfer((uint8_t)((ReadAddr) >> 8));
      spi.transfer((uint8_t)ReadAddr);
      for (uint16_t i = 0; i < NumByteToRead; i++)
      {
          pBuffer[i] = spi.transfer(0); //ѭ������
      }
      cs = 1;

    }
	
    void write (uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite) { //д��flash
      uint32_t secpos;
      uint16_t secoff;
      uint16_t secremain;
      uint16_t i;
      uint8_t * W25QXX_BUF;
      W25QXX_BUF = &aBuf[0];
      secpos = WriteAddr / 4096; //������ַ
      secoff = WriteAddr % 4096; //�������ڵ�ƫ��
      secremain = 4096 - secoff; //����ʣ��ռ��С
      //printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//������
      if (NumByteToWrite <= secremain)secremain = NumByteToWrite; //������4096���ֽ�
      while (1)
      {
        this->read(W25QXX_BUF, secpos * 4096, 4096); //������������������
        for (i = 0; i < secremain; i++) //У������
        {
          if (W25QXX_BUF[secoff + i] != 0XFF)break; //��Ҫ����
        }

        if (i < secremain) //��Ҫ����
        {
          this->eraseSector(secpos);//�����������
          for (i = 0; i < secremain; i++) //����
          {
            W25QXX_BUF[i + secoff] = pBuffer[i];
          }
          this->writeNoCheck(W25QXX_BUF, secpos * 4096, 4096); //д����������
        } else
          this->writeNoCheck(pBuffer, WriteAddr, secremain); //д�Ѿ������˵�,ֱ��д������ʣ������.

        if (NumByteToWrite == secremain)break; //д�������
        else//д��δ����
        {
          secpos++;//������ַ��1
          secoff = 0; //ƫ��λ��Ϊ0

          pBuffer += secremain; //ָ��ƫ��
          WriteAddr += secremain; //д��ַƫ��
          NumByteToWrite -= secremain;      //�ֽ����ݼ�
          if (NumByteToWrite > 4096)secremain = 4096; //��һ����������д����
          else secremain = NumByteToWrite;    //��һ����������д����
        }
      };

    }
    void writePage(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
    {
      this->writeEnable();                  //SET WEL
      cs = 0;   //ʹ������
      spi.transfer(W25X_PageProgram);      //����дҳ����
      spi.transfer((uint8_t)((WriteAddr) >> 16)); //����24bit��ַ
      spi.transfer((uint8_t)((WriteAddr) >> 8));
      spi.transfer((uint8_t)WriteAddr);
      for (uint16_t i = 0; i < NumByteToWrite; i++) spi.transfer(pBuffer[i]); //ѭ��д��
      cs = 1 ;                           //ȡ��Ƭѡ
      this->waitBusy();            //�ȴ�д�����
    }

    void writeNoCheck(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite) {
      uint16_t pageremain;
      pageremain = 256 - WriteAddr % 256; //��ҳʣ����ֽ���
      if (NumByteToWrite <= pageremain)pageremain = NumByteToWrite; //������256���ֽ�
      while (1)
      {
        this->writePage(pBuffer, WriteAddr, pageremain);
        if (NumByteToWrite == pageremain)break; //д�������
        else //NumByteToWrite>pageremain
        {
          pBuffer += pageremain;
          WriteAddr += pageremain;

          NumByteToWrite -= pageremain;     //��ȥ�Ѿ�д���˵��ֽ���
          if (NumByteToWrite > 256)pageremain = 256; //һ�ο���д��256���ֽ�
          else pageremain = NumByteToWrite;   //����256���ֽ���
        }
      }
    }

    void eraseChip(void) {        //��Ƭ����
      this->writeEnable();                  //SET WEL
      this->waitBusy();
      cs = 0;                           //ʹ������
      spi.transfer(W25X_ChipErase);        //����Ƭ��������
      cs = 1;                         //ȡ��Ƭѡ
      this->waitBusy();              //�ȴ�оƬ��������

    }
    void eraseSector(uint32_t Dst_Addr) { //��������
      Dst_Addr *= 4096;
      this->writeEnable();                  //SET WEL
      this->waitBusy();
      cs = 0;           //ʹ������
      spi.transfer(W25X_SectorErase);      //������������ָ��
      spi.transfer((uint8_t)((Dst_Addr) >> 16)); //����24bit��ַ
      spi.transfer((uint8_t)((Dst_Addr) >> 8));
      spi.transfer((uint8_t)Dst_Addr);
      cs = 1;  //ȡ��Ƭѡ
      this->waitBusy();           //�ȴ��������

    }
    void waitBusy(void) {           //�ȴ�����
      while ((this->readSR() & 0x01) == 0x01); // �ȴ�BUSYλ���
    }
    void powerDown(void) {        //�������ģʽ
      cs = 0;
      spi.transfer(W25X_PowerDown);
      cs = 1;
      delay(3);
    }
    void WAKEUP(void) {
      cs = 0;
      spi.transfer(W25X_ReleasePowerDown);
      cs = 1;
      delay(3);

    }
  private:
    SoftSPI<mosiPin, misoPin, sckPin, 0>spi;
    DigitalPin<csPin>cs;
    uint8_t aBuf[W25QXX_BUFFERSIZE];
	uint8_t	ID[5];
};

#endif  //__cplusplus
#endif  //__W25QXX_H















