#include <Arduino.h>
#include "bspio/bspio.h"
#include "ili9481.h"
//#include "ili9481_reg.h"
//#include "stdlib.h"
#include "font/font.h"
#include "tftlcd/lcd.h"
 
#define  ILI9481_WR_REG(x) 	LCD_IO_WriteReg(x)
#define  ILI9481_WR_DATA(x) LCD_IO_WriteData(x)
#define  ILI9481_RD_DATA    LCD_IO_ReadData
#define  ILI9481_WriteRegData(x,y) LCD_IO_WriteRegData(x,y)

//����LCD��Ҫ����
//Ĭ��Ϊ����

LCD_DrvTypeDef ILI9481_DRV = {
  .Init       = ILI9481_Init,
  .ReadPixel  = ILI9481_ReadPixel,
  .WritePixel = ILI9481_WritePixel,
  .Fill	= ILI9481_Fill,
  
//option  
  .DisplayOn  = ILI9481_DisplayOn,
  .DisplayOff = ILI9481_DisplayOff,
  .SetCursor  = ILI9481_SetCursor,
};

extern LCD_DevTypeDef lcddev;

//���Ĵ���
//LCD_Reg:�Ĵ������
//����ֵ:������ֵ
uint16_t ILI9481_ReadReg(uint16_t LCD_Reg)
{										   
 	ILI9481_WR_REG(LCD_Reg);  //д��Ҫ���ļĴ�����  
	return ILI9481_RD_DATA(); 
} 

//��ʼдGRAM
void ILI9481_WriteRAM_Prepare(void)
{
	ILI9481_WR_REG(lcddev.wramcmd);
} 

//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
uint16_t ILI9481_BGR2RGB(uint16_t c)
{
	uint16_t  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
}		 
//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
uint16_t ILI9481_ReadPixel(uint16_t x,uint16_t y)
{
 	uint16_t r;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	ILI9481_SetCursor(x,y);
	ILI9481_WR_REG(0x2E);      		 		//����IC���Ͷ�GRAMָ��
 	//dummy READ
	delayMicroseconds(1);//��ʱ1us					   
 	r=DATAIN;  	//ʵ��������ɫ
	delayMicroseconds(1);//��ʱ1us					   
 	r=DATAIN;  	//ʵ��������ɫ
	return (r);
}
//LCD������ʾ
void ILI9481_DisplayOn(void)
{	
 ILI9481_WriteRegData(R7,0x0173); 			//������ʾ
}	 
//LCD�ر���ʾ
void ILI9481_DisplayOff(void)
{	   
 ILI9481_WriteRegData(R7, 0x0);//�ر���ʾ 
}   
//���ù��λ��
//Xpos:������
//Ypos:������
void ILI9481_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
 	ILI9481_Set_Window(Xpos,Ypos,Xpos,Ypos);
}

//����
//x,y:����
//lcddev.TextColor:�˵����ɫ
void ILI9481_WritePixel(uint16_t x,uint16_t y,uint16_t color)
{
	ILI9481_SetCursor(x,y);		//���ù��λ�� 
	ILI9481_WR_DATA(color); 
}  	 
//���ٻ���
//x,y:����
//color:��ɫ
void ILI9481_Fast_WritePixel(uint16_t x,uint16_t y,uint16_t color)
{	   
	ILI9481_SetCursor(x,y);		//���ù��λ�� 
	ILI9481_WR_DATA(color);		//д����
}
//����LCD��ʾ����
//dir:0,������1,����
void ILI9481_Display_Dir(uint8_t dir)
{
	if(dir==0)			//����
	{
	
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;  	 	
			lcddev.width=320;
			lcddev.height=480;
			ILI9481_WriteRegData(0x36,0X0A);//BGR==1,MY==0,MX==0,MV==0
	}
		else 				//����
	{	  				
			lcddev.dir=1;	//����
			lcddev.wramcmd=0X2C;
	 		lcddev.setxcmd=0X2A;
			lcddev.setycmd=0X2B;  	 		 
			lcddev.width=480;
			lcddev.height=320; 	
			ILI9481_WriteRegData(0x36,0x28);//BGR==1,MY==1,MX==0,MV==1  63		
		}
	

}	 
//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height.
//68042,����ʱ��֧�ִ�������!! 
void ILI9481_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{   
	ILI9481_WR_REG(lcddev.setxcmd);	
	ILI9481_WR_DATA(sx>>8);
	ILI9481_WR_DATA(0x00FF&sx);		
	ILI9481_WR_DATA((width-0)>>8);
	ILI9481_WR_DATA(0x00FF&(width-0));

	ILI9481_WR_REG(lcddev.setycmd);	
	ILI9481_WR_DATA(sy>>8);
	ILI9481_WR_DATA(0x00FF&sy);		
	ILI9481_WR_DATA((height-0)>>8);
	ILI9481_WR_DATA(0x00FF&(height-0));

	ILI9481_WriteRAM_Prepare();	//��ʼд��GRAM
} 

//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ALIENTEK��Ʒ��LCDҺ����
//������ռ�ýϴ�flash,�û����Ը����Լ���ʵ�����,ɾ��δ�õ���LCD��ʼ������.�Խ�ʡ�ռ�.
void ILI9481_Init(void)
{ 
	LCD_IO_Init();		 
	
	
	//Һ������ʼ��
	ILI9481_WR_REG(0x11);
	delay(20);
	ILI9481_WR_REG(0xD0);
	ILI9481_WR_DATA(0x07);
	ILI9481_WR_DATA(0x42);
	ILI9481_WR_DATA(0x18);
	
	ILI9481_WR_REG(0xD1);
	ILI9481_WR_DATA(0x00);
	ILI9481_WR_DATA(0x07);//07
	ILI9481_WR_DATA(0x10);
	
	ILI9481_WR_REG(0xD2);
	ILI9481_WR_DATA(0x01);
	ILI9481_WR_DATA(0x02);
	
	ILI9481_WR_REG(0xC0);
	ILI9481_WR_DATA(0x10);
	ILI9481_WR_DATA(0x3B);
	ILI9481_WR_DATA(0x00);
	ILI9481_WR_DATA(0x02);
	ILI9481_WR_DATA(0x11);
	
	ILI9481_WR_REG(0xC5);
	ILI9481_WR_DATA(0x03);
	
	ILI9481_WR_REG(0xC8);
	ILI9481_WR_DATA(0x00);
	ILI9481_WR_DATA(0x32);
	ILI9481_WR_DATA(0x36);
	ILI9481_WR_DATA(0x45);
	ILI9481_WR_DATA(0x06);
	ILI9481_WR_DATA(0x16);
	ILI9481_WR_DATA(0x37);
	ILI9481_WR_DATA(0x75);
	ILI9481_WR_DATA(0x77);
	ILI9481_WR_DATA(0x54);
	ILI9481_WR_DATA(0x0C);
	ILI9481_WR_DATA(0x00);
	
	ILI9481_WR_REG(0x36);
	ILI9481_WR_DATA(0x0A);
	
	ILI9481_WR_REG(0x3A);
	ILI9481_WR_DATA(0x55);
	
	ILI9481_WR_REG(0x2A);
	ILI9481_WR_DATA(0x00);
	ILI9481_WR_DATA(0x00);
	ILI9481_WR_DATA(0x01);
	ILI9481_WR_DATA(0x3F);
	
	ILI9481_WR_REG(0x2B);
	ILI9481_WR_DATA(0x00);
	ILI9481_WR_DATA(0x00);
	ILI9481_WR_DATA(0x01);
	ILI9481_WR_DATA(0xE0);
	delay(120);
	ILI9481_WR_REG(0x29);
	ILI9481_WR_REG(0x002c); 

	
	ILI9481_Display_Dir(1);		 	//Ĭ��Ϊ����
//	LCD_Clear(WHITE);
}  		  
  
//��������
//color:Ҫ���������ɫ
void ILI9481_Clear(uint16_t color)
{
	uint32_t index=0;      
	uint32_t totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 			//�õ��ܵ���
	ILI9481_Set_Window(0,0,lcddev.width-1,lcddev.height-1);				
	for(index=0;index<totalpoint;index++)ILI9481_WR_DATA(color);	
}  
//��ָ�����������ָ����ɫ
//�����С:(xend-xsta+1)*(yend-ysta+1)
//xsta
//color:Ҫ������ɫ
void ILI9481_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint16_t height,width;
	uint16_t i,j;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
	ILI9481_Set_Window(sx,sy,ex,ey);	
 	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)ILI9481_WR_DATA(color);//д������ 
	}	
	ILI9481_Set_Window(0,0,lcddev.width-1,lcddev.height-1);		
}  
//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void ILI9481_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{  
	uint16_t height,width;
	uint16_t i,j;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
	ILI9481_Set_Window(sx,sy,ex,ey);		
 	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)ILI9481_WR_DATA(color[i*width+j]);//д������ 
	}	 
	ILI9481_Set_Window(0,0,lcddev.width-1,lcddev.height-1);			
} 
