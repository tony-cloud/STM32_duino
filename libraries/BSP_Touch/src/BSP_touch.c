#include <Arduino.h>
#include "BSP_touch.h"
//#include "../LCD/BSP_tft_lcd.h"
#include "math.h"
//������������֧��ADS7843/7846/UH7843/7846/XPT2046/TSC2046/OTT2001A�ȣ� ����	   
 
//������оƬ��������	   
#define PEN  		digitalRead(tp_dev.irq)  	    //T_PEN
#define DOUT 		digitalRead(tp_dev.miso)   	    //T_MISO
#define TDIN0 		digitalWrite(tp_dev.mosi,LOW)  	//T_MOSI
#define TDIN1 		digitalWrite(tp_dev.mosi,HIGH)  	//T_MOSI
#define TCLK0 		digitalWrite(tp_dev.sck,LOW)  	//T_SCK
#define TCLK1 		digitalWrite(tp_dev.sck,HIGH)  	//T_SCK
#define TCS0  		digitalWrite(tp_dev.cs,LOW)  	//T_CS
#define TCS1  		digitalWrite(tp_dev.cs,HIGH)  	//T_CS

#define delay_ms(x)  delay(x)
#define delay_us(x)  delayMicroseconds(x)

_m_tp_dev tp_dev=
{
	.init = TP_Init,
	.scan = TP_Scan,
	.adjust = TP_Adjust,
	.xfac = TOUCH_XFAC/1000.0,   /*xfac*/
	.yfac = TOUCH_YFAC/1000.0,   /*yfac*/
	.xoff = TOUCH_XOFF,   /*xoff*/
	.yoff = TOUCH_YOFF,   /*yoff*/
	.touchtype = 1,   /*touchtype*/
	
#ifndef TOUCH_XYCHG
	.CMD_RDX = 0XD0,
	.CMD_RDY = 0X90,
#elif (TOUCH_XYCHG==0)
	.CMD_RDX = 0XD0,
	.CMD_RDY = 0X90,
#else	
	.CMD_RDX = 0X90,
	.CMD_RDY = 0XD0,
#endif


#ifndef TOUCH_MISO
    .miso = TOUCH_MISO,
#endif
#ifndef TOUCH_MOSI
	.mosi = TOUCH_MOSI,
#endif
#ifndef TOUCH_SCK
	.sck = TOUCH_SCK,
#endif
#ifndef TOUCH_NCS
	.cs  = TOUCH_NCS,
#endif
#ifndef TOUCH_NIRQ
	.irq = TOUCH_NIRQ,
#endif
};

//SPIд����
//������ICд��1byte����    
//num:Ҫд�������
void TP_Write_Byte(uint8_t num)    
{  
	uint8_t count=0;   
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80)digitalWrite(tp_dev.mosi,HIGH);  
		else digitalWrite(tp_dev.mosi,LOW);   
		num<<=1;    
		digitalWrite(tp_dev.sck,LOW); 	 
		digitalWrite(tp_dev.sck,HIGH);		//��������Ч	        
	}		 			    
}

//SPI������ 
//�Ӵ�����IC��ȡadcֵ
//CMD:ָ��
//����ֵ:����������	   
uint16_t TP_Read_AD(uint8_t CMD)	  
{ 	 
	uint8_t count=0; 	  
	uint16_t Num=0; 
	digitalWrite(tp_dev.sck,LOW);		//������ʱ�� 	 
	TDIN0; 	//����������
	digitalWrite(tp_dev.cs,LOW); 		//ѡ�д�����IC
	TP_Write_Byte(CMD);//����������
	delay_us(6);//ADS7846��ת��ʱ���Ϊ6us
	digitalWrite(tp_dev.sck,LOW); 	     	    
	delay_us(1);    	   
	digitalWrite(tp_dev.sck,HIGH);		//��1��ʱ�ӣ����BUSY
	delay_us(1);    
	digitalWrite(tp_dev.sck,LOW); 	     	    
	for(count=0;count<16;count++)//����16λ����,ֻ�и�12λ��Ч 
	{ 				  
		Num<<=1; 	 
		digitalWrite(tp_dev.sck,LOW);	//�½�����Ч  	    	   
		delay_us(1);    
 		digitalWrite(tp_dev.sck,HIGH);
 		if(digitalRead(tp_dev.miso))Num++; 		 
	}  	
	Num>>=4;   	//ֻ�и�12λ��Ч.
	digitalWrite(tp_dev.cs,HIGH);		//�ͷ�Ƭѡ	 
	return(Num);   
}

//��ȡһ������ֵ(x����y)
//������ȡREAD_TIMES������,����Щ������������,
//Ȼ��ȥ����ͺ����LOST_VAL����,ȡƽ��ֵ 
//xy:ָ�CMD_RDX/CMD_RDY��
//����ֵ:����������
#define READ_TIMES 5 	//��ȡ����
#define LOST_VAL 1	  	//����ֵ
uint16_t TP_Read_XOY(uint8_t xy)
{
	uint16_t i, j;
	uint16_t buf[READ_TIMES];
	uint16_t sum=0;
	uint16_t temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);		 		    
	for(i=0;i<READ_TIMES-1; i++)//����
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 
//��ȡx,y����
//��Сֵ��������100.
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
uint8_t TP_Read_XY(uint16_t *x,uint16_t *y)
{
	uint16_t xtemp,ytemp;			 	 		  
	xtemp=TP_Read_XOY(tp_dev.CMD_RDX);
	ytemp=TP_Read_XOY(tp_dev.CMD_RDY);	  												   
	//if(xtemp<100||ytemp<100)return 0;//����ʧ��
	*x=xtemp;
	*y=ytemp;
	return 1;//�����ɹ�
}

//����2�ζ�ȡ������IC,�������ε�ƫ��ܳ���
//ERR_RANGE,��������,����Ϊ������ȷ,�����������.	   
//�ú����ܴ�����׼ȷ��
//x,y:��ȡ��������ֵ
//����ֵ:0,ʧ��;1,�ɹ���
#define ERR_RANGE 50 //��Χ 
uint8_t TP_Read_XY2(uint16_t *x,uint16_t *y) 
{
	uint16_t x1,y1;
 	uint16_t x2,y2;
 	uint8_t flag;    
    flag=TP_Read_XY(&x1,&y1);   
    if(flag==0)return(0);
    flag=TP_Read_XY(&x2,&y2);	   
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//ǰ�����β�����+-50��
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;	  
}

#if 0
//////////////////////////////////////////////////////////////////////////////////		  
//��LCD�����йصĺ���  
//��һ��������
//����У׼�õ�
//x,y:����
//color:��ɫ

//��һ�����(2*2�ĵ�)		   
//x,y:����
//color:��ɫ
void TP_Draw_Big_Point(uint16_t x,uint16_t y,uint16_t color)
{	    
	POINT_COLOR=color;
	LCD_DrawPoint(x,y);//���ĵ� 
	LCD_DrawPoint(x+1,y);
	LCD_DrawPoint(x,y+1);
	LCD_DrawPoint(x+1,y+1);	 	  	
}
#endif		
//////////////////////////////////////////////////////////////////////////////////		  
//��������ɨ��
//tp:0,��Ļ����;1,��������(У׼�����ⳡ����)
//����ֵ:��ǰ����״̬.

uint8_t TP_Scan(uint8_t tp)
{
    uint16_t x,y;
	float x1,y1;
	TP_Read_XY2(&x,&y);//��ȡ��������
	if((x>100)&&(y>100)){
		tp_dev.x[0]=x;
		tp_dev.y[0]=y;
		if(tp){
			return 1;
	    }else {
		  x1 = (float)((tp_dev.x[0]*tp_dev.xfac)-tp_dev.xoff);
		  y1 = (float)((tp_dev.y[0]*tp_dev.yfac)-tp_dev.yoff);
	      tp_dev.x[0]=(int16_t)x1;                 //�����ת��Ϊ��Ļ����
	      tp_dev.y[0]=(int16_t)y1;  
		  return 1;
	    } 
	}else{
		return 0;
	}			   
}
/*
uint8_t TP_Scan(uint8_t tp)
{			   
	int32_t x1,y1;
	if(digitalRead(tp_dev.irq)==0)//�а�������
	{
		if(tp)TP_Read_XY2(&tp_dev.x[0],&tp_dev.y[0]);//��ȡ��������
		else if(TP_Read_XY2(&tp_dev.x[0],&tp_dev.y[0]))//��ȡ��Ļ����
		{
		  x1 = (int32_t)(((tp_dev.x[0]-tp_dev.xoff)*tp_dev.xfac)/1000+10);
		  y1 = (int32_t)(((tp_dev.y[0]-tp_dev.yoff)*tp_dev.yfac)/1000+10);
	      tp_dev.x[0]=x1;                 //�����ת��Ϊ��Ļ����
	      tp_dev.y[0]=y1;  
	 	} 
		return 1
	}
	return 0;	
}	  
*/
//////////////////////////////////////////////////////////////////////////	 
//������EEPROM����ĵ�ַ�����ַ,ռ��13���ֽ�(RANGE:SAVE_ADDR_BASE~SAVE_ADDR_BASE+12)
#define SAVE_ADDR_BASE 40
//����У׼����										    
#if 0
void TP_Save_Adjdata(void)
{
	int32 temp;			 
	//����У�����!
	temp=tp_dev.xfac*100000000;//����xУ������      
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE,temp,4);   
	temp=tp_dev.yfac*100000000;//����yУ������    
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE+4,temp,4);
	//����xƫ����
    AT24CXX_WriteLenByte(SAVE_ADDR_BASE+8,tp_dev.xoff,2);		    
	//����yƫ����
	AT24CXX_WriteLenByte(SAVE_ADDR_BASE+10,tp_dev.yoff,2);	
	//���津������
	AT24CXX_WriteOneByte(SAVE_ADDR_BASE+12,tp_dev.touchtype);	
	temp=0X0A;//���У׼����
	AT24CXX_WriteOneByte(SAVE_ADDR_BASE+13,temp); 
}

//�õ�������EEPROM�����У׼ֵ
//����ֵ��1���ɹ���ȡ����
//        0����ȡʧ�ܣ�Ҫ����У׼
uint8_t TP_Get_Adjdata(void)
{					  
	s32 tempfac;
	tempfac=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+13);//��ȡ�����,���Ƿ�У׼���� 		 
	if(tempfac==0X0A)//�������Ѿ�У׼����			   
	{    												 
		tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE,4);		   
		tp_dev.xfac=(float)tempfac/100000000;//�õ�xУ׼����
		tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+4,4);			          
		tp_dev.yfac=(float)tempfac/100000000;//�õ�yУ׼����
	    //�õ�xƫ����
		tp_dev.xoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+8,2);			   	  
 	    //�õ�yƫ����
		tp_dev.yoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+10,2);				 	  
 		tp_dev.touchtype=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+12);//��ȡ�������ͱ��
		if(tp_dev.touchtype)//X,Y��������Ļ�෴
		{
			tp_dev.CMD_RDX=0X90;
			tp_dev.CMD_RDY=0XD0;	 
		}else				   //X,Y��������Ļ��ͬ
		{
			tp_dev.CMD_RDX=0XD0;
			tp_dev.CMD_RDY=0X90;	 
		}		 
		return 1;	 
	}
	return 0;
}	 

//��ʾ�ַ���
const uint8_t* TP_REMIND_MSG_TBL="Please use the stylus click the cross on the screen.The cross will always move until the screen adjustment is completed.";
 					  
//��ʾУ׼���(��������)
void TP_Adj_Info_Show(uint16_t x0,uint16_t y0,uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint16_t x3,uint16_t y3,uint16_t fac)
{	  
	POINT_COLOR=RED;
	LCD_ShowString(40,160,lcddev.width,lcddev.height,16,"x1:");
 	LCD_ShowString(40+80,160,lcddev.width,lcddev.height,16,"y1:");
 	LCD_ShowString(40,180,lcddev.width,lcddev.height,16,"x2:");
 	LCD_ShowString(40+80,180,lcddev.width,lcddev.height,16,"y2:");
	LCD_ShowString(40,200,lcddev.width,lcddev.height,16,"x3:");
 	LCD_ShowString(40+80,200,lcddev.width,lcddev.height,16,"y3:");
	LCD_ShowString(40,220,lcddev.width,lcddev.height,16,"x4:");
 	LCD_ShowString(40+80,220,lcddev.width,lcddev.height,16,"y4:");  
 	LCD_ShowString(40,240,lcddev.width,lcddev.height,16,"fac is:");     
	LCD_ShowNum(40+24,160,x0,4,16);		//��ʾ��ֵ
	LCD_ShowNum(40+24+80,160,y0,4,16);	//��ʾ��ֵ
	LCD_ShowNum(40+24,180,x1,4,16);		//��ʾ��ֵ
	LCD_ShowNum(40+24+80,180,y1,4,16);	//��ʾ��ֵ
	LCD_ShowNum(40+24,200,x2,4,16);		//��ʾ��ֵ
	LCD_ShowNum(40+24+80,200,y2,4,16);	//��ʾ��ֵ
	LCD_ShowNum(40+24,220,x3,4,16);		//��ʾ��ֵ
	LCD_ShowNum(40+24+80,220,y3,4,16);	//��ʾ��ֵ
 	LCD_ShowNum(40+56,lcddev.width,fac,3,16); 	//��ʾ��ֵ,����ֵ������95~105��Χ֮��.
}

//������У׼����
//�õ��ĸ�У׼����
void TP_Adjust(void)
{								 
	uint16_t pos_temp[4][2];//���껺��ֵ
	uint8_t  cnt=0;	
	uint16_t d1,d2;
	uint32_t tem1,tem2;
	double fac; 	
	uint16_t outtime=0;
 	cnt=0;				
	POINT_COLOR=BLUE;
	BACK_COLOR =WHITE;
	LCD_Clear(WHITE);//����   
	POINT_COLOR=RED;//��ɫ 
	LCD_Clear(WHITE);//���� 	   
	POINT_COLOR=BLACK;
	LCD_ShowString(40,40,160,100,16,(uint8_t*)TP_REMIND_MSG_TBL);//��ʾ��ʾ��Ϣ
	TP_Drow_Touch_Point(20,20,RED);//����1 
	tp_dev.sta=0;//���������ź� 
	tp_dev.xfac=0;//xfac��������Ƿ�У׼��,����У׼֮ǰ�������!�������	 
	while(1)//�������10����û�а���,���Զ��˳�
	{
		tp_dev.scan(1);//ɨ����������
		if((tp_dev.sta&0xc0)==TP_CATH_PRES)//����������һ��(��ʱ�����ɿ���.)
		{	
			outtime=0;		
			tp_dev.sta&=~(1<<6);//��ǰ����Ѿ����������.
						   			   
			pos_temp[cnt][0]=tp_dev.x[0];
			pos_temp[cnt][1]=tp_dev.y[0];
			cnt++;	  
			switch(cnt)
			{			   
				case 1:						 
					TP_Drow_Touch_Point(20,20,WHITE);				//�����1 
					TP_Drow_Touch_Point(lcddev.width-20,20,RED);	//����2
					break;
				case 2:
 					TP_Drow_Touch_Point(lcddev.width-20,20,WHITE);	//�����2
					TP_Drow_Touch_Point(20,lcddev.height-20,RED);	//����3
					break;
				case 3:
 					TP_Drow_Touch_Point(20,lcddev.height-20,WHITE);			//�����3
 					TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,RED);	//����4
					break;
				case 4:	 //ȫ���ĸ����Ѿ��õ�
	    		    //�Ա����
					tem1=abs(pos_temp[0][0]-pos_temp[1][0]);//x1-x2
					tem2=abs(pos_temp[0][1]-pos_temp[1][1]);//y1-y2
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//�õ�1,2�ľ���
					
					tem1=abs(pos_temp[2][0]-pos_temp[3][0]);//x3-x4
					tem2=abs(pos_temp[2][1]-pos_temp[3][1]);//y3-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//�õ�3,4�ľ���
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05||d1==0||d2==0)//���ϸ�
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//�����4
   	 					TP_Drow_Touch_Point(20,20,RED);								//����1
 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����   
 						continue;
					}
					tem1=abs(pos_temp[0][0]-pos_temp[2][0]);//x1-x3
					tem2=abs(pos_temp[0][1]-pos_temp[2][1]);//y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//�õ�1,3�ľ���
					
					tem1=abs(pos_temp[1][0]-pos_temp[3][0]);//x2-x4
					tem2=abs(pos_temp[1][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//�õ�2,4�ľ���
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//���ϸ�
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//�����4
   	 					TP_Drow_Touch_Point(20,20,RED);								//����1
 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����   
						continue;
					}//��ȷ��
								   
					//�Խ������
					tem1=abs(pos_temp[1][0]-pos_temp[2][0]);//x1-x3
					tem2=abs(pos_temp[1][1]-pos_temp[2][1]);//y1-y3
					tem1*=tem1;
					tem2*=tem2;
					d1=sqrt(tem1+tem2);//�õ�1,4�ľ���
	
					tem1=abs(pos_temp[0][0]-pos_temp[3][0]);//x2-x4
					tem2=abs(pos_temp[0][1]-pos_temp[3][1]);//y2-y4
					tem1*=tem1;
					tem2*=tem2;
					d2=sqrt(tem1+tem2);//�õ�2,3�ľ���
					fac=(float)d1/d2;
					if(fac<0.95||fac>1.05)//���ϸ�
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//�����4
   	 					TP_Drow_Touch_Point(20,20,RED);								//����1
 						TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����   
						continue;
					}//��ȷ��
					//������
					tp_dev.xfac=(float)(lcddev.width-40)/(pos_temp[1][0]-pos_temp[0][0]);//�õ�xfac		 
					tp_dev.xoff=(lcddev.width-tp_dev.xfac*(pos_temp[1][0]+pos_temp[0][0]))/2;//�õ�xoff
						  
					tp_dev.yfac=(float)(lcddev.height-40)/(pos_temp[2][1]-pos_temp[0][1]);//�õ�yfac
					tp_dev.yoff=(lcddev.height-tp_dev.yfac*(pos_temp[2][1]+pos_temp[0][1]))/2;//�õ�yoff  
					if(abs(tp_dev.xfac)>2||abs(tp_dev.yfac)>2)//������Ԥ����෴��.
					{
						cnt=0;
 				    	TP_Drow_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);	//�����4
   	 					TP_Drow_Touch_Point(20,20,RED);								//����1
						LCD_ShowString(40,26,lcddev.width,lcddev.height,16,"TP Need readjust!");
						tp_dev.touchtype=!tp_dev.touchtype;//�޸Ĵ�������.
						if(tp_dev.touchtype)//X,Y��������Ļ�෴
						{
							tp_dev.CMD_RDX=0X90;
							tp_dev.CMD_RDY=0XD0;	 
						}else				   //X,Y��������Ļ��ͬ
						{
							tp_dev.CMD_RDX=0XD0;
							tp_dev.CMD_RDY=0X90;	 
						}			    
						continue;
					}		
					POINT_COLOR=BLUE;
					LCD_Clear(WHITE);//����
					LCD_ShowString(35,110,lcddev.width,lcddev.height,16,"Touch Screen Adjust OK!");//У�����
					delay_ms(1000);
//					TP_Save_Adjdata();  
 					LCD_Clear(WHITE);//����   
					return;//У�����				 
			}
		}
		delay_ms(10);
		outtime++;
		if(outtime>1000)
		{
//			TP_Get_Adjdata();
			break;
	 	} 
 	}
}
#else
void TP_Adjust(void){};	
#endif

//��������ʼ��
//����ֵ:0,û�н���У׼
//		 1,���й�У׼
uint8_t TP_Init(void)
{
#if OTT_MAX_TOUCH	
	if(lcddev.id == 0X5510) //���ݴ�����
	{
		OTT2001A_Init();
		tp_dev.scan = CTP_Scan; //ɨ�躯��ָ����ݴ�����ɨ�躯��
		tp_dev.touchtype |= 0X80; //������
		tp_dev.touchtype |= lcddev.dir&0x01;//������������
		return 0;
	}else
#endif
	{ 
    pinMode(tp_dev.cs,OUTPUT);
	pinMode(tp_dev.sck,OUTPUT);	
    pinMode(tp_dev.miso,INPUT);
	pinMode(tp_dev.mosi,OUTPUT);
#ifdef 	TOUCH_NIRQ
	pinMode(tp_dev.irq,INPUT_PULLUP);	
#endif
#ifdef TOUCH_BUSY
	pinMode(TOUCH_BUSY,INPUT);	
#endif
	TP_Read_XY(&tp_dev.x[0],&tp_dev.y[0]); //��һ�ζ�ȡ��ʼ��
	TP_Read_XY(&tp_dev.x[0],&tp_dev.y[0]); //��һ�ζ�ȡ��ʼ��

//		AT24CXX_Init(); //��ʼ��24CXX
//		if(TP_Get_Adjdata())return 0; //�Ѿ�У׼��
//		else   //δУ׼����
//		{
//			LCD_Clear(BACK_COLOR); //����
//			TP_Adjust(); //��ĻУ׼
//			TP_Save_Adjdata(); //����У׼����
//		}
//		TP_Get_Adjdata(); //��ȡУ׼ֵ
    }
	return 1;
}
	
