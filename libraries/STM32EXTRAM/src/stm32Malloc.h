
#ifndef __STM32MALLOC_H__
#define __STM32MALLOC_H__

template<uint32_t BASEADR,uint32_t LENGTH,uint32_t  CELLLENGTH>
class MALLOCClass
{
  public:

    MALLOCClass() {
    }

    //释放内存(外部调用)
    //memx:所属内存块
    //ptr:内存首地址
	
    void free(void *ptr)
    {
      uint32_t offset;
      if (ptr == NULL) return; //地址为0.
      offset = (uint32_t)ptr - (uint32_t) membase;
      myMemFree(offset); //释放内存
    }
	
    //分配内存(外部调用)
    //memx:所属内存块
    //size:内存大小(字节)
    //返回值:分配到的内存首地址.
    template<typename T>
    T *malloc(uint32_t size)
    {
      uint32_t offset;
      offset = myMemMalloc(size);
      if (offset == 0XFFFFFFFF) 
		  return NULL;
      else 
		  return reinterpret_cast<T *>((uint32_t)membase + offset);
    }
	
    //重新分配内存(外部调用)
    //memx:所属内存块
    //*ptr:旧内存首地址
    //size:要分配的内存大小(字节)
    //返回值:新分配到的内存首地址.
    template<typename T>
    T *realloc(void *ptr, uint32_t size)
    {
      uint32_t offset = this->myMemMalloc(size);
      if (offset == 0XFFFFFFFF){
		  return NULL;
	  }
	  else
      {
        this->myMemCpy((void*)((uint32_t)membase + offset), ptr, size); //拷贝旧内存内容到新内存
        this->free(ptr);                            //释放旧内存
        return reinterpret_cast<T *>((uint32_t)membase + offset);        //返回新内存首地址
      }
    }

    //获取内存使用率
    //memx:所属内存块
    //返回值:使用率(0~100)
    uint8_t perused(void)
    {
      uint32_t used = 0;
      uint32_t i;
      for (i = 0; i < memtblsize; i++)
      {
        if (memmap[i])  used++;
      }
      return (used * 100) / memtblsize;
    }

    void deInit(void)
    {
      myMemIinit(SRAMEX);
      myMemIinit(SRAMCCM);
    }
	
	void setBank(uint8_t bank){
	  imemx = bank;
	}

  private:

//  struct _m_mallco_dev mallco_dev =
//   {
//	  { (uint16_t *)((uint32_t)MEM1_MAPBASE),
//	    (uint16_t *)((uint32_t)MEM0_MAPBASE),
//	  }, //内存管理状态表
//      {
//		(uint8_t *)((uint32_t)MEM1_BASE), 
//		(uint8_t *)((uint32_t)MEM0_BASE),
//	  },   //内存池
//	  {0, 0},              //内存管理未就绪
//    };

 	uint16_t* memmap; 				//内存管理状态表
	uint8_t*  membase ;				//内存池 管理SRAMBANK个区域的内存
	uint8_t  memrdy = 0; 		    //内存管理是否就绪
   
    uint8_t imemx =1;

    STM32EXTRAM(void) { 
    };

    const uint32_t memtblsize = MEM0_ALLOC_TABLE_SIZE; //内存表大小
    const uint32_t memblksize = MEM0_BLOCK_SIZE;       //内存分块大小
    const uint32_t memsize    = MEM0_MAX_SIZE;          //内存总大小


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
    void myMemIinit(void)
    {
      myMemSet(memmap,  0, memtblsize * 2); //内存状态表数据清零
      myMemSet(membase, 0, memsize);   //内存池所有数据清零
      memrdy = 1;                //内存管理初始化OK
    }
	
    //内存分配(内部调用)
    //memx:所属内存块
    //size:要分配的内存大小(字节)
    //返回值:0XFFFFFFFF,代表错误;其他,内存偏移地址
	
    uint32_t myMemMalloc(uint32_t size)
    {
      signed long offset = 0;
      uint32_t nmemb; //需要的内存块数
      uint32_t cmemb = 0; //连续空内存块数
      uint32_t i;
      if (!memrdy) myMemIinit(); //未初始化,先执行初始化
      if (size == 0) return 0XFFFFFFFF; //不需要分配
      nmemb = size / memblksize; //获取需要分配的连续内存块数
      if (size % memblksize)nmemb++;
      for (offset = memtblsize - 1; offset >= 0; offset--) //搜索整个内存控制区
      {
        if (memmap[offset])cmemb++; //连续空内存块数增加
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

#endif /* __STM3210E_EVAL_SRAM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

