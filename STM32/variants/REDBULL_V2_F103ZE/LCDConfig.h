/*******************Copyright (c)****************************************                         
**--------------File Info------------------------------------------------
** File name:			LCDConfig.h   for emWin & uCGUI
** Descriptions:		LCD Configuration
**------------------------------------------------------------------------
** Modified by:			huaweiwx@sina.com
** Modified date:	    2017-08-02
** Version:             17.8.2
** Descriptions:		for arduino halmx
**************************************************************************/

#ifndef __LCDCONFIG_H__
#define __LCDCONFIG_H__

//我有两个屏 9320/9486 选择一个
//#define BSP_TFT_LCD        0x9320		//指定LCD型号 ILI9320
#define BSP_TFT_LCD        0x9486		//指定LCD型号 ILI9486

#define LCD_CONTROLLER     (BSP_TFT_LCD)
#define LCD_BITSPERPIXEL   (16)
#define LCD_FIXEDPALETTE   (565)
#define LCD_SWAP_RB        (1)
#define LCD_SWAP_XY        (0)

#if BSP_TFT_LCD == 0x9486
#define LCD_XSIZE          (480)
#define LCD_YSIZE          (320)
#else									//9320	
#define LCD_XSIZE          (320)
#define LCD_YSIZE          (240)
#endif

#endif
/*************************************************************************
      END FILE
**************************************************************************/

