#if __has_include("STemWin.h")
#include  <Arduino.h>
#include "STemWin/inc/GUI.h"
#include "Adafruit/stm32_adafruit_lcd.h"
#include "GUIDRV_Template.h"
#include "STemWin/inc/GUIDRV_FlexColor.h"

//�봥�����йض��壬����ʵ�������д
#define TOUCH_AD_TOP		160  	//���´������Ķ�����д�� Y ��ģ������ֵ��
#define TOUCH_AD_BOTTOM		3990 	//���´������ĵײ���д�� Y ��ģ������ֵ��
#define TOUCH_AD_LEFT 		160		//���´���������࣬д�� X ��ģ������ֵ��
#define TOUCH_AD_RIGHT		3990	//���´��������Ҳ࣬д�� X ��ģ������ֵ��


//��Ļ��С
#define XSIZE_PHYS  320 //X��
#define YSIZE_PHYS  240 //Y��
#define VXSIZE_PHYS	320 
#define VYSIZE_PHYS 240



//���ü��
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif

  

//���ó���,���ڴ�����ʾ��������,������ɫת���������ʾ�ߴ�
void LCD_X_Config(void) {
		LCD_SetSizeEx    (0, BSP_LCD_GetXSize, BSP_LCD_GetYSize);
		LCD_SetVSizeEx   (0, BSP_LCD_GetXSize, BSP_LCD_GetYSize);
//			GUI_TOUCH_SetOrientation(GUI_SWAP_XY|GUI_MIRROR_Y); 
		GUI_TOUCH_Calibrate(GUI_COORD_X,0,240,0,235); 		
		GUI_TOUCH_Calibrate(GUI_COORD_Y,0,320,0,319);
}

//��ʾ�������Ļص�����
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
  int r;
  (void) LayerIndex;
  (void) pData;
  
  switch (Cmd) {
  case LCD_X_INITCONTROLLER: {
	//����ʼ����ʱ�򱻵���,��Ҫ��������ʾ������,�����ʾ���������ⲿ��ʼ������Ҫ�û���ʼ��
		
//	BSP_LCD_Init(); //��ʼ��LCD �Ѿ��ڿ�ʼ��ʼ����,���Դ˴�����Ҫ��ʼ����

    return 0;
  }
		default:
    r = -1;
	}
  return r;
}

#endif
