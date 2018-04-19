#ifndef _TOUCH_H
#define _TOUCH_H
#include "ott2001a.h"

#define TP_PRES_DOWN	0X80  //����������
#define TP_CATH_PRES	0X40  //�а���������
typedef struct
{
	uint8_t (*init)(void);  //��ʼ��������
	uint8_t (*scan)(uint8_t);		 //ɨ�败����0,��Ļɨ��;1,��������
	void (*adjust)(void); //������У׼
#ifdef OTT_MAX_TOUCH
	uint16_t x[OTT_MAX_TOUCH];  //��ǰ����
	uint16_t y[OTT_MAX_TOUCH];  //�����������5������,��������Ϊx[0],y[0]����:�˴�ɨ��ʱ,��������������
#else
	uint16_t x[1];  //��ǰ����
	uint16_t y[1];  //
#endif

	//x[4],y[4]�洢��һ�ΰ���ʱ������
	uint8_t sta;  	//�ʵ�״̬
						//b7:����1/�ɿ�0; 
						//b6:0,û�а�������;1,�а�������. 
						//b5:����
						//b4~b0:���ݴ��������µĵ���(0,��ʾδ����,1��ʾ����)
/////////////////////������У׼����(����������ҪУ׼)//////////////////////			
	float xfac;
	float yfac;
	int16_t xoff;
	int16_t yoff;
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//b0:0,����(�ʺ�����ΪX����,����ΪY�����TP)
//   1,����(�ʺ�����ΪY����,����ΪX�����TP) 
//b1~6:����.
//b7:0,������
//   1,������ 
	uint8_t touchtype;
	uint8_t CMD_RDX;
	uint8_t CMD_RDY;
	uint8_t miso;
    uint8_t mosi;
	uint8_t sck;
	uint8_t cs;
	uint8_t irq;
}_m_tp_dev;

extern _m_tp_dev tp_dev; //������������touch.c���涨��

//������оƬ��������	   
//#define PEN  		PCin(5)  	//T_PEN
//#define DOUT 		PBin(14)   	//T_MISO
//#define TDIN 		PBout(15)  	//T_MOSI
//#define TCLK 		PBout(13)  	//T_SCK
//#define TCS  		PBout(12)  	//T_CS  

#ifdef __cplusplus
 extern "C" {
#endif /* __cplusplus */

//������/������ ���ú���
uint8_t TP_Scan(uint8_t tp);								//ɨ��
uint8_t TP_Init(void);								//��ʼ��

//����������
void TP_Write_Byte(uint8_t num);						//�����оƬд��һ������
uint16_t TP_Read_AD(uint8_t CMD);							//��ȡADת��ֵ
uint16_t TP_Read_XOY(uint8_t xy);							//���˲��������ȡ(X/Y)
uint8_t TP_Read_XY(uint16_t *x,uint16_t *y);					//˫�����ȡ(X+Y)
uint8_t TP_Read_XY2(uint16_t *x,uint16_t *y);					//����ǿ�˲���˫���������ȡ
void TP_Drow_Touch_Point(uint16_t x,uint16_t y,uint16_t color);//��һ������У׼��
void TP_Draw_Big_Point(uint16_t x,uint16_t y,uint16_t color);	//��һ�����
void TP_Save_Adjdata(void);						//����У׼����
uint8_t TP_Get_Adjdata(void);						//��ȡУ׼����
void TP_Adjust(void);							//������У׼
void TP_Adj_Info_Show(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t fac);//��ʾУ׼��Ϣ

#ifdef __cplusplus
}  // extern "C" {

class TOUCH
{
 public:
	TOUCH(){
		pdev = &tp_dev;
	};
	TOUCH(uint8_t mosi, uint8_t miso, uint8_t sck,uint8_t cs, uint8_t irq){
		pdev->mosi = mosi;
		pdev->miso = miso;
		pdev->sck = sck;
		pdev->cs = cs;
		pdev->irq = irq;
	};		
	uint8_t Init(uint8_t typ = 0){
		pdev->touchtype |= typ&0x01;
		return TP_Init();};
    void     writeByte(uint8_t num){TP_Write_Byte(num);};						//�����оƬд��һ������
    uint16_t readAD(uint8_t CMD){return TP_Read_AD( CMD);};							//��ȡADת��ֵ
	uint16_t readXOY(uint8_t xy){return TP_Read_XOY(xy);};							//���˲��������ȡ(X/Y)
	uint8_t  readXY(uint16_t *x,uint16_t *y){return TP_Read_XY(x,y);};					//˫�����ȡ(X+Y)
	uint8_t  readXY2(uint16_t *x,uint16_t *y){return TP_Read_XY2(x,y);};					//����ǿ�˲���˫���������ȡ
//	void TP_Drow_Touch_Point(uint16_t x,uint16_t y,uint16_t color);//��һ������У׼��
//	void TP_Draw_Big_Point(uint16_t x,uint16_t y,uint16_t color);	//��һ�����
//	void TP_Save_Adjdata(void);						//����У׼����
//	uint8_t TP_Get_Adjdata(void);					//��ȡУ׼����
	void     adjust(void){TP_Adjust();};			//������У׼
//	void TP_Adj_Info_Show(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t fac);//��ʾУ׼��Ϣ
	//������/������ ���ú���
	uint8_t  scan(uint8_t tp=0){return TP_Scan(tp);};				//ɨ��
	uint8_t  status(void){return (pdev->sta >>6);};				//ɨ��
	_m_tp_dev* Info(void){
		return pdev;
	}
	_m_tp_dev* pdev; 
};
#endif /* __cplusplus */ 
#endif

