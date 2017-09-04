/****************************************Copyright (c)**************************************************                         
**--------------File Info-------------------------------------------------------------------------------
** File name:			LCDConfig.h   for emWin & uCGUI
** Descriptions:		LCD Configuration
**
**------------------------------------------------------------------------------------------------------
** Modified by:			huaweiwx@sina.com
** Modified date:	    2017-08-02
** Version:             17.8.2
** Descriptions:		for arduino halmx
********************************************************************************************************/

#ifndef __LCDCONFIG_H__
#define __LCDCONFIG_H__

# define BSP_TFT_LCD       0x5420      //指定LCD型号 SPFD5420
#define LCD_XSIZE          (400)
#define LCD_YSIZE          (240)
#define LCD_CONTROLLER     (BSP_TFT_LCD)
#define LCD_BITSPERPIXEL   (16)
#define LCD_FIXEDPALETTE   (565)
#define LCD_SWAP_RB        (1)
#define LCD_SWAP_XY        (0)

#endif
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/

