#include <Arduino.h>
#include "bspio/bspio.h"
#include "ili9341.h"
#include "ili9341_reg.h"
#include "font/font.h"
#include "tftlcd/lcd.h"
 
#define  ILI9341_WR_REG(x) 	LCD_IO_WriteReg(x)
#define  ILI9341_WR_DATA(x) LCD_IO_WriteData(x)
#define  ILI9341_RD_DATA    LCD_IO_ReadData
#define  ILI9341_WriteRegData(x,y) LCD_IO_WriteRegData(x,y)

//����LCD��Ҫ����
//Ĭ��Ϊ����

LCD_DrvTypeDef ILI9341_DRV = {
  .Init       = ILI9341_Init,
  .DisplayOn  = ILI9341_DisplayOn,
  .DisplayOff = ILI9341_DisplayOff,
  .SetCursor  = ILI9341_SetCursor,
  .ReadPixel  = ILI9341_ReadPixel,
  .WritePixel = ILI9341_WritePixel,
  .Fill	= ILI9341_Fill,
  
//option  
  .DrawHLine = ILI9341_DrawHLine,
  .DrawVLine = ILI9341_DrawVLine,
};


extern LCD_DevTypeDef lcddev;

uint16_t ILI9341_ReadReg(uint16_t Reg)
{										   
	ILI9341_WR_REG(Reg);		//д��Ҫ���ļĴ������
	delayMicroseconds(5);		  
	return ILI9341_RD_DATA();		//���ض�����ֵ
}   
//��ʼдGRAM
void ILI9341_WriteRAM_Prepare(void)
{
 	ILI9341_WR_REG(lcddev.wramcmd);
}	 
//LCDдGRAM
//RGB_Code:��ɫֵ
void ILI9341_WriteRAM(uint16_t RGB_Code)
{							    
	ILI9341_WR_DATA(RGB_Code);//дʮ��λGRAM
}
//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ

uint16_t ILI9341_BGR2RGB(uint16_t c)
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
uint16_t ILI9341_ReadPixel(uint16_t x,uint16_t y)
{
 	uint16_t r=0,g=0,b=0;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	ILI9341_SetCursor(x,y);	    
	ILI9341_WR_REG(0X2E);//9341/6804/3510 ���Ͷ�GRAMָ��
	if(ILI9341_RD_DATA())r=0;							//dummy Read	   
	opt_delay(2);	  
 	r=ILI9341_RD_DATA();  		  						//ʵ��������ɫ
 	opt_delay(2);	  
	b=ILI9341_RD_DATA(); 
	g=r&0XFF;		//����9341/5310/5510,��һ�ζ�ȡ����RG��ֵ,R��ǰ,G�ں�,��ռ8λ
	g<<=8;
	return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));//ILI9341/NT35310/NT35510��Ҫ��ʽת��һ��
}			 
//LCD������ʾ
void ILI9341_DisplayOn(void)
{					   
	ILI9341_WR_REG(0X29);	//������ʾ
}	 
//LCD�ر���ʾ
void ILI9341_DisplayOff(void)
{	   
	ILI9341_WR_REG(0X28);	//�ر���ʾ
}   
//���ù��λ��
//Xpos:������
//Ypos:������
void ILI9341_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	 
		ILI9341_WR_REG(lcddev.setxcmd); 
		ILI9341_WR_DATA(Xpos>>8); 
		ILI9341_WR_DATA(Xpos&0XFF);	 
		ILI9341_WR_REG(lcddev.setycmd); 
		ILI9341_WR_DATA(Ypos>>8); 
		ILI9341_WR_DATA(Ypos&0XFF);
} 		 
//����LCD���Զ�ɨ�跽��
//ע��:�����������ܻ��ܵ��˺������õ�Ӱ��(������9341/6804����������),
//����,һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.
//dir:0~7,����8������(���嶨���lcd.h)
//9320/9325/9328/4531/4535/1505/b505/8989/5408/9341/5310/5510��IC�Ѿ�ʵ�ʲ���	   	   
void ILI9341_Scan_Dir(uint8_t dir)
{
	uint16_t regval=0;
	uint16_t dirreg=0;
	uint16_t temp;  
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
		switch(dir)
		{
			case L2R_U2D://������,���ϵ���
				regval|=(0<<7)|(0<<6)|(0<<5); 
				break;
			case L2R_D2U://������,���µ���
				regval|=(1<<7)|(0<<6)|(0<<5); 
				break;
			case R2L_U2D://���ҵ���,���ϵ���
				regval|=(0<<7)|(1<<6)|(0<<5); 
				break;
			case R2L_D2U://���ҵ���,���µ���
				regval|=(1<<7)|(1<<6)|(0<<5); 
				break;	 
			case U2D_L2R://���ϵ���,������
				regval|=(0<<7)|(0<<6)|(1<<5); 
				break;
			case U2D_R2L://���ϵ���,���ҵ���
				regval|=(0<<7)|(1<<6)|(1<<5); 
				break;
			case D2U_L2R://���µ���,������
				regval|=(1<<7)|(0<<6)|(1<<5); 
				break;
			case D2U_R2L://���µ���,���ҵ���
				regval|=(1<<7)|(1<<6)|(1<<5); 
				break;	 
		}
		dirreg=0X36;
 		regval|=0X08;//5310/5510����ҪBGR   
		ILI9341_WriteRegData(dirreg,regval);
 		if((regval&0X20)||lcddev.dir==1)
		{
			if(lcddev.width<lcddev.height)//����X,Y
			{
				temp=lcddev.width;
				lcddev.width=lcddev.height;
				lcddev.height=temp;
 			}
		}else  
		{
			if(lcddev.width>lcddev.height)//����X,Y
			{
				temp=lcddev.width;
				lcddev.width=lcddev.height;
				lcddev.height=temp;
 			}
		}  
		{
			ILI9341_WR_REG(lcddev.setxcmd); 
			ILI9341_WR_DATA(0);ILI9341_WR_DATA(0);
			ILI9341_WR_DATA((lcddev.width-1)>>8);ILI9341_WR_DATA((lcddev.width-1)&0XFF);
			ILI9341_WR_REG(lcddev.setycmd); 
			ILI9341_WR_DATA(0);ILI9341_WR_DATA(0);
			ILI9341_WR_DATA((lcddev.height-1)>>8);ILI9341_WR_DATA((lcddev.height-1)&0XFF);  
		}
}   
//����
//x,y:����
//lcddev.TextColor:�˵����ɫ
void ILI9341_WritePixel(uint16_t x,uint16_t y,uint16_t color)
{
	ILI9341_SetCursor(x,y);		//���ù��λ�� 
	ILI9341_WriteRAM_Prepare();	//��ʼд��GRAM
	ILI9341_WR_DATA(color); 
}
//���ٻ���
//x,y:����
//color:��ɫ
void ILI9341_Fast_WritePixel(uint16_t x,uint16_t y,uint16_t color)
{	   
	ILI9341_WR_REG(lcddev.setxcmd); 
	ILI9341_WR_DATA(x>>8); 
	ILI9341_WR_DATA(x&0XFF);	 
	ILI9341_WR_REG(lcddev.setycmd); 
	ILI9341_WR_DATA(y>>8); 
	ILI9341_WR_DATA(y&0XFF);
	ILI9341_WR_REG(lcddev.wramcmd); 
	ILI9341_WR_DATA(color); 
}	 


//����LCD��ʾ����
//dir:0,������1,����
void ILI9341_Display_Dir(uint8_t dir)
{
	if(dir==0)			//����
	{
		lcddev.dir=0;	//����
		lcddev.width=240;
		lcddev.height=320;
		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;  	 
	}else 				//����
	{	  				
		lcddev.dir=1;	//����
		lcddev.width=320;
		lcddev.height=240;
		lcddev.wramcmd=0X2C;
	 	lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B;  	 
	} 
	ILI9341_Scan_Dir(DFT_SCAN_DIR);	//Ĭ��ɨ�跽��
}	 
//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height.
//68042,����ʱ��֧�ִ�������!! 
void ILI9341_SetDisplayWindow(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{   
	width=sx+width-1;
	height=sy+height-1;
	ILI9341_WR_REG(lcddev.setxcmd); 
	ILI9341_WR_DATA(sx>>8); 
	ILI9341_WR_DATA(sx&0XFF);	 
	ILI9341_WR_DATA(width>>8); 
	ILI9341_WR_DATA(width&0XFF);  
	ILI9341_WR_REG(lcddev.setycmd); 
	ILI9341_WR_DATA(sy>>8); 
	ILI9341_WR_DATA(sy&0XFF); 
	ILI9341_WR_DATA(height>>8); 
	ILI9341_WR_DATA(height&0XFF); 
} 
//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ILI9341Һ��,�������������ǻ���ILI9320��!!!
//�������ͺŵ�����оƬ��û�в���! 
void ILI9341_Init(void)
{ 										  
	LCD_IO_Init();		 
 	delay(50); // delay 50 ms 
	
	lcddev.id = 0x9341; 	   			   
	
	ILI9341_WR_REG(0xCF);  
	ILI9341_WR_DATA(0x00); 
	ILI9341_WR_DATA(0xC1); 
	ILI9341_WR_DATA(0X30); 
	ILI9341_WR_REG(0xED);  
	ILI9341_WR_DATA(0x64); 
	ILI9341_WR_DATA(0x03); 
	ILI9341_WR_DATA(0X12); 
	ILI9341_WR_DATA(0X81); 
	ILI9341_WR_REG(0xE8);  
	ILI9341_WR_DATA(0x85); 
	ILI9341_WR_DATA(0x10); 
	ILI9341_WR_DATA(0x7A); 
	ILI9341_WR_REG(0xCB);  
	ILI9341_WR_DATA(0x39); 
	ILI9341_WR_DATA(0x2C); 
	ILI9341_WR_DATA(0x00); 
	ILI9341_WR_DATA(0x34); 
	ILI9341_WR_DATA(0x02); 
	ILI9341_WR_REG(0xF7);  
	ILI9341_WR_DATA(0x20); 
	ILI9341_WR_REG(0xEA);  
	ILI9341_WR_DATA(0x00); 
	ILI9341_WR_DATA(0x00); 
	ILI9341_WR_REG(0xC0);    //Power control 
	ILI9341_WR_DATA(0x1B);   //VRH[5:0] 
	ILI9341_WR_REG(0xC1);    //Power control 
	ILI9341_WR_DATA(0x01);   //SAP[2:0];BT[3:0] 
	ILI9341_WR_REG(0xC5);    //VCM control 
	ILI9341_WR_DATA(0x30); 	 //3F
	ILI9341_WR_DATA(0x30); 	 //3C
	ILI9341_WR_REG(0xC7);    //VCM control2 
	ILI9341_WR_DATA(0XB7); 
	ILI9341_WR_REG(0x36);    // Memory Access Control 
	ILI9341_WR_DATA(0x48); 
	ILI9341_WR_REG(0x3A);   
	ILI9341_WR_DATA(0x55); 
	ILI9341_WR_REG(0xB1);   
	ILI9341_WR_DATA(0x00);   
	ILI9341_WR_DATA(0x1A); 
	ILI9341_WR_REG(0xB6);    // Display Function Control 
	ILI9341_WR_DATA(0x0A); 
	ILI9341_WR_DATA(0xA2); 
	ILI9341_WR_REG(0xF2);    // 3Gamma Function Disable 
	ILI9341_WR_DATA(0x00); 
	ILI9341_WR_REG(0x26);    //Gamma curve selected 
	ILI9341_WR_DATA(0x01); 
	ILI9341_WR_REG(0xE0);    //Set Gamma 
	ILI9341_WR_DATA(0x0F); 
	ILI9341_WR_DATA(0x2A); 
	ILI9341_WR_DATA(0x28); 
	ILI9341_WR_DATA(0x08); 
	ILI9341_WR_DATA(0x0E); 
	ILI9341_WR_DATA(0x08); 
	ILI9341_WR_DATA(0x54); 
	ILI9341_WR_DATA(0XA9); 
	ILI9341_WR_DATA(0x43); 
	ILI9341_WR_DATA(0x0A); 
	ILI9341_WR_DATA(0x0F); 
	ILI9341_WR_DATA(0x00); 
	ILI9341_WR_DATA(0x00); 
	ILI9341_WR_DATA(0x00); 
	ILI9341_WR_DATA(0x00); 		 
	ILI9341_WR_REG(0XE1);    //Set Gamma 
	ILI9341_WR_DATA(0x00); 
	ILI9341_WR_DATA(0x15); 
	ILI9341_WR_DATA(0x17); 
	ILI9341_WR_DATA(0x07); 
	ILI9341_WR_DATA(0x11); 
	ILI9341_WR_DATA(0x06); 
	ILI9341_WR_DATA(0x2B); 
	ILI9341_WR_DATA(0x56); 
	ILI9341_WR_DATA(0x3C); 
	ILI9341_WR_DATA(0x05); 
	ILI9341_WR_DATA(0x10); 
	ILI9341_WR_DATA(0x0F); 
	ILI9341_WR_DATA(0x3F); 
	ILI9341_WR_DATA(0x3F); 
	ILI9341_WR_DATA(0x0F); 
	ILI9341_WR_REG(0x2B); 
	ILI9341_WR_DATA(0x00);
	ILI9341_WR_DATA(0x00);
	ILI9341_WR_DATA(0x01);
	ILI9341_WR_DATA(0x3f);
	ILI9341_WR_REG(0x2A); 
	ILI9341_WR_DATA(0x00);
	ILI9341_WR_DATA(0x00);
	ILI9341_WR_DATA(0x00);
	ILI9341_WR_DATA(0xef);	 
	ILI9341_WR_REG(0x11); //Exit Sleep
	delay(120);
	ILI9341_WR_REG(0x29); //display on	
	ILI9341_Display_Dir(1);		 	//Ĭ��Ϊ����
//	ILI9341_LED=0;					//��������
//	ILI9341_Clear(lcddev.TextColor);
}  
//��������
//color:Ҫ���������ɫ
void ILI9341_Clear(uint16_t color)
{
	uint32_t index=0;      
	uint32_t totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 			//�õ��ܵ���
    ILI9341_SetCursor(0x00,0x0000);	//���ù��λ�� 

	ILI9341_WriteRAM_Prepare();     		//��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		ILI9341_WR_DATA(color);	   
	}
}  
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void ILI9341_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint16_t i,j;
	uint16_t xlen=0;
	{
		xlen=ex-sx+1;	 
		for(i=sy;i<=ey;i++)
		{
		 	ILI9341_SetCursor(sx,i);      				//���ù��λ�� 
			ILI9341_WriteRAM_Prepare();     			//��ʼд��GRAM	  
			for(j=0;j<xlen;j++)ILI9341_WR_DATA(color);	//���ù��λ�� 	    
		}
	}	 
}  

//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void ILI9341_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{  
	uint16_t height,width;
	uint16_t i,j;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
 	for(i=0;i<height;i++)
	{
 		ILI9341_SetCursor(sx,sy+i);   	//���ù��λ�� 
		ILI9341_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)ILI9341_WR_DATA(color[i*height+j]);//д������ 
	}	  
}
  
void ILI9341_DrawHLine(uint16_t color, uint16_t sx, uint16_t sy, uint16_t Length){
	ILI9341_Fill(sx,sy,(sx+Length),sy,color);
}

void ILI9341_DrawVLine(uint16_t color, uint16_t sx, uint16_t sy, uint16_t Length){
	ILI9341_Fill(sx,sy,sx,(sy+Length),color);
}
