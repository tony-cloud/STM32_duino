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
File        : LISTBOX.h
Purpose     : LISTBOX widget include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef LISTBOX_H
#define LISTBOX_H

#include "inc/WM.h"
#include "WIDGET.h"             /* Req. for WIDGET_DRAW_ITEM_FUNC */
#include "DIALOG_Intern.h"      /* Req. for Create indirect data structure */

#if GUI_WINSUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       defines
*
**********************************************************************
*/

#define LISTBOX_ALL_ITEMS  -1

/*********************************************************************
*
*       Color indices
*/
#define LISTBOX_CI_UNSEL    0
#define LISTBOX_CI_SEL      1
#define LISTBOX_CI_SELFOCUS 2

/************************************************************
*
*       States
*/
typedef WM_HMEM LISTBOX_Handle;

/*********************************************************************
*
*               Notification codes
*
* The following is the list of notification codes specific to this widget,
* Send with the WM_NOTIFY_PARENT message
*/
#define LISTBOX_NOTIFICATION_LOST_FOCUS    (WM_NOTIFICATION_WIDGET + 0)

/************************************************************
*
*       Create / Status flags
*/
#define LISTBOX_CF_AUTOSCROLLBAR_H   (1<<0)
#define LISTBOX_CF_AUTOSCROLLBAR_V   (1<<1)
#define LISTBOX_CF_MULTISEL          (1<<2)
#define LISTBOX_SF_AUTOSCROLLBAR_H   LISTBOX_CF_AUTOSCROLLBAR_H
#define LISTBOX_SF_AUTOSCROLLBAR_V   LISTBOX_CF_AUTOSCROLLBAR_V
#define LISTBOX_SF_MULTISEL          LISTBOX_CF_MULTISEL

/*********************************************************************
*
*       Standard member functions
*
**********************************************************************
*/

#define LISTBOX_EnableMemdev(hObj)  WM_EnableMemdev(hObj)
#define LISTBOX_DisableMemdev(hObj) WM_DisableMemdev(hObj)
#define LISTBOX_Delete(hObj)        WM_DeleteWindow(hObj)
#define LISTBOX_Paint(hObj)         WM_Paint(hObj)
#define LISTBOX_Invalidate(hObj)    WM_InvalidateWindow(hObj)

/*********************************************************************
*
*       Create functions
*
**********************************************************************
*/

LISTBOX_Handle LISTBOX_Create        (const GUI_ConstString* ppText, int x0, int y0, int xsize, int ysize, int Flags);
LISTBOX_Handle LISTBOX_CreateAsChild (const GUI_ConstString* ppText, WM_HWIN hWinParent, int x0, int y0, int xsize, int ysize, int Flags);
LISTBOX_Handle LISTBOX_CreateIndirect(const GUI_WIDGET_CREATE_INFO* pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK* cb);
LISTBOX_Handle LISTBOX_CreateEx      (int x0, int y0, int xsize, int ysize, WM_HWIN hParent,
                                      int WinFlags, int ExFlags, int Id, const GUI_ConstString* ppText);

/*********************************************************************
*
*       Member functions
*
**********************************************************************
*/

int          LISTBOX_AddKey          (LISTBOX_Handle hObj, int Key);
void         LISTBOX_AddString       (LISTBOX_Handle hObj, const char* s);
void         LISTBOX_DecSel          (LISTBOX_Handle hObj);
void         LISTBOX_DeleteItem      (LISTBOX_Handle hObj, unsigned int Index);
unsigned     LISTBOX_GetItemSpacing  (LISTBOX_Handle hObj);
unsigned     LISTBOX_GetNumItems     (LISTBOX_Handle hObj);
int          LISTBOX_GetSel          (LISTBOX_Handle hObj);
const GUI_FONT GUI_UNI_PTR * LISTBOX_GetFont    (LISTBOX_Handle hObj);
int          LISTBOX_GetItemDisabled (LISTBOX_Handle hObj, unsigned Index);
int          LISTBOX_GetItemSel      (LISTBOX_Handle hObj, unsigned Index);
void         LISTBOX_GetItemText     (LISTBOX_Handle hObj, unsigned Index, char * pBuffer, int MaxSize);
int          LISTBOX_GetMulti        (LISTBOX_Handle hObj);
int          LISTBOX_GetScrollStepH  (LISTBOX_Handle hObj);
void         LISTBOX_IncSel          (LISTBOX_Handle hObj);
void         LISTBOX_InsertString    (LISTBOX_Handle hObj, const char* s, unsigned int Index);
int          LISTBOX_OwnerDraw       (const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
void         LISTBOX_SetAutoScrollH  (LISTBOX_Handle hObj, int OnOff);
void         LISTBOX_SetAutoScrollV  (LISTBOX_Handle hObj, int OnOff);
void         LISTBOX_SetBkColor      (LISTBOX_Handle hObj, unsigned int Index, GUI_COLOR color);
void         LISTBOX_SetFont         (LISTBOX_Handle hObj, const GUI_FONT GUI_UNI_PTR * pFont);
void         LISTBOX_SetItemDisabled (LISTBOX_Handle hObj, unsigned Index, int OnOff);
void         LISTBOX_SetItemSel      (LISTBOX_Handle hObj, unsigned Index, int OnOff);
void         LISTBOX_SetItemSpacing  (LISTBOX_Handle hObj, unsigned Value);
void         LISTBOX_SetMulti        (LISTBOX_Handle hObj, int Mode);
void         LISTBOX_SetOwner        (LISTBOX_Handle hObj, WM_HWIN hOwner);
void         LISTBOX_SetOwnerDraw    (LISTBOX_Handle hObj, WIDGET_DRAW_ITEM_FUNC * pfDrawItem);
void         LISTBOX_SetScrollStepH  (LISTBOX_Handle hObj, int Value);
void         LISTBOX_SetSel          (LISTBOX_Handle hObj, int Sel);
void         LISTBOX_SetScrollbarWidth(LISTBOX_Handle hObj, unsigned Width);
void         LISTBOX_SetString       (LISTBOX_Handle hObj, const char* s, unsigned int Index);
void         LISTBOX_SetText         (LISTBOX_Handle hObj, const GUI_ConstString* ppText);
GUI_COLOR    LISTBOX_SetTextColor    (LISTBOX_Handle hObj, unsigned int Index, GUI_COLOR Color);
int          LISTBOX_UpdateScrollers (LISTBOX_Handle hObj);
void         LISTBOX_InvalidateItem  (LISTBOX_Handle hObj, int Index);

/*********************************************************************
*
*       Global functions
*
**********************************************************************
*/

const GUI_FONT GUI_UNI_PTR* LISTBOX_GetDefaultFont(void);
int         LISTBOX_GetDefaultScrollStepH (void);
GUI_COLOR   LISTBOX_GetDefaultBkColor     (unsigned Index);
GUI_COLOR   LISTBOX_GetDefaultTextColor   (unsigned Index);
void        LISTBOX_SetDefaultFont        (const GUI_FONT GUI_UNI_PTR * pFont);
void        LISTBOX_SetDefaultScrollStepH (int Value);
void        LISTBOX_SetDefaultBkColor     (unsigned Index, GUI_COLOR Color);
void        LISTBOX_SetDefaultTextColor   (unsigned Index, GUI_COLOR Color);

/*********************************************************************
*
*       Compatibility to older versions
*
**********************************************************************
*/

#define LISTBOX_SetBackColor(hObj, Index, Color) LISTBOX_SetBkColor(hObj, Index, Color)
#define LISTBOX_DeleteString  LISTBOX_DeleteItem

#if defined(__cplusplus)
  }
#endif

#endif   /* GUI_WINSUPPORT */
#endif   /* LISTBOX_H */