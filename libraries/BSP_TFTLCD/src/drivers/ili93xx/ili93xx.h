#ifndef __ILI93XX_H
#define __ILI93XX_H		
#if __has_include("bsp.h")
#  include "bsp.h"
#endif
#include "stdlib.h"
//////////////////////////////////////////////////////////////////////////////////	 

//2.4��/2.8��/3.5��/4.3�� TFTҺ������	  
//֧������IC�ͺŰ���:ILI9341/ILI9325/RM68042/RM68021/ILI9320/ILI9328/LGDP4531/LGDP4535/
//                  SPFD5408/SSD1289/1505/B505/C505/NT35310/NT35510��		    

//********************************************************************************
//V1.2�޸�˵��
//֧����SPFD5408������,�����Һ��IDֱ�Ӵ�ӡ��HEX��ʽ.����鿴LCD����IC.
//V1.3
//�����˿���IO��֧��
//�޸��˱�����Ƶļ��ԣ�������V1.8���Ժ�Ŀ�����汾��
//����1.8�汾֮ǰ(������1.8)��Һ��ģ��,���޸�LCD_Init������LCD_LED=1;ΪLCD_LED=1;
//V1.4
//�޸���LCD_ShowChar������ʹ�û��㹦�ܻ��ַ���
//�����˺�������ʾ��֧��
//V1.5 20110730
//1,�޸���B505Һ������ɫ�����bug.
//2,�޸��˿���IO�������������÷�ʽ.
//V1.6 20111116
//1,�����LGDP4535Һ��������֧��
//V1.7 20120713
//1,����LCD_RD_DATA����
//2,���Ӷ�ILI9341��֧��
//3,����ILI9325�Ķ�����������
//4,����LCD_Scan_Dir����(����ʹ��)	  
//6,�����޸��˲���ԭ���ĺ���,����Ӧ9341�Ĳ���
//V1.8 20120905
//1,����LCD��Ҫ�������ýṹ��lcddev
//2,����LCD_Display_Dir����,֧�����ߺ������л�
//V1.9 20120911
//1,����RM68042������ID:6804��������6804��֧�ֺ�����ʾ����ԭ�򣺸ı�ɨ�跽ʽ��
//����6804��������ʧЧ���Թ��ܶ෽�������У���ʱ�޽⡣
//V2.0 20120924
//�ڲ�Ӳ����λ�������,ILI9341��ID��ȡ�ᱻ�����9300,�޸�LCD_Init,���޷�ʶ��
//�����������IDΪ9300/�Ƿ�ID��,ǿ��ָ������ICΪILI9341��ִ��9341�ĳ�ʼ����
//V2.1 20120930
//����ILI9325����ɫ��bug��
//V2.2 20121007
//����LCD_Scan_Dir��bug��
//V2.3 20130120
//����6804֧�ֺ�����ʾ
//V2.4 20131120
//1,����NT35310��ID:5310����������֧��
//2,����LCD_SetDisplayWindow����,�������ô���,�Կ������,�Ƚ�����,���Ǹú����ں���ʱ,��֧��6804.
//V2.5 20140211
//1,����NT35510��ID:5510����������֧��
//////////////////////////////////////////////////////////////////////////////////	

 
  

//������Լ���LCD�ߴ�,�����޸�!!!!!!!!!!!!!
//����LCD�ߴ��С
//1��2.8��
//2��3.5��
//3��4.3��(������) 
#define   LCD_SIZE_TYPE    1  //uCGUI��,Ĭ������Ϊ2.8����


//////////////////////////////////////////////////////////////////////////////////
	 
//ɨ�跽����
#define L2R_U2D  0 //������,���ϵ���
#define L2R_D2U  1 //������,���µ���
#define R2L_U2D  2 //���ҵ���,���ϵ���
#define R2L_D2U  3 //���ҵ���,���µ���

#define U2D_L2R  4 //���ϵ���,������
#define U2D_R2L  5 //���ϵ���,���ҵ���
#define D2U_L2R  6 //���µ���,������
#define D2U_R2L  7 //���µ���,���ҵ���	 

#define DFT_SCAN_DIR  L2R_U2D  //Ĭ�ϵ�ɨ�跽��


#ifdef __cplusplus
extern "C"{
#endif

void ILI93XX_Init(void);													   	//��ʼ��
void ILI93XX_DisplayOn(void);													//����ʾ
void ILI93XX_DisplayOff(void);													//����ʾ
void ILI93XX_Clear(uint16_t Color);	 												//����
void ILI93XX_SetCursor(uint16_t Xpos, uint16_t Ypos);										//���ù��
void ILI93XX_WritePixel(uint16_t x,uint16_t y,uint16_t color);											//����
void ILI93XX_Fast_WritePixel(uint16_t x,uint16_t y,uint16_t color);								//���ٻ���
uint16_t  ILI93XX_ReadPixel(uint16_t x,uint16_t y); 											//���� 
void ILI93XX_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);		   				//��䵥ɫ
void ILI93XX_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);				//���ָ����ɫ

void ILI93XX_Scan_Dir(uint8_t dir);							//������ɨ�跽��
void ILI93XX_Display_Dir(uint8_t dir);						//������Ļ��ʾ����
void ILI93XX_SetDisplayWindow(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);//���ô���

#ifdef __cplusplus
} //extern "C"{
#endif

				  		 
#endif  
	 
	 



