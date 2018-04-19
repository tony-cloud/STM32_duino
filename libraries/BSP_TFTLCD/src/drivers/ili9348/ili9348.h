#ifndef __ILI9348_H
#define __ILI9348_H		
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

void ILI9348_Init(void);													   	//��ʼ��
void ILI9348_DisplayOn(void);													//����ʾ
void ILI9348_DisplayOff(void);													//����ʾ
void ILI9348_Clear(uint16_t Color);	 												//����
void ILI9348_SetCursor(uint16_t Xpos, uint16_t Ypos);										//���ù��
void ILI9348_WritePixel(uint16_t x,uint16_t y,uint16_t color);											//����
void ILI9348_Fast_WritePixel(uint16_t x,uint16_t y,uint16_t color);								//���ٻ���
uint16_t  ILI9348_ReadPixel(uint16_t x,uint16_t y); 											//���� 
void ILI9348_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);		   				//��䵥ɫ
void ILI9348_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);				//���ָ����ɫ

void ILI9348_Scan_Dir(uint8_t dir);							//������ɨ�跽��
void ILI9348_Display_Dir(uint8_t dir);						//������Ļ��ʾ����
void ILI9348_SetDisplayWindow(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height);//���ô���

#ifdef __cplusplus
} //extern "C"{
#endif

				  		 
#endif  
	 
	 



