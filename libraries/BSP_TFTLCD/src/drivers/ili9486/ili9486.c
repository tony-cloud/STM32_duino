#include <Arduino.h>
#include "bspio/bspio.h"
#include "ili9486.h"
#include "font/font.h"
#include "tftlcd/lcd.h"
 
#define  ILI9486_WR_REG(x) 	LCD_IO_WriteReg(x)
#define  ILI9486_WR_DATA(x) LCD_IO_WriteData(x)
#define  ILI9486_RD_DATA    LCD_IO_ReadData
#define  ILI9486_WriteRegData(x,y) LCD_IO_WriteRegData(x,y)

//����LCD��Ҫ����
//Ĭ��Ϊ����

LCD_DrvTypeDef ILI9486_DRV = {
  .Init       = ILI9486_Init,
  .DisplayOn  = ILI9486_DisplayOn,
  .DisplayOff = ILI9486_DisplayOff,
  .SetCursor  = ILI9486_SetCursor,
  .ReadPixel  = ILI9486_ReadPixel,
  .WritePixel = ILI9486_WritePixel,
  .Fill	      = ILI9486_Fill,
  
//option  
  .DrawHLine = ILI9486_DrawHLine,
  .DrawVLine = ILI9486_DrawVLine,
};


extern LCD_DevTypeDef lcddev;

/********************************************************************************************************
*	�� �� ��: Delay
*	����˵��: ��ʱ
*	��    ��: nCount ��ʱ����
*	�� �� ֵ: ��
*********************************************************************************************************/
static void op_delay(uint32_t nCount)
{
  for(volatile uint32_t i=nCount ; i != 0; i--);
}

   
//��ʼдGRAM
void ILI9486_WriteRAM_Prepare(void)
{
 	ILI9486_WR_REG(0x002c);	  
}	 

//����
//x,y:����
//color:�˵����ɫ
void ILI9486_WritePixel(uint16_t x,uint16_t y,uint16_t color)
{
	ILI9486_SetCursor(x,y);//���ù��λ�� 
    ILI9486_WR_REG(0x002c);
	ILI9486_WR_DATA(color); 
} 

//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
uint16_t ILI9486_ReadPixel(uint16_t x,uint16_t y)
{
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	ILI9486_SetCursor(x,y);	    
	ILI9486_WR_REG(0X002E);     //���Ͷ�GRAMָ�� ILI_CMD_W_FROM_MEM
    op_delay(10);
	ILI9486_RD_DATA();        //dumm
    op_delay(10);
    return ILI9486_RD_DATA();						
}			 

//���ù��λ��
//Xpos:������
//Ypos:������
void ILI9486_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	ILI9486_Set_Window(Xpos,Ypos,1,1);	
/*	ILI9486_WR_REG(0X2A); 
	ILI9486_WR_DATA(Xpos>>8); 
	ILI9486_WR_DATA(Xpos&0XFF);	 
	ILI9486_WR_REG(0X2B); 
	ILI9486_WR_DATA(Ypos>>8); 
	ILI9486_WR_DATA(Ypos&0XFF);	
*/	
} 

//��ʼ��lcd

void ILI9486_Init(void)
{ 	
	LCD_IO_Init();		 
	op_delay(0xAFFF<<2);
	lcddev.id =0x9486;

	ILI9486_WR_REG(0xB0);
	ILI9486_WR_DATA(0x00);
	ILI9486_WR_REG(0x11);
	op_delay(2000);

	ILI9486_WR_REG(0xB3);
	ILI9486_WR_DATA(0x02);
	ILI9486_WR_DATA(0x00);
	ILI9486_WR_DATA(0x00);
	ILI9486_WR_DATA(0x00);

	ILI9486_WR_REG(0xC0);
	ILI9486_WR_DATA(0x10);//13
	ILI9486_WR_DATA(0x3B);//480
	ILI9486_WR_DATA(0x00);
	ILI9486_WR_DATA(0x02);
	ILI9486_WR_DATA(0x00);
	ILI9486_WR_DATA(0x01);
	ILI9486_WR_DATA(0x00);//NW
	ILI9486_WR_DATA(0x43);

	ILI9486_WR_REG(0xC1);
	ILI9486_WR_DATA(0x10);//ILI9486_WR_DATA(0x08);
	ILI9486_WR_DATA(0x10);//ILI9486_WR_DATA(0x16);//CLOCK
	ILI9486_WR_DATA(0x08);
	ILI9486_WR_DATA(0x08);

	ILI9486_WR_REG(0xC4);
	ILI9486_WR_DATA(0x11);
	ILI9486_WR_DATA(0x07);
	ILI9486_WR_DATA(0x03);
	ILI9486_WR_DATA(0x03);

	ILI9486_WR_REG(0xC6);
	ILI9486_WR_DATA(0x00);

	ILI9486_WR_REG(0xC8);//GAMMA
	ILI9486_WR_DATA(0x03);
	ILI9486_WR_DATA(0x03);
	ILI9486_WR_DATA(0x13);
	ILI9486_WR_DATA(0x5C);
	ILI9486_WR_DATA(0x03);
	ILI9486_WR_DATA(0x07);
	ILI9486_WR_DATA(0x14);
	ILI9486_WR_DATA(0x08);
	ILI9486_WR_DATA(0x00);
	ILI9486_WR_DATA(0x21);
	ILI9486_WR_DATA(0x08);
	ILI9486_WR_DATA(0x14);
	ILI9486_WR_DATA(0x07);
	ILI9486_WR_DATA(0x53);
	ILI9486_WR_DATA(0x0C);
	ILI9486_WR_DATA(0x13);
	ILI9486_WR_DATA(0x03);
	ILI9486_WR_DATA(0x03);
	ILI9486_WR_DATA(0x21);
	ILI9486_WR_DATA(0x00);

	ILI9486_WR_REG(0x35);
	ILI9486_WR_DATA(0x00);

	ILI9486_WR_REG(0x36);  
	ILI9486_WR_DATA(0x08);
	ILI9486_WR_REG(0x3A);
	ILI9486_WR_DATA(0x55);

	ILI9486_WR_REG(0x44);
	ILI9486_WR_DATA(0x00);
	ILI9486_WR_DATA(0x01);

	ILI9486_WR_REG(0xB6);
	ILI9486_WR_DATA(0x00);
	ILI9486_WR_DATA(0x22);//0 GS SS SM ISC[3:0];����GS SS������ʾ����ͬʱ�޸�R36
	ILI9486_WR_DATA(0x3B);

	ILI9486_WR_REG(0xD0);
	ILI9486_WR_DATA(0x07);
	ILI9486_WR_DATA(0x07);//VCI1
	ILI9486_WR_DATA(0x1D);//VRH

	ILI9486_WR_REG(0xD1);
	ILI9486_WR_DATA(0x00);
	ILI9486_WR_DATA(0x03);//VCM
	ILI9486_WR_DATA(0x00);//VDV
	ILI9486_WR_REG(0xD2);
	ILI9486_WR_DATA(0x03);
	ILI9486_WR_DATA(0x14);
	ILI9486_WR_DATA(0x04);

	ILI9486_WR_REG(0x29);
	op_delay(2000);

	ILI9486_WR_REG(0xB4);
	ILI9486_WR_DATA(0x00);
	op_delay(2000);
	ILI9486_WR_REG(0x2C);
		
	ILI9486_Display_Dir(1);		 	//Ĭ��Ϊ����
}  

//��������
//color:Ҫ���������ɫ
void ILI9486_Clear(uint16_t color)
{
	ILI9486_Fill(0,0,lcddev.width-1,lcddev.height-1,color);
}  

//LCD������ʾ
void ILI9486_DisplayOn(void)
{					   
	ILI9486_WR_REG(0X29);  //ILI_CMD_DISP_ON
}	 

//LCD�ر���ʾ
void ILI9486_DisplayOff(void)
{	   
	ILI9486_WR_REG(0X28);	//ILI_CMD_DISP_OFF
} 

//����LCD��ʾ����
//dir:0,������1,����
void ILI9486_Display_Dir(uint8_t dir)
{
	lcddev.wramcmd=0X2C;  //ILI_CMD_W_TO_MEM
	lcddev.setxcmd=0X2A;  //ILI_CMD_COL_ADDR_SET
	lcddev.setycmd=0X2B;  //ILI_CMD_PAGE_ADDR_SET	 	
	if(dir==0)			//����
	{
		lcddev.width=320;
		lcddev.height=480;
		ILI9486_WriteRegData(0x36,0X0A); //BGR=1,MY=0,MX=0,MV=0
	}
	else 				
	{	  				
		lcddev.dir=1;	//����
		lcddev.width=480;
		lcddev.height=320; 	
		ILI9486_WriteRegData(0x36,0x28); //BGR=1,MY=1,MX=0,MV=1	
	}
}

//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height.
void ILI9486_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{   
	ILI9486_WR_REG(lcddev.setxcmd);	
	ILI9486_WR_DATA(sx>>8);
	ILI9486_WR_DATA(0x00FF&sx);		
	ILI9486_WR_DATA((width-0)>>8);
	ILI9486_WR_DATA(0x00FF&(width-0));

	ILI9486_WR_REG(lcddev.setycmd);	
	ILI9486_WR_DATA(sy>>8);
	ILI9486_WR_DATA(0x00FF&sy);		
	ILI9486_WR_DATA((height-0)>>8);
	ILI9486_WR_DATA(0x00FF&(height-0));

	ILI9486_WriteRAM_Prepare();	//��ʼд��GRAM
} 

//��ָ�����������ָ����ɫ
//�����С:(xend-xsta+1)*(yend-ysta+1)
//xsta
//color:Ҫ������ɫ
void ILI9486_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint16_t height,width;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
	ILI9486_Set_Window(sx,sy,ex,ey);	
 	for(volatile int i=0;i<height;i++)
	{
		for(volatile int j=0;j<width;j++) ILI9486_WR_DATA(color);//д������ 
	}	
	ILI9486_Set_Window(0,0,lcddev.width-1,lcddev.height-1);		
}  

void ILI9486_DrawHLine(uint16_t color, uint16_t sx, uint16_t sy, uint16_t Length){
	ILI9486_Fill(sx,sy,(sx+Length),sy,color);
}

void ILI9486_DrawVLine(uint16_t color, uint16_t sx, uint16_t sy, uint16_t Length){
	ILI9486_Fill(sx,sy,sx,(sy+Length),color);
}
