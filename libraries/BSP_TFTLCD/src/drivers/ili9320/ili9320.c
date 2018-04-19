#include <Arduino.h>
#include "bspio/bspio.h"
#include "ili9320.h"
#include "ili9320_reg.h"
//#include "stdlib.h"
#include "font/font.h"
#include "tftlcd/lcd.h"
 
#define  ILI9320_WR_REG(x) 	LCD_IO_WriteReg(x)
#define  ILI9320_WR_DATA(x) LCD_IO_WriteData(x)
#define  ILI9320_RD_DATA    LCD_IO_ReadData
#define  ILI9320_WriteRegData(x,y) LCD_IO_WriteRegData(x,y)



LCD_DrvTypeDef ILI9320_DRV = {
  .Init       = ILI9320_Init,
  .DisplayOn  = ILI9320_DisplayOn,
  .DisplayOff = ILI9320_DisplayOff,
  .SetCursor  = ILI9320_SetCursor,
  .ReadPixel  = ILI9320_ReadPixel,
  .WritePixel = ILI9320_WritePixel,
  .Fill	= ILI9320_Fill,

//option
  .DrawHLine = ILI9320_DrawHLine,
  .DrawVLine = ILI9320_DrawVLine,
};


extern LCD_DevTypeDef lcddev;

uint16_t ILI9320_ReadReg(uint16_t Reg)
{										   
	ILI9320_WR_REG(Reg);		//д��Ҫ���ļĴ������
	delayMicroseconds(5);		  
	return ILI9320_RD_DATA();		//���ض�����ֵ
}   
//��ʼдGRAM
void ILI9320_WriteRAM_Prepare(void)
{
 	ILI9320_WR_REG(lcddev.wramcmd);
}	 
//LCDдGRAM
//RGB_Code:��ɫֵ
void ILI9320_WriteRAM(uint16_t RGB_Code)
{							    
	ILI9320_WR_DATA(RGB_Code);//дʮ��λGRAM
}
//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ

uint16_t ILI9320_BGR2RGB(uint16_t c)
{
	uint16_t  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
} 
//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
static void opt_delay(uint8_t i)
{
	while(i--);
}
//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
uint16_t ILI9320_ReadPixel(uint16_t x,uint16_t y)
{
 	uint16_t r=0;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	ILI9320_SetCursor(x,y);	    
	ILI9320_WR_REG(R34);      		 				//����IC���Ͷ�GRAMָ��
 	opt_delay(2);				//FOR 9320,��ʱ2us	    
	r=ILI9320_RD_DATA();							//dummy Read	   
	opt_delay(2);	  
 	r=ILI9320_RD_DATA();  		  						//ʵ��������ɫ
    return ILI9320_BGR2RGB(r);						//����IC
}			 
//LCD������ʾ
void ILI9320_DisplayOn(void)
{					   
    ILI9320_WriteRegData(R7,0x0173); 				 	//������ʾ
}	 
//LCD�ر���ʾ
void ILI9320_DisplayOff(void)
{	   
	ILI9320_WriteRegData(R7,0x0);//�ر���ʾ 
}   
//���ù��λ��
//Xpos:������
//Ypos:������
void ILI9320_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	 
	if(lcddev.dir==1)Xpos=lcddev.width-1-Xpos;//������ʵ���ǵ�תx,y����
	ILI9320_WriteRegData(lcddev.setxcmd, Xpos);
	ILI9320_WriteRegData(lcddev.setycmd, Ypos);
} 		 
//����LCD���Զ�ɨ�跽��
//ע��:�����������ܻ��ܵ��˺������õ�Ӱ��(������9341/6804����������),
//����,һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.
//dir:0~7,����8������(���嶨���lcd.h)
//9320/9325/9328/4531/4535/1505/b505/8989/5408/9341/5310/5510��IC�Ѿ�ʵ�ʲ���	   	   
void ILI9320_Scan_Dir(uint8_t dir)
{
	uint16_t regval=0;
	uint16_t dirreg=0;
	if(lcddev.dir==1)  //����ʱ����6804���ı�ɨ�跽��
	{			   
		switch(dir)//����ת��
		{
			case 0:dir=6;break;
			case 1:dir=7;break;
			case 2:dir=4;break;
			case 3:dir=5;break;
			case 4:dir=1;break;
			case 5:dir=0;break;
			case 6:dir=3;break;
			case 7:dir=2;break;	     
		}
	}
	{
		switch(dir)
		{
			case L2R_U2D://������,���ϵ���
				regval|=(1<<5)|(1<<4)|(0<<3); 
				break;
			case L2R_D2U://������,���µ���
				regval|=(0<<5)|(1<<4)|(0<<3); 
				break;
			case R2L_U2D://���ҵ���,���ϵ���
				regval|=(1<<5)|(0<<4)|(0<<3);
				break;
			case R2L_D2U://���ҵ���,���µ���
				regval|=(0<<5)|(0<<4)|(0<<3); 
				break;	 
			case U2D_L2R://���ϵ���,������
				regval|=(1<<5)|(1<<4)|(1<<3); 
				break;
			case U2D_R2L://���ϵ���,���ҵ���
				regval|=(1<<5)|(0<<4)|(1<<3); 
				break;
			case D2U_L2R://���µ���,������
				regval|=(0<<5)|(1<<4)|(1<<3); 
				break;
			case D2U_R2L://���µ���,���ҵ���
				regval|=(0<<5)|(0<<4)|(1<<3); 
				break;	 
		}
		dirreg=0X03;
		regval|=1<<12;  
		ILI9320_WriteRegData(dirreg,regval);
	}
}   
//����
//x,y:����
//lcddev.TextColor:�˵����ɫ
void ILI9320_WritePixel(uint16_t x,uint16_t y,uint16_t color)
{
	ILI9320_SetCursor(x,y);		//���ù��λ�� 
	ILI9320_WriteRAM_Prepare();	//��ʼд��GRAM
	ILI9320_WR_DATA(color); 
}



//����LCD��ʾ����
//dir:0,������1,����
void ILI9320_Display_Dir(uint8_t dir)
{
	if(dir==0)			//����
	{
		lcddev.dir=0;	//����
		lcddev.width=240;
		lcddev.height=320;
		{
			lcddev.wramcmd=R34;
	 		lcddev.setxcmd=R32;
			lcddev.setycmd=R33;  
		}
	}else 				//����
	{	  				
		lcddev.dir=1;	//����
		lcddev.width=320;
		lcddev.height=240;
		{
			lcddev.wramcmd=R34;
	 		lcddev.setxcmd=R33;
			lcddev.setycmd=R32;  
		}
	} 
	ILI9320_Scan_Dir(DFT_SCAN_DIR);	//Ĭ��ɨ�跽��
}	 
//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height.
//68042,����ʱ��֧�ִ�������!! 
void ILI9320_SetDisplayWindow(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{   
	uint8_t hsareg,heareg,vsareg,veareg;
	uint16_t hsaval,heaval,vsaval,veaval; 
	width=sx+width-1;
	height=sy+height-1;
	{
		if(lcddev.dir==1)//����
		{
			//����ֵ
			hsaval=sy;				
			heaval=height;
			vsaval=lcddev.width-width-1;
			veaval=lcddev.width-sx-1;				
		}else
		{ 
			hsaval=sx;				
			heaval=width;
			vsaval=sy;
			veaval=height;
		}
		{
			hsareg=0X50;heareg=0X51;//ˮƽ���򴰿ڼĴ���
			vsareg=0X52;veareg=0X53;//��ֱ���򴰿ڼĴ���	  
		}								  
		//���üĴ���ֵ
		ILI9320_WriteRegData(hsareg,hsaval);
		ILI9320_WriteRegData(heareg,heaval);
		ILI9320_WriteRegData(vsareg,vsaval);
		ILI9320_WriteRegData(veareg,veaval);		
		ILI9320_SetCursor(sx,sy);	//���ù��λ��
	}
} 
//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ILI9320Һ��,�������������ǻ���ILI9320��!!!
//�������ͺŵ�����оƬ��û�в���! 
void ILI9320_Init(void)
{ 										  
	LCD_IO_Init();		 
 	delay(50); // delay 50 ms 
 	ILI9320_WriteRegData(0x0000,0x0001);
	delay(50); // delay 50 ms 
  	lcddev.id = ILI9320_ReadReg(0x0000);   
	{
		ILI9320_WriteRegData(0x00,0x0000);
		ILI9320_WriteRegData(0x01,0x0100);	//Driver Output Contral.
		ILI9320_WriteRegData(0x02,0x0700);	//LCD Driver Waveform Contral.
		ILI9320_WriteRegData(0x03,0x1030);//Entry Mode Set.
		//ILI9320_WriteRegData(0x03,0x1018);	//Entry Mode Set.
	
		ILI9320_WriteRegData(0x04,0x0000);	//Scalling Contral.
		ILI9320_WriteRegData(0x08,0x0202);	//Display Contral 2.(0x0207)
		ILI9320_WriteRegData(0x09,0x0000);	//Display Contral 3.(0x0000)
		ILI9320_WriteRegData(0x0a,0x0000);	//Frame Cycle Contal.(0x0000)
		ILI9320_WriteRegData(0x0c,(1<<0));	//Extern Display Interface Contral 1.(0x0000)
		ILI9320_WriteRegData(0x0d,0x0000);	//Frame Maker Position.
		ILI9320_WriteRegData(0x0f,0x0000);	//Extern Display Interface Contral 2.	    
		delay(50); 
		ILI9320_WriteRegData(0x07,0x0101);	//Display Contral.
		delay(50); 								  
		ILI9320_WriteRegData(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));	//Power Control 1.(0x16b0)
		ILI9320_WriteRegData(0x11,0x0007);								//Power Control 2.(0x0001)
		ILI9320_WriteRegData(0x12,(1<<8)|(1<<4)|(0<<0));				//Power Control 3.(0x0138)
		ILI9320_WriteRegData(0x13,0x0b00);								//Power Control 4.
		ILI9320_WriteRegData(0x29,0x0000);								//Power Control 7.
	
		ILI9320_WriteRegData(0x2b,(1<<14)|(1<<4));	    
		ILI9320_WriteRegData(0x50,0);	//Set X Star
		//ˮƽGRAM��ֹλ��Set X End.
		ILI9320_WriteRegData(0x51,239);	//Set Y Star
		ILI9320_WriteRegData(0x52,0);	//Set Y End.t.
		ILI9320_WriteRegData(0x53,319);	//
	
		ILI9320_WriteRegData(0x60,0x2700);	//Driver Output Control.
		ILI9320_WriteRegData(0x61,0x0001);	//Driver Output Control.
		ILI9320_WriteRegData(0x6a,0x0000);	//Vertical Srcoll Control.
	
		ILI9320_WriteRegData(0x80,0x0000);	//Display Position? Partial Display 1.
		ILI9320_WriteRegData(0x81,0x0000);	//RAM Address Start? Partial Display 1.
		ILI9320_WriteRegData(0x82,0x0000);	//RAM Address End-Partial Display 1.
		ILI9320_WriteRegData(0x83,0x0000);	//Displsy Position? Partial Display 2.
		ILI9320_WriteRegData(0x84,0x0000);	//RAM Address Start? Partial Display 2.
		ILI9320_WriteRegData(0x85,0x0000);	//RAM Address End? Partial Display 2.
	
		ILI9320_WriteRegData(0x90,(0<<7)|(16<<0));	//Frame Cycle Contral.(0x0013)
		ILI9320_WriteRegData(0x92,0x0000);	//Panel Interface Contral 2.(0x0000)
		ILI9320_WriteRegData(0x93,0x0001);	//Panel Interface Contral 3.
		ILI9320_WriteRegData(0x95,0x0110);	//Frame Cycle Contral.(0x0110)
		ILI9320_WriteRegData(0x97,(0<<8));	//
		ILI9320_WriteRegData(0x98,0x0000);	//Frame Cycle Contral.	   
		ILI9320_WriteRegData(0x07,0x0173);	//(0x0173)
	}
	ILI9320_Display_Dir(1);		 	//Ĭ��Ϊ����
//	ILI9320_LED=0;					//��������
//	ILI9320_Clear(lcddev.TextColor);
}

//��������
//color:Ҫ���������ɫ
void ILI9320_Clear(uint16_t color)
{
	uint32_t index=0;      
	uint32_t totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 			//�õ��ܵ���
    ILI9320_SetCursor(0x00,0x0000);	//���ù��λ�� 
	ILI9320_WriteRAM_Prepare();     		//��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		ILI9320_WR_DATA(color);	   
	}
}  
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void ILI9320_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint16_t i,j;
	uint16_t xlen=0;
	xlen=ex-sx+1;	 
	for(i=sy;i<=ey;i++)
		{
		 	ILI9320_SetCursor(sx,i);      				//���ù��λ�� 
			ILI9320_WriteRAM_Prepare();     			//��ʼд��GRAM	  
			for(j=0;j<xlen;j++)ILI9320_WR_DATA(color);	//���ù��λ�� 	    
		}
}  

void ILI9320_DrawHLine(uint16_t color, uint16_t sx, uint16_t sy, uint16_t Length){
	ILI9320_Fill(sx,sy,(sx+Length),sy,color);
}

void ILI9320_DrawVLine(uint16_t color, uint16_t sx, uint16_t sy, uint16_t Length){
	ILI9320_Fill(sx,sy,sx,(sy+Length),color);
}
