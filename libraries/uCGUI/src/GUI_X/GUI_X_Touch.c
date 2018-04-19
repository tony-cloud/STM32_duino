/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUI_TOUCH_X.C
Purpose     : Config / System dependent externals for GUI
---------------------------END-OF-HEADER------------------------------
*/
#include 	"Arduino.h"
#include 	"inc/GUI.h"
#include	"inc/GUI_X.h"
#include	<BSP_Touch.h>

void GUI_TOUCH_X_ActivateX(void) {

}

void GUI_TOUCH_X_ActivateY(void) {
}

int  GUI_TOUCH_X_MeasureX(void) {

 // u16 x,y;
  tp_dev.scan(0);
  return tp_dev.x[0];
}

int  GUI_TOUCH_X_MeasureY(void) {
 // u16 x,y;
	tp_dev.scan(0);
    return tp_dev.y[0];
}


