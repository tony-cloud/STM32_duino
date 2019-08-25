/*
   JlinkRTT.h  J-Link RTT Viewer Terminals for Arduino by huaweiwx@sina.com 2018.11.25
*/

#ifndef JLINK_RTT_H
#define JLINK_RTT_H

#include "Arduino.h"
#include "SEGGER_RTT.h"



#ifdef __cplusplus

#include "Stream.h"

/*********************************************************************
*       RTT "Terminal" class
*********************************************************************/
class JLINKRTT:public Stream {
public:
    JLINKRTT(){
      SEGGER_RTT_Init();  //可以不使用该函数
      SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
	}
	
    void begin(uint32_t baud = 115200) {
      UNUSED(baud);
    }
    int available( void ) {
      return SEGGER_RTT_HasKey();
    }
	int read( void ) {
      uint8_t c= SEGGER_RTT_GetKey();
      return c;
    }
    unsigned  read(unsigned BufferIndex,void* pBuffer, unsigned BufferSize){
	  return SEGGER_RTT_Read( BufferIndex,pBuffer, BufferSize);
    }
    int availableForWrite(void) {
      return 1;
    }
    size_t write(const uint8_t ch ) {
	  SEGGER_RTT_Write(0, &ch, 1);
      return 1;
    }
    int peek(void ){
		return 1;
	}

    void flush( void ) {} ;

    int  setTerminal(char TerminalId){ return SEGGER_RTT_SetTerminal(TerminalId);}
    int  terminalOut(char TerminalId, const char* s){return SEGGER_RTT_TerminalOut(TerminalId, s);}

    using Print::write; // pull in write(str) and write(buf, size) from Print

    void end(void) {}

    operator bool() {
      return true;
    }; // RTT always active

/* 
int          SEGGER_RTT_AllocDownBuffer         (const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_AllocUpBuffer           (const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_ConfigUpBuffer          (unsigned BufferIndex, const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
int          SEGGER_RTT_ConfigDownBuffer        (unsigned BufferIndex, const char* sName, void* pBuffer, unsigned BufferSize, unsigned Flags);
unsigned     SEGGER_RTT_HasData                 (unsigned BufferIndex);
unsigned     SEGGER_RTT_ReadNoLock              (unsigned BufferIndex,       void* pData,   unsigned BufferSize);
int          SEGGER_RTT_SetNameDownBuffer       (unsigned BufferIndex, const char* sName);
int          SEGGER_RTT_SetNameUpBuffer         (unsigned BufferIndex, const char* sName);
int          SEGGER_RTT_SetFlagsDownBuffer      (unsigned BufferIndex, unsigned Flags);
int          SEGGER_RTT_SetFlagsUpBuffer        (unsigned BufferIndex, unsigned Flags);
int          SEGGER_RTT_WaitKey                 (void);
unsigned     SEGGER_RTT_WriteNoLock             (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteSkipNoLock         (unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
unsigned     SEGGER_RTT_WriteString             (unsigned BufferIndex, const char* s);
void         SEGGER_RTT_WriteWithOverwriteNoLock(unsigned BufferIndex, const void* pBuffer, unsigned NumBytes);
*/
};

extern JLINKRTT  jlinkRTT;

#endif


#endif

/*************************** End of file ****************************/
