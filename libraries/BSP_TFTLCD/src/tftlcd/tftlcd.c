#include <Arduino.h>
#include "bspio/bspio.h"
#include "font/font.h"
#include "lcd.h" 
#include "tftlcd.h"


extern LCD_DrvTypeDef ILI9320_DRV;
extern LCD_DrvTypeDef ILI9325_DRV;
extern LCD_DrvTypeDef ILI9328_DRV;
extern LCD_DrvTypeDef ILI9331_DRV;
extern LCD_DrvTypeDef ILI9341_DRV;
extern LCD_DrvTypeDef ILI9348_DRV;
extern LCD_DrvTypeDef ILI9481_DRV;
extern LCD_DrvTypeDef ILI9486_DRV;
extern LCD_DrvTypeDef SPFD5408_DRV;
extern LCD_DrvTypeDef SPFD5420_DRV;
extern LCD_DrvTypeDef ILI93XX_DRV;

#if BSP_TFT_LCD == ILI9320
#  define TFTLCD_DRV ILI9320_DRV
#elif BSP_TFT_LCD == ILI9325
#  define TFTLCD_DRV ILI9325_DRV
#elif BSP_TFT_LCD == ILI9328
#  define TFTLCD_DRV ILI9328_DRV
#elif BSP_TFT_LCD == ILI9331
#  define TFTLCD_DRV ILI9331_DRV
#elif BSP_TFT_LCD == ILI9341
#  define TFTLCD_DRV ILI9341_DRV
#elif BSP_TFT_LCD == ILI9348
#  define TFTLCD_DRV ILI9348_DRV
#elif BSP_TFT_LCD == ILI9481
#  define TFTLCD_DRV ILI9481_DRV
#elif BSP_TFT_LCD == ILI9486
#  define TFTLCD_DRV ILI9486_DRV
#elif BSP_TFT_LCD == SPFD5408
#  define TFTLCD_DRV SPFD5408_DRV
#elif BSP_TFT_LCD == SPFD5420
#  define TFTLCD_DRV SPFD5420_DRV
#elif (BSP_TFT_LCD == RM68021)|| (BSP_TFT_LCD == RM68042)|| (BSP_TFT_LCD == B505)\
      ||(BSP_TFT_LCD == C505)||(BSP_TFT_LCD == LGDP4531)||(BSP_TFT_LCD == LGDP4535)\
	  ||(BSP_TFT_LCD == NT35310)||(BSP_TFT_LCD == NT35510) ||(BSP_TFT_LCD == ILI93XX)
#  define TFTLCD_DRV ILI93XX_DRV
#else
# error  "!unsupport lcd drver!"	
#endif

#define  LCD_WR_REG(x) 	LCD_IO_WriteReg(x)
#define  LCD_WR_DATA(x) LCD_IO_WriteData(x)
#define  LCD_RD_DATA    LCD_IO_ReadData
#define  LCD_WriteRegData(x,y) LCD_IO_WriteRegData(x,y)

LCD_DrvTypeDef* pLcdDrv = &TFTLCD_DRV;
//����LCD��Ҫ����   lcd.h
//Ĭ��Ϊ����  
LCD_DevTypeDef lcddev ={
	.TextColor = 0x0000,	//������ɫ
	.BackColor = 0xffff,  //����ɫ 
};


//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
uint16_t LCD_ReadPixel(uint16_t x,uint16_t y)
{
	return pLcdDrv->ReadPixel(x,y);
}

//LCD������ʾ
void LCD_DisplayOn(void)
{					   
     pLcdDrv->DisplayOn();
}

//LCD�ر���ʾ
void LCD_DisplayOff(void)
{	   
	pLcdDrv->DisplayOff();
}

//���ù��λ��
//Xpos:������
//Ypos:������
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	 
	pLcdDrv->SetCursor(Xpos, Ypos);
} 		 

//����
//x,y:����
//lcddev.TextColor:�˵����ɫ
void LCD_WritePixel(uint16_t x,uint16_t y,uint16_t color)
{
	pLcdDrv->WritePixel(x,y,color);
}


//���ô���,���Զ����û������굽�������Ͻ�(sx,sy).
//sx,sy:������ʼ����(���Ͻ�)
//width,height:���ڿ�Ⱥ͸߶�,�������0!!
//�����С:width*height.
//68042,����ʱ��֧�ִ�������!! 
void LCD_SetDisplayWindow(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{   
	pLcdDrv->SetDisplayWindow(sx,sy,width,height);
} 

//��ʼ��lcd
//�ó�ʼ���������Գ�ʼ������ILI93XXҺ��,�������������ǻ���ILI9320��!!!
//�������ͺŵ�����оƬ��û�в���! 
void LCDx_Init(void)
{ 										  
	pLcdDrv->Init();
}
void LCD_WriteRAM_Prepare(void){
   
};
//��������
//color:Ҫ���������ɫ
void LCD_Clear(uint16_t color)
{
   LCD_Fill(0,0,lcddev.width-1,lcddev.height-1, color);
}  
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
{
  pLcdDrv->Fill(sx,sy,ex,ey,color);
}
//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	if(x1 ==x2){
		pLcdDrv->DrawVLine(lcddev.TextColor, x1, y1, y2-y1);
		return;
	}else if(y1 ==y2){
		pLcdDrv->DrawHLine(lcddev.TextColor, x1, y1, x2-x1);
		return;
	}
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(uint16_t t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_WritePixel(uRow,uCol,lcddev.TextColor);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    
//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_WritePixel(x0+a,y0-b,lcddev.TextColor);             //5
 		LCD_WritePixel(x0+b,y0-a,lcddev.TextColor);             //0           
		LCD_WritePixel(x0+b,y0+a,lcddev.TextColor);             //4               
		LCD_WritePixel(x0+a,y0+b,lcddev.TextColor);             //6 
		LCD_WritePixel(x0-a,y0+b,lcddev.TextColor);             //1       
 		LCD_WritePixel(x0-b,y0+a,lcddev.TextColor);             
		LCD_WritePixel(x0-a,y0-b,lcddev.TextColor);             //2             
  		LCD_WritePixel(x0-b,y0-a,lcddev.TextColor);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 									  
//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode)
{  							  
    uint8_t temp,t1,t;
	uint16_t y0=y;
	uint16_t colortemp=lcddev.TextColor;      			     
	//���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	if(!mode) //�ǵ��ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)lcddev.TextColor=colortemp;
				else lcddev.TextColor=lcddev.BackColor;
				LCD_WritePixel(x,y,lcddev.TextColor);	
				temp<<=1;
				y++;
				if(x>=lcddev.width){lcddev.TextColor=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){lcddev.TextColor=colortemp;return;}//��������
					break;
				}
			}  	 
	    }    
	}else//���ӷ�ʽ
	{
	    for(t=0;t<size;t++)
	    {   
			if(size==12)temp=asc2_1206[num][t];  //����1206����
			else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
			{			    
		        if(temp&0x80)LCD_WritePixel(x,y,lcddev.TextColor); 
				temp<<=1;
				y++;
				if(x>=lcddev.height){lcddev.TextColor=colortemp;return;}//��������
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=lcddev.width){lcddev.TextColor=colortemp;return;}//��������
					break;
				}
			}  	 
	    }     
	}
	lcddev.TextColor=colortemp;	    	   	 	  
}
   
//m^n����
//����ֵ:m^n�η�.
uint32_t LCD_Pow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}

//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode)
{  
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 
//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p)
{         
	uint8_t x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}






























