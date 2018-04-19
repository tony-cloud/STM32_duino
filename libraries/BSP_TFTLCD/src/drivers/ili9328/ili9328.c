#include <Arduino.h>
#include "bspio/bspio.h"
#include "ili9328.h"
#include "ili9328_reg.h"
//#include "stdlib.h"
#include "font/font.h"
#include "tftlcd/lcd.h"
 
#define  ILI9328_WR_REG(x) 	LCD_IO_WriteReg(x)
#define  ILI9328_WR_DATA(x) LCD_IO_WriteData(x)
#define  ILI9328_RD_DATA    LCD_IO_ReadData
#define  ILI9328_WriteRegData(x,y) LCD_IO_WriteRegData(x,y)


//����LCD��Ҫ����
//Ĭ��Ϊ����

LCD_DrvTypeDef ILI9328_DRV = {
  .Init       = ILI9328_Init,
  .ReadPixel  = ILI9328_ReadPixel,
  .WritePixel = ILI9328_WritePixel,
  .Fill	= ILI9328_Fill,
  
//option  
  .DisplayOn  = ILI9328_DisplayOn,
  .DisplayOff = ILI9328_DisplayOff,
  .SetCursor  = ILI9328_SetCursor,
};


extern LCD_DevTypeDef lcddev;

uint16_t ILI9328_ReadReg(uint16_t Reg)
{										   
	ILI9328_WR_REG(Reg);		//д��Ҫ���ļĴ������
	delayMicroseconds(5);		  
	return ILI9328_RD_DATA();		//���ض�����ֵ
}   
//��ʼдGRAM
void ILI9328_WriteRAM_Prepare(void)
{
 	ILI9328_WR_REG(lcddev.wramcmd);
}	 
//LCDдGRAM
//RGB_Code:��ɫֵ
void ILI9328_WriteRAM(uint16_t RGB_Code)
{							    
	ILI9328_WR_DATA(RGB_Code);//дʮ��λGRAM
}
//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ

uint16_t ILI9328_BGR2RGB(uint16_t c)
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
uint16_t ILI9328_ReadPixel(uint16_t x,uint16_t y)
{
 	uint16_t r=0;
	if(x>=lcddev.width||y>=lcddev.height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	ILI9328_SetCursor(x,y);	    
	ILI9328_WR_REG(R34);      		 				//����IC���Ͷ�GRAMָ��
	r=ILI9328_RD_DATA();							//dummy Read	   
	opt_delay(2);	  
 	r=ILI9328_RD_DATA();  		  						//ʵ��������ɫ
    return ILI9328_BGR2RGB(r);						//����IC
}			 
//LCD������ʾ
void ILI9328_DisplayOn(void)
{					   
	ILI9328_WriteRegData(R7,0x0173); 				 	//������ʾ
}	 
//LCD�ر���ʾ
void ILI9328_DisplayOff(void)
{	   
	ILI9328_WriteRegData(R7,0x0);//�ر���ʾ 
}   
//���ù��λ��
//Xpos:������
//Ypos:������
void ILI9328_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	 

	{
		if(lcddev.dir==1)Xpos=lcddev.width-1-Xpos;//������ʵ���ǵ�תx,y����
		ILI9328_WriteRegData(lcddev.setxcmd, Xpos);
		ILI9328_WriteRegData(lcddev.setycmd, Ypos);
	}	 
} 		 
//����LCD���Զ�ɨ�跽��
//ע��:�����������ܻ��ܵ��˺������õ�Ӱ��(������9341/6804����������),
//����,һ������ΪL2R_U2D����,�������Ϊ����ɨ�跽ʽ,���ܵ�����ʾ������.
//dir:0~7,����8������(���嶨���lcd.h)
//9320/9325/9328/4531/4535/1505/b505/8989/5408/9341/5310/5510��IC�Ѿ�ʵ�ʲ���	   	   
void ILI9328_Scan_Dir(uint8_t dir)
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
		ILI9328_WriteRegData(dirreg,regval);
	}
}   
//����
//x,y:����
//lcddev.TextColor:�˵����ɫ
void ILI9328_WritePixel(uint16_t x,uint16_t y,uint16_t color)
{
	ILI9328_SetCursor(x,y);		//���ù��λ�� 
	ILI9328_WriteRAM_Prepare();	//��ʼд��GRAM
	ILI9328_WR_DATA(color); 
}
//���ٻ���
//x,y:����
//color:��ɫ
void ILI9328_Fast_WritePixel(uint16_t x,uint16_t y,uint16_t color)
{	   

	{
 		if(lcddev.dir==1)x=lcddev.width-1-x;//������ʵ���ǵ�תx,y����
		ILI9328_WriteRegData(lcddev.setxcmd,x);
		ILI9328_WriteRegData(lcddev.setycmd,y);
	}			 
	ILI9328_WR_REG(lcddev.wramcmd); 
	ILI9328_WR_DATA(color); 
}	 


//����LCD��ʾ����
//dir:0,������1,����
void ILI9328_Display_Dir(uint8_t dir)
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
	ILI9328_Scan_Dir(DFT_SCAN_DIR);	//Ĭ��ɨ�跽��
}	 
//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height.
//68042,����ʱ��֧�ִ�������!! 
void ILI9328_SetDisplayWindow(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
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
		ILI9328_WriteRegData(hsareg,hsaval);
		ILI9328_WriteRegData(heareg,heaval);
		ILI9328_WriteRegData(vsareg,vsaval);
		ILI9328_WriteRegData(veareg,veaval);		
		ILI9328_SetCursor(sx,sy);	//���ù��λ��
	}
} 
//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ILI93XXҺ��,�������������ǻ���ILI9320��!!!
//�������ͺŵ�����оƬ��û�в���! 
void ILI9328_Init(void)
{ 										  
	LCD_IO_Init();		 
 	delay(50); // delay 50 ms 
 	ILI9328_WriteRegData(0x0000,0x0001);
	delay(50); // delay 50 ms 
  	lcddev.id = 0X9328;   
	{
  		ILI9328_WriteRegData(0x00EC,0x108F);// internal timeing      
 		ILI9328_WriteRegData(0x00EF,0x1234);// ADD        
		//ILI9328_WriteRegData(0x00e7,0x0010);      
        //ILI9328_WriteRegData(0x0000,0x0001);//�����ڲ�ʱ��
        ILI9328_WriteRegData(0x0001,0x0100);     
        ILI9328_WriteRegData(0x0002,0x0700);//��Դ����                    
		//ILI9328_WriteRegData(0x0003,(1<<3)|(1<<4) ); 	//65K  RGB
		//DRIVE TABLE(�Ĵ��� 03H)
		//BIT3=AM BIT4:5=ID0:1
		//AM ID0 ID1   FUNCATION
		// 0  0   0	   R->L D->U
		// 1  0   0	   D->U	R->L
		// 0  1   0	   L->R D->U
		// 1  1   0    D->U	L->R
		// 0  0   1	   R->L U->D
		// 1  0   1    U->D	R->L
		// 0  1   1    L->R U->D �����������.
		// 1  1   1	   U->D	L->R
        ILI9328_WriteRegData(0x0003,(1<<12)|(3<<4)|(0<<3) );//65K    
        ILI9328_WriteRegData(0x0004,0x0000);                                   
        ILI9328_WriteRegData(0x0008,0x0202);	           
        ILI9328_WriteRegData(0x0009,0x0000);         
        ILI9328_WriteRegData(0x000a,0x0000);//display setting         
        ILI9328_WriteRegData(0x000c,0x0001);//display setting          
        ILI9328_WriteRegData(0x000d,0x0000);//0f3c          
        ILI9328_WriteRegData(0x000f,0x0000);
		//��Դ����
        ILI9328_WriteRegData(0x0010,0x0000);   
        ILI9328_WriteRegData(0x0011,0x0007);
        ILI9328_WriteRegData(0x0012,0x0000);                                                                 
        ILI9328_WriteRegData(0x0013,0x0000);                 
     	ILI9328_WriteRegData(0x0007,0x0001);                 
       	delay(50); 
        ILI9328_WriteRegData(0x0010,0x1490);   
        ILI9328_WriteRegData(0x0011,0x0227);
        delay(50); 
        ILI9328_WriteRegData(0x0012,0x008A);                  
        delay(50); 
        ILI9328_WriteRegData(0x0013,0x1a00);   
        ILI9328_WriteRegData(0x0029,0x0006);
        ILI9328_WriteRegData(0x002b,0x000d);
        delay(50); 
        ILI9328_WriteRegData(0x0020,0x0000);                                                            
        ILI9328_WriteRegData(0x0021,0x0000);           
		delay(50); 
		//٤��У��
        ILI9328_WriteRegData(0x0030,0x0000); 
        ILI9328_WriteRegData(0x0031,0x0604);   
        ILI9328_WriteRegData(0x0032,0x0305);
        ILI9328_WriteRegData(0x0035,0x0000);
        ILI9328_WriteRegData(0x0036,0x0C09); 
        ILI9328_WriteRegData(0x0037,0x0204);
        ILI9328_WriteRegData(0x0038,0x0301);        
        ILI9328_WriteRegData(0x0039,0x0707);     
        ILI9328_WriteRegData(0x003c,0x0000);
        ILI9328_WriteRegData(0x003d,0x0a0a);
        delay(50); 
        ILI9328_WriteRegData(0x0050,0x0000); //ˮƽGRAM��ʼλ�� 
        ILI9328_WriteRegData(0x0051,0x00ef); //ˮƽGRAM��ֹλ��                    
        ILI9328_WriteRegData(0x0052,0x0000); //��ֱGRAM��ʼλ��                    
        ILI9328_WriteRegData(0x0053,0x013f); //��ֱGRAM��ֹλ��  
 
        ILI9328_WriteRegData(0x0060,0xa700);        
        ILI9328_WriteRegData(0x0061,0x0001); 
        ILI9328_WriteRegData(0x006a,0x0000);
        ILI9328_WriteRegData(0x0080,0x0000);
        ILI9328_WriteRegData(0x0081,0x0000);
        ILI9328_WriteRegData(0x0082,0x0000);
        ILI9328_WriteRegData(0x0083,0x0000);
        ILI9328_WriteRegData(0x0084,0x0000);
        ILI9328_WriteRegData(0x0085,0x0000);
      
        ILI9328_WriteRegData(0x0090,0x0010);     
        ILI9328_WriteRegData(0x0092,0x0600);  
        //������ʾ����    
        ILI9328_WriteRegData(0x0007,0x0133); 
	}
	ILI9328_Display_Dir(1);		 	//Ĭ��Ϊ����
//	ILI9328_LED=0;					//��������
//	ILI9328_Clear(lcddev.TextColor);
}  
//��������
//color:Ҫ���������ɫ
void ILI9328_Clear(uint16_t color)
{
	uint32_t index=0;      
	uint32_t totalpoint=lcddev.width;
	totalpoint*=lcddev.height; 			//�õ��ܵ���
    ILI9328_SetCursor(0x00,0x0000);	//���ù��λ�� 

	ILI9328_WriteRAM_Prepare();     		//��ʼд��GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		ILI9328_WR_DATA(color);	   
	}
}  
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void ILI9328_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{          
	uint16_t i,j;
	uint16_t xlen=0;
	{
		xlen=ex-sx+1;	 
		for(i=sy;i<=ey;i++)
		{
		 	ILI9328_SetCursor(sx,i);      				//���ù��λ�� 
			ILI9328_WriteRAM_Prepare();     			//��ʼд��GRAM	  
			for(j=0;j<xlen;j++)ILI9328_WR_DATA(color);	//���ù��λ�� 	    
		}
	}	 
}  

//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void ILI9328_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
{  
	uint16_t height,width;
	uint16_t i,j;
	width=ex-sx+1; 			//�õ����Ŀ��
	height=ey-sy+1;			//�߶�
 	for(i=0;i<height;i++)
	{
 		ILI9328_SetCursor(sx,sy+i);   	//���ù��λ�� 
		ILI9328_WriteRAM_Prepare();     //��ʼд��GRAM
		for(j=0;j<width;j++)ILI9328_WR_DATA(color[i*height+j]);//д������ 
	}	  
}  
