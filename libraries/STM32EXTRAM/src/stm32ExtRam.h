#ifndef __STM32EXTSRAM_H
#define __STM32EXTSRAM_H

#include <Arduino.h>
#if __has_include("bsp.h")
#include "bsp.h"
#endif

//定义内存池
  #define SRAMEX     0
  
//mem0 内存参数设定.mem0处于CCM,用于管理CCM(特别注意,这部分SRAM,仅CPU可以访问!!)
#ifdef CCMDATARAM_BASE
# define MEM1_MAPBASE            CCMDATARAM_BASE                    /*ccram maptable set at sram start*/
# define MEM1_BLOCK_SIZE		 32  	  						    /* 内存块大小为32字节 */
# define MEM1_MAX_SIZE			 60 *1024  						    /* 最大管理内存60K */
# define MEM1_ALLOC_TABLE_SIZE	 (MEM1_MAX_SIZE/MEM1_BLOCK_SIZE) 	/* 内存表大小 */
# define MEM1_BASE               (MEM1_MAPBASE + MEM1_ALLOC_TABLE_SIZE*2)  /* ccram start addr*/
# define SRAMBANK 	 2	    //定义支持的SRAM块数.	
#else
# define SRAMBANK 	 1	    //定义支持的SRAM块数.	
#endif

#ifdef SDRAM_START
#define EXTRAM_START  SDRAM_START
#define EXTRAM_LENGTH SDRAM_LENGTH
#else
#define EXTRAM_START  SRAM_START
#define EXTRAM_LENGTH SRAM_LENGTH
#endif
#define EXTRAM_END   (EXTRAM_START+EXTRAM_LENGTH)

//mem1 内存参数设定, mem1的内存池处于 extram 里面
#define MEM0_MAX_SIZE			(EXTRAM_LENGTH)/32*30  				//  2/32 for alloc table size
#define MEM0_BLOCK_SIZE			32  	  						    //内存块大小为32字节
#define MEM0_ALLOC_TABLE_SIZE	((MEM0_MAX_SIZE)/MEM0_BLOCK_SIZE) 	//内存表大小

#define MEM0_MAPBASE  (EXTRAM_END - (MEM0_ALLOC_TABLE_SIZE)*2)
#define MEM0_BASE     (MEM0_MAPBASE - MEM0_MAX_SIZE)


  
		 






#if SDRAM_START
extern SDRAM_HandleTypeDef sdramHandle;
#elif SRAM_START
extern SRAM_HandleTypeDef  sramHandle;
#else
#error !!!undef SRAM_START or SDRAM_START!!!
#endif

extern "C" void setHeap(unsigned char* s, unsigned char* e);

//内存管理控制器
struct _m_mallco_dev
{
//	void    (*init)(uint8_t);					//初始化
//	uint8_t (*perused)(uint8_t);		  	    //内存使用率
	uint16_t* memmap[SRAMBANK]; 				//内存管理状态表
	uint8_t*  membase[SRAMBANK];				//内存池 管理SRAMBANK个区域的内存
	uint8_t   memrdy[SRAMBANK]; 				//内存管理是否就绪
};

typedef enum
{
	EXTRAM = 0,		//外部内存池
#ifdef CCMDATARAM_BASE
    CCMRAM = 1,     //CCM内存池(此部分SRAM仅仅CPU可以访问!!!)
#endif	
} BANK_EmuType;

class STM32EXTRAM
{
  public:

    static STM32EXTRAM& getInstance() {
      static STM32EXTRAM instance; // Guaranteed to be destroyed. Instantiated on first use.
      return instance;
    }

    STM32EXTRAM(STM32EXTRAM const&)        = delete;
    void operator=(STM32EXTRAM const&)  = delete;

    inline uint8_t readData( uint32_t uwStartAddress, uint8_t *pData, uint32_t uwDataSize) {
#ifdef SDRAM_START
      return HAL_SDRAM_Read_8b(&sdramHandle, (uint32_t *)(uwStartAddress + SDRAM_START), pData, uwDataSize);
#else
      return HAL_SRAM_Read_8b(&sramHandle, (uint32_t *)(uwStartAddress + SRAM_START), pData, uwDataSize);
#endif
    };
    inline uint8_t readData( uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize) {
#ifdef SDRAM_START
      return HAL_SDRAM_Read_16b(&sdramHandle, (uint32_t *)(uwStartAddress + SDRAM_START), pData, uwDataSize);
#else
      return HAL_SRAM_Read_16b(&sramHandle, (uint32_t *)(uwStartAddress + SRAM_START), pData, uwDataSize);
#endif
    };
    inline uint8_t readData( uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize) {
#ifdef SDRAM_START
      return HAL_SDRAM_Read_32b(&sdramHandle, (uint32_t *)(uwStartAddress + SDRAM_START), pData, uwDataSize);
#else
      return HAL_SRAM_Read_32b(&sramHandle, (uint32_t *)(uwStartAddress + SRAM_START), pData, uwDataSize);
#endif
    };
    inline uint8_t writeData(uint32_t uwStartAddress, uint8_t *pData, uint32_t uwDataSize) {
#ifdef SDRAM_START
      return HAL_SDRAM_Write_8b(&sdramHandle, (uint32_t *)(uwStartAddress + SDRAM_START), pData, uwDataSize);
#else
      return HAL_SRAM_Write_8b(&sramHandle, (uint32_t *)(uwStartAddress + SRAM_START), pData, uwDataSize);
#endif
    };
    inline uint8_t writeData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize) {
#ifdef SDRAM_START
      return HAL_SDRAM_Write_16b(&sdramHandle, (uint32_t *)(uwStartAddress + SDRAM_START), pData, uwDataSize);
#else
      return HAL_SRAM_Write_16b(&sramHandle, (uint32_t *)(uwStartAddress + SRAM_START), pData, uwDataSize);
#endif
    };

    inline uint8_t writeData(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize) {
#ifdef SDRAM_START
      return HAL_SDRAM_Write_32b(&sdramHandle, (uint32_t *)(uwStartAddress + SDRAM_START), pData, uwDataSize);
#else
      return HAL_SRAM_Write_32b(&sramHandle, (uint32_t *)(uwStartAddress + SRAM_START), pData, uwDataSize);
#endif
    };

    template<typename T>
    T *getRamBaseAddress() {
#ifdef SDRAM_START
      return reinterpret_cast<T *>(SDRAM_START);
#else
      return reinterpret_cast<T *>(SRAM_START);
#endif
    }

    inline uint32_t getRamByteLength() {
#ifdef SDRAM_START
      return SDRAM_LENGTH;
#else
      return SRAM_LENGTH;
#endif
    }

    inline void setHeapAtExtRam(void) {
#ifdef SDRAM_START
      setHeap((unsigned char*)SDRAM_START, (unsigned char*)SDRAM_START + SDRAM_LENGTH);
#else
      setHeap((unsigned char*)SRAM_START, (unsigned char*)SRAM_START + SRAM_LENGTH);
#endif
    }

    inline void setHeapAtExtRam(uint32_t s, uint32_t e) {
      setHeap((unsigned char*)s, (unsigned char*)e);
    }

	
//释放内存(外部调用)
//memx:所属内存块
//ptr:内存首地址
    inline void free(void *ptr)
    {
      free(ptr,imemx);   //释放内存
    }

    void free(void *ptr,uint8_t memx)
    {
      uint32_t offset;
      if (ptr == NULL)return; //地址为0.
      offset = (uint32_t)ptr - (uint32_t)mallco_dev.membase[memx];
      myMemFree(memx, offset); //释放内存
    }
	
//分配内存(外部调用)
//memx:所属内存块
//size:内存大小(字节)
//返回值:分配到的内存首地址.
    template<typename T>
    T *malloc(uint32_t size)
    {
       return malloc<T>(size,imemx);
    }

    template<typename T>
    T *malloc(uint32_t size,uint8_t memx)
    {
      uint32_t offset;
      offset = myMemMalloc(memx, size * sizeof(T));
      if (offset == 0XFFFFFFFF) 
		  return NULL;
      else 
		  return reinterpret_cast<T *>((uint32_t)mallco_dev.membase[memx] + offset);
    }
	
//重新分配内存(外部调用)
//memx:所属内存块
//*ptr:旧内存首地址
//size:要分配的内存大小(字节)
//返回值:新分配到的内存首地址.
    template<typename T>
    T *realloc(void *ptr, uint32_t size)
    {
      return  realloc<T>(ptr, size, imemx);
    }
	
    template<typename T>
    T *realloc(void *ptr, uint32_t size,uint8_t memx)
    {
      uint32_t offset = this->myMemMalloc(memx, size* sizeof(T));
      if (offset == 0XFFFFFFFF){
		  return NULL;
	  }
	  else
      {
        this->myMemCpy((void*)((uint32_t)mallco_dev.membase[memx] + offset), ptr, size* sizeof(T)); //拷贝旧内存内容到新内存
        this->free(ptr,memx);                            //释放旧内存
        return reinterpret_cast<T *>((uint32_t)mallco_dev.membase[memx] + offset);        //返回新内存首地址
      }
    }

//获取内存使用率
//memx:所属内存块
//返回值:使用率(0~100)
    uint8_t perused(void){
		return this->perused(imemx);
	}
	
    uint8_t perused(uint8_t memx)
    {
      uint32_t used = 0;
      uint32_t i;
      for (i = 0; i < memtblsize[memx]; i++)
      {
        if (mallco_dev.memmap[memx][i]) used++;
      }
      return (used * 100) / (memtblsize[memx]);
    }

    void deInit(void)
    {
      myMemIinit(EXTRAM);
#ifdef CCMDATARAM_BASE	  
      myMemIinit(CCMRAM);
#endif	  
    }
	
	void setBank(BANK_EmuType bank){
	  imemx = bank;
	}

  private:
/*malloc*/
    struct _m_mallco_dev mallco_dev =
    {
	  { (uint16_t *)((uint32_t)MEM0_MAPBASE),
#ifdef CCMDATARAM_BASE	  
	    (uint16_t *)((uint32_t)MEM1_MAPBASE),
#endif
	  }, //内存管理状态表
      {
		(uint8_t *)((uint32_t)MEM0_BASE), 
#ifdef CCMDATARAM_BASE	  
		(uint8_t *)((uint32_t)MEM1_BASE),
#endif	  
	  },   //内存池
#ifdef CCMDATARAM_BASE	  
	  {0, 0},              //内存管理未就绪
#else
      {0},
#endif	
    };
    
    uint8_t imemx = 0;

    STM32EXTRAM(void) { 
    };
	
#ifdef CCMDATARAM_BASE	  
    const uint32_t memtblsize[SRAMBANK] = {MEM0_ALLOC_TABLE_SIZE, MEM1_ALLOC_TABLE_SIZE}; //内存表大小
    const uint32_t memblksize[SRAMBANK] = {MEM0_BLOCK_SIZE, MEM1_BLOCK_SIZE};             //内存分块大小
    const uint32_t memsize[SRAMBANK]    = {MEM0_MAX_SIZE, MEM1_MAX_SIZE};                 //内存总大小
#else
    const uint32_t memtblsize[SRAMBANK] = {MEM0_ALLOC_TABLE_SIZE};
    const uint32_t memblksize[SRAMBANK] = {MEM0_BLOCK_SIZE};
    const uint32_t memsize[SRAMBANK]    = {MEM0_MAX_SIZE};
#endif

//复制内存
//*des:目的地址
//*src:源地址
//n:需要复制的内存长度(字节为单位)
    void myMemCpy(void *des,void *src,uint32_t n)  
    {  
        uint8_t *xdes = (uint8_t*)des;
    	uint8_t *xsrc = (uint8_t*)src; 
        while(n--) *xdes++ = *xsrc++;  
    }  

//设置内存
//*s:内存首地址
//c :要设置的值
//count:需要设置的内存大小(字节为单位)
    void myMemSet(void *s,uint8_t c,uint32_t count)  
    {  
        uint8_t *xs = (uint8_t *)s;  
        while(count--)*xs++=c;  
    }	   

//内存管理初始化
//memx:所属内存块
    void myMemIinit(uint8_t memx)
    {
      myMemSet(mallco_dev.memmap[memx],  0, memtblsize[memx] * 2); //内存状态表数据清零
      myMemSet(mallco_dev.membase[memx], 0, memsize[memx]);   //内存池所有数据清零
      mallco_dev.memrdy[memx] = 1;                //内存管理初始化OK
    }
	
//内存分配(内部调用)
//memx:所属内存块
//size:要分配的内存大小(字节)
//返回值:0XFFFFFFFF,代表错误;其他,内存偏移地址
    uint32_t myMemMalloc(uint8_t memx, uint32_t size)
    {
      signed long offset = 0;
      uint32_t nmemb; //需要的内存块数
      uint32_t cmemb = 0; //连续空内存块数
      uint32_t i;
      if (!mallco_dev.memrdy[memx]) myMemIinit(memx); //未初始化,先执行初始化
      if (size == 0) return 0XFFFFFFFF; //不需要分配
      nmemb = size / memblksize[memx]; //获取需要分配的连续内存块数
      if (size % memblksize[memx])nmemb++;
      for (offset = memtblsize[memx] - 1; offset >= 0; offset--) //搜索整个内存控制区
      {
        if (!mallco_dev.memmap[memx][offset])cmemb++; //连续空内存块数增加
        else cmemb = 0;             //连续内存块清零
        if (cmemb == nmemb)           //找到了连续nmemb个空内存块
        {
          for (i = 0; i < nmemb; i++)     //标注内存块非空
          {
            mallco_dev.memmap[memx][offset + i] = nmemb;
          }
          return (offset * memblksize[memx]); //返回偏移地址
        }
      }
      return 0XFFFFFFFF;//未找到符合分配条件的内存块
    }

//释放内存(内部调用)
//memx:所属内存块
//offset:内存地址偏移
//返回值:0,释放成功;1,释放失败;
    uint8_t myMemFree(uint8_t memx, uint32_t offset)
    {
      int i;
      if (!mallco_dev.memrdy[memx]) //未初始化,先执行初始化
      {
        myMemIinit(memx);
        return 1;//未初始化
      }
      if (offset < memsize[memx]) //偏移在内存池内.
      {
        int index = offset / memblksize[memx];  //偏移所在内存块号码
        int nmemb = mallco_dev.memmap[memx][index]; //内存块数量
        for (i = 0; i < nmemb; i++)       //内存块清零
        {
          mallco_dev.memmap[memx][index + i] = 0;
        }
        return 0;
      } else return 2;//偏移超区了.
    }

};

#endif /* __STM32EXTRAM_H */

