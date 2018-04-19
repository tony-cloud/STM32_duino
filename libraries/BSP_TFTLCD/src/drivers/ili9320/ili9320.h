#ifndef __ILI9320_H
#define __ILI9320_H		
#if __has_include("bsp.h")
#  include "bsp.h"
#endif
#include "stdlib.h"

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

void ILI9320_Init(void);													   	//��ʼ��
void ILI9320_DisplayOn(void);													//����ʾ
void ILI9320_DisplayOff(void);													//����ʾ
void ILI9320_Clear(uint16_t Color);	 												//����
void ILI9320_SetCursor(uint16_t Xpos, uint16_t Ypos);										//���ù��
void ILI9320_WritePixel(uint16_t x,uint16_t y,uint16_t color);											//����
void ILI9320_Fast_WritePixel(uint16_t x,uint16_t y,uint16_t color);								//���ٻ���
uint16_t  ILI9320_ReadPixel(uint16_t x,uint16_t y); 											//���� 
void ILI9320_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);		   				//��䵥ɫ
void ILI9320_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);				//���ָ����ɫ

void ILI9320_Scan_Dir(uint8_t dir);							//������ɨ�跽��
void ILI9320_Display_Dir(uint8_t dir);						//������Ļ��ʾ����
void ILI9320_SetDisplayWindow(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);//���ô���
void ILI9320_DrawHLine(uint16_t color, uint16_t sx, uint16_t sy, uint16_t Length);
void ILI9320_DrawVLine(uint16_t color, uint16_t sx, uint16_t sy, uint16_t Length);

#ifdef __cplusplus
} //extern "C"{
#endif

				  		 
#endif  
	 
	 



