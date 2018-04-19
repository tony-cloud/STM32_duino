#ifndef GUICONF_H
#define GUICONF_H

#define GUI_NUM_LAYERS            10   // ��ʾ��������

#if __has_include(<FreeRTOS.h>)   
#define GUI_OS                    (1)  // ʹ�ò���ϵͳ
#else
#define GUI_OS                    (0)  // ʹ�ò���ϵͳ
#endif

#define GUI_SUPPORT_TOUCH         (1)  // ֧�ִ���

#define GUI_DEFAULT_FONT          &GUI_Font6x8	//Ĭ������
#define GUI_SUPPORT_MOUSE             (1)    	//֧�����
#define GUI_WINSUPPORT                (1)    	//���ڹ���
#define GUI_SUPPORT_MEMDEV            (1)    	//�洢�豸
#define GUI_SUPPORT_DEVICES           (1)    	//ʹ���豸ָ��
#endif  
