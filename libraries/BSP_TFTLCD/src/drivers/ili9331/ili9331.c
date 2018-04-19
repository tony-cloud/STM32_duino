#include <Arduino.h>
#include "bspio/bspio.h"
#include "ili9331.h"
#include "ili9331_reg.h"
//#include "stdlib.h"
#include "font/font.h"
#include "tftlcd/lcd.h"
 
#define  ILI9331_WR_REG(x) 	LCD_IO_WriteReg(x)
#define  ILI9331_WR_DATA(x) LCD_IO_WriteData(x)
#define  ILI9331_RD_DATA    LCD_IO_ReadData
#define  ILI9331_WriteRegData(x,y) LCD_IO_WriteRegData(x,y)


//����LCD��Ҫ����
//Ĭ��Ϊ����

LCD_DrvTypeDef ILI9331_DRV = {
  .Init       = ILI9331_Init,
  .ReadPixel  = ILI9331_ReadPixel,
  .WritePixel = ILI9331_WritePixel,
  .Fill	= ILI9331_Fill,
  
//option  
  .DisplayOn  = ILI9331_DisplayOn,
  .DisplayOff = ILI9331_DisplayOff,
  .SetCursor  = ILI9331_SetCursor,
};


extern LCD_DevTypeDef lcddev;

uint16_t ILI9331_ReadReg(uint16_t Reg)
{										   
	ILI9331_WR_REG(Reg);		//д��Ҫ���ļĴ������
	delayMicroseconds(5);		  
	return ILI9331_RD_DATA();		//���ض�����ֵ
}   
//��ʼдGRAM
void ILI9331_WriteRAM_Prepare(void)
{
 	ILI9331_WR_REG(lcddev.wramcmd);
}	 
//LCDдGRAM
//RGB_Code:��ɫֵ
void ILI9331_WriteRAM(uint16_t RGB_Code)
{							    
	ILI9331_WR_DATA(RGB_Code);//дʮ��λGRAM
}
//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ

uint16_t ILI9331_BGR2RGB(uint16_t c)
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
uint16_t ILI9331_ReadPixel(uint16_t x,uint16_t y)
{
 	uint16_t r=0;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	ILI9331_SetCursor(x,y);	    
    ILI9331_WR_REG(R34);      		 				//����IC���Ͷ�GRAMָ��
	r=ILI9331_RD_DATA();							//dummy Read	   
	opt_delay(2);	  
 	r=ILI9331_RD_DATA();  		  						//ʵ��������ɫ
    return ILI9331_BGR2RGB(r);						//����IC
}			 
//LCD������ʾ
void ILI9331_DisplayOn(void)
{					   
	ILI9331_WriteRegData(R7,0x0173); 				 	//������ʾ
}	 
//LCD�ر���ʾ
void ILI9331_DisplayOff(void)
{	   
	ILI9331_WriteRegData(R7,0x0);//�ر���ʾ 
}   
//���ù��λ��
//Xpos:������
//Ypos:������
void ILI9331_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	 
	{
		if(lcddev.dir==1)Xpos=lcddev.width-1-Xpos;//������ʵ���ǵ�תx,y����
		ILI9331_WriteRegData(lcddev.setxcmd, Xpos);
		ILI9331_WriteRegData(lcddev.setycmd, Ypos);
	}	 
} 		 
//����LCD���Զ�ɨ�跽��
//ע��:�����������ܻ��ܵ��˺������õ�Ӱ��(������9341/6804����������),
//����,һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.
//dir:0~7,����8������(���嶨���lcd.h)
//9320/9325/9328/4531/4535/1505/b505/8989/5408/9341/5310/5510��IC�Ѿ�ʵ�ʲ���	   	   
void ILI9331_Scan_Dir(uint8_t dir)
{
	uint16_t regval=0;
	uint16_t dirreg=0;
	if(lcddev.dir==1)//����ʱ����6804���ı�ɨ�跽��
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
		ILI9331_WriteRegData(dirreg,regval);
	}
}   
//����
//x,y:����
//lcddev.TextColor:�˵����ɫ
void ILI9331_WritePixel(uint16_t x,uint16_t y,uint16_t color)
{
	ILI9331_SetCursor(x,y);		//���ù��λ�� 
	ILI9331_WriteRAM_Prepare();	//��ʼд��GRAM
	ILI9331_WR_DATA(color); 
}
//���ٻ���
//x,y:����
//color:��ɫ
void ILI9331_Fast_WritePixel(uint16_t x,uint16_t y,uint16_t color)
{	   
	{
 		if(lcddev.dir==1)x=lcddev.width-1-x;//������ʵ���ǵ�תx,y����
		ILI9331_WriteRegData(lcddev.setxcmd,x);
		ILI9331_WriteRegData(lcddev.setycmd,y);
	}			 
	ILI9331_WR_REG(lcddev.wramcmd); 
	ILI9331_WR_DATA(color); 
}	 


//����LCD��ʾ����
//dir:0,������1,����
void ILI9331_Display_Dir(uint8_t dir)
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
	ILI9331_Scan_Dir(DFT_SCAN_DIR);	//Ĭ��ɨ�跽��
}	 
//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height.
//68042,����ʱ��֧�ִ�������!! 
void ILI9331_SetDisplayWindow(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
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
		ILI9331_WriteRegData(hsareg,hsaval);
		ILI9331_WriteRegData(heareg,heaval);
		ILI9331_WriteRegData(vsareg,vsaval);
		ILI9331_WriteRegData(veareg,veaval);		
		ILI9331_SetCursor(sx,sy);	//���ù��λ��
	}
} 
//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ILI9331Һ��,�������������ǻ���ILI9320��!!!
//�������ͺŵ�����оƬ��û�в���! 
void ILI9331_Init(void)
{ 										  
	LCD_IO_Init();		 
 	delay(50); // delay 50 ms 
 	ILI9331_WriteRegData(0x0000,0x0001);
	delay(50); // delay 50 ms 
  	lcddev.id = 0X9331;   
 	{
		ILI9331_WriteRegData(0x00E7, 0x1014);
		ILI9331_WriteRegData(0x0001, 0x0100); // set SS and SM bit
		ILI9331_WriteRegData(0x0002, 0x0200); // set 1 line inversion
        ILI9331_WriteRegData(0x0003,(1<<12)|(3<<4)|(1<<3));//65K    
		//ILI9331_WriteRegData(0x0003, 0x1030); // set GRAM write direction and BGR=1.
		ILI9331_WriteRegData(0x0008, 0x0202); // set the back porch and front porch
		ILI9331_WriteRegData(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
		ILI9331_WriteRegData(0x000A, 0x0000); // FMARK function
		ILI9331_WriteRegData(0x000C, 0x0000); // RGB interface setting
		ILI9331_WriteRegData(0x000D, 0x0000); // Frame marker Position
		ILI9331_WriteRegData(0x000F, 0x0000); // RGB interface polarity
		//*************Power On sequence ****************//
		ILI9331_WriteRegData(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
		ILI9331_WriteRegData(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
		ILI9331_WriteRegData(0x0012, 0x0000); // VREG1OUT voltage
		ILI9331_WriteRegData(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
		delay(200); // Dis-charge capacitor power voltage
		ILI9331_WriteRegData(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
		ILI9331_WriteRegData(0x0011, 0x0227); // DC1[2:0], DC0[2:0], VC[2:0]
		delay(50); // Delay 50ms
		ILI9331_WriteRegData(0x0012, 0x000C); // Internal reference voltage= Vci;
		delay(50); // Delay 50ms
		ILI9331_WriteRegData(0x0013, 0x0800); // Set VDV[4:0] for VCOM amplitude
		ILI9331_WriteRegData(0x0029, 0x0011); // Set VCM[5:0] for VCOMH
		ILI9331_WriteRegData(0x002B, 0x000B); // Set Frame Rate
		delay(50); // Delay 50ms
		ILI9331_WriteRegData(0x0020, 0x0000); // GRAM horizontal Address
		ILI9331_WriteRegData(0x0021, 0x013f); // GRAM Vertical Address
		// ----------- Adjust the Gamma Curve ----------//
		ILI9331_WriteRegData(0x0030, 0x0000);
		ILI9331_WriteRegData(0x0031, 0x0106);
		ILI9331_WriteRegData(0x0032, 0x0000);
		ILI9331_WriteRegData(0x0035, 0x0204);
		ILI9331_WriteRegData(0x0036, 0x160A);
		ILI9331_WriteRegData(0x0037, 0x0707);
		ILI9331_WriteRegData(0x0038, 0x0106);
		ILI9331_WriteRegData(0x0039, 0x0707);
		ILI9331_WriteRegData(0x003C, 0x0402);
		ILI9331_WriteRegData(0x003D, 0x0C0F);
		//------------------ Set GRAM area ---------------//
		ILI9331_WriteRegData(0x0050, 0x0000); // Horizontal GRAM Start Address
		ILI9331_WriteRegData(0x0051, 0x00EF); // Horizontal GRAM End Address
		ILI9331_WriteRegData(0x0052, 0x0000); // Vertical GRAM Start Address
		ILI9331_WriteRegData(0x0053, 0x013F); // Vertical GRAM Start Address
		ILI9331_WriteRegData(0x0060, 0x2700); // Gate Scan Line
		ILI9331_WriteRegData(0x0061, 0x0001); // NDL,VLE, REV 
		ILI9331_WriteRegData(0x006A, 0x0000); // set scrolling line
		//-------------- Partial Display Control ---------//
		ILI9331_WriteRegData(0x0080, 0x0000);
		ILI9331_WriteRegData(0x0081, 0x0000);
		ILI9331_WriteRegData(0x0082, 0x0000);
		ILI9331_WriteRegData(0x0083, 0x0000);
		ILI9331_WriteRegData(0x0084, 0x0000);
		ILI9331_WriteRegData(0x0085, 0x0000);
		//-------------- Panel Control -------------------//
		ILI9331_WriteRegData(0x0090, 0x0010);
		ILI9331_WriteRegData(0x0092, 0x0600);
		ILI9331_WriteRegData(0x0007, 0x0133); // 262K color and display ON
	}		 
	ILI9331_Display_Dir(1);		 	//Ĭ��Ϊ����
//	ILI9331_LED=0;					//��������
//	ILI9331_Clear(lcddev.TextColor);
}  
//��������
//color:Ҫ���������ɫ
void ILI9331_Clear(uint16_t color)
{
	uint32_t index=0;      
	uint32_t totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 			//�õ��ܵ���
	ILI9331_SetCursor(0x00,0x0000);	//���ù��λ�� 

	ILI9331_WriteRAM_Prepare();     		//��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		ILI9331_WR_DATA(color);	   
	}
}  
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void ILI9331_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint16_t i,j;
	uint16_t xlen=0;
	{
		xlen=ex-sx+1;	 
		for(i=sy;i<=ey;i++)
		{
		 	ILI9331_SetCursor(sx,i);      				//���ù��λ�� 
			ILI9331_WriteRAM_Prepare();     			//��ʼд��GRAM	  
			for(j=0;j<xlen;j++)ILI9331_WR_DATA(color);	//���ù��λ�� 	    
		}
	}	 
}  

//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void ILI9331_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{  
	uint16_t height,width;
	uint16_t i,j;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
 	for(i=0;i<height;i++)
	{
 		ILI9331_SetCursor(sx,sy+i);   	//���ù��λ�� 
		ILI9331_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)ILI9331_WR_DATA(color[i*height+j]);//д������ 
	}	  
}  
