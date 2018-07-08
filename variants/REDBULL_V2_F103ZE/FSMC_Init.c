#include "bsp.h"
#ifdef __GNUC__
  #pragma GCC diagnostic ignored "-Wunused-variable"
#endif

void _Error_Handler(char* file, uint32_t line);
static uint32_t FSMC_Initialized = 0;
void STM_FSMC_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  if (FSMC_Initialized) return;
     FSMC_Initialized=1;
  /* Peripheral clock enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_FSMC_CLK_ENABLE();
  
  /** FSMC GPIO Configuration  
  PF0   ------> FSMC_A0
  PF1   ------> FSMC_A1
  PF2   ------> FSMC_A2
  PF3   ------> FSMC_A3
  PF4   ------> FSMC_A4
  PF5   ------> FSMC_A5
  PF12  ------> FSMC_A6
  PF13  ------> FSMC_A7
  PF14  ------> FSMC_A8
  PF15  ------> FSMC_A9
  PG0   ------> FSMC_A10
  PG1   ------> FSMC_A11
  PG2   ------> FSMC_A12
  PG3   ------> FSMC_A13
  PG4   ------> FSMC_A14
  PG5   ------> FSMC_A15
  PD11  ------> FSMC_A16 FSMC_CLE   //nand
  PD12  ------> FSMC_A17 FSMC_ALE   //nand
  PD13  ------> FSMC_A18
  PE3   ------> FSMC_A19
  PE4   ------> FSMC_A20
  PE5   ------> FSMC_A21
  PE6   ------> FSMC_A22
  PD14  ------> FSMC_D0
  PD15  ------> FSMC_D1
  PD0   ------> FSMC_D2
  PD1   ------> FSMC_D3
  PE7   ------> FSMC_D4
  PE8   ------> FSMC_D5
  PE9   ------> FSMC_D6
  PE10  ------> FSMC_D7
  PE11  ------> FSMC_D8
  PE12  ------> FSMC_D9
  PE13  ------> FSMC_D10
  PE14  ------> FSMC_D11
  PE15  ------> FSMC_D12
  PD8   ------> FSMC_D13
  PD9   ------> FSMC_D14
  PD10  ------> FSMC_D15
  PD4   ------> FSMC_NOE   //r 
  PD5   ------> FSMC_NWE   //w
  PD6   ------> FSMC_NWAIT //nor/nand
  PD7   ------> FSMC_NCE2  //nand 
  PG9   ------> FSMC_NE2   //nor
  PG10  ------> FSMC_NE3   //sram
  PG12  ------> FSMC_NE4   //lcd
  PE0   ------> FSMC_NBL0  //sram
  PE1   ------> FSMC_NBL1  //sram
  PG6  -------> FSMC_INT2  //nand op
  */
  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_0| GPIO_PIN_1| GPIO_PIN_2|GPIO_PIN_3| GPIO_PIN_4|GPIO_PIN_5
                      |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                       |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_12;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin =  GPIO_PIN_0|GPIO_PIN_1 |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
						 |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                         |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                         |GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_0| GPIO_PIN_1| GPIO_PIN_4| GPIO_PIN_5
                      | GPIO_PIN_7| GPIO_PIN_8| GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11 
                      |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  
    /*!< Configure PD6 for NOR memory Ready/Busy signal */
  GPIO_InitStruct.Pin  = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /*!< Configure PG6 for NAND INT signal */
  GPIO_InitStruct.Pin  = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

}

//lcd FSMC
SRAM_HandleTypeDef fsmcLcdHandle;
void STM_FSMC_LCD_TimeSet(uint8_t _as, uint8_t _ds)
{ 	
  FSMC_NORSRAM_TimingTypeDef Timing;

  STM_FSMC_GPIO_Init();
  /** Perform the SRAM4(LCD) initialization sequence
  */
  fsmcLcdHandle.Instance = FSMC_NORSRAM_DEVICE;
  fsmcLcdHandle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* fsmcLcdHandle.Init */
  fsmcLcdHandle.Init.NSBank = FSMC_NORSRAM_BANK4;
  fsmcLcdHandle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  fsmcLcdHandle.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  fsmcLcdHandle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  fsmcLcdHandle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  fsmcLcdHandle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  fsmcLcdHandle.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  fsmcLcdHandle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  fsmcLcdHandle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  fsmcLcdHandle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  fsmcLcdHandle.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  fsmcLcdHandle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  fsmcLcdHandle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
//  fsmcLcdHandle.Init.PageSize = FSMC_PAGE_SIZE_NONE;
  /* Timing */
  Timing.AddressSetupTime = _as/14;	//   1000/72(HCLK) =14ns
  Timing.AddressHoldTime =   1;
  Timing.DataSetupTime =    _ds/14;	//   1000/72(HCLK) =14ns
  Timing.BusTurnAroundDuration = 1;
  Timing.CLKDivision = 2;
  Timing.DataLatency = 2;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&fsmcLcdHandle, &Timing, NULL) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}

SRAM_HandleTypeDef sramHandle;
void STM_FSMC_SRAM_Init(void)
{ 	
  FSMC_NORSRAM_TimingTypeDef Timing;
  
  STM_FSMC_GPIO_Init();
  
   /** Perform the SRAM3 memory initialization sequence
  */
  sramHandle.Instance = FSMC_NORSRAM_DEVICE;
  sramHandle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* sramHandle.Init */
  sramHandle.Init.NSBank = FSMC_NORSRAM_BANK3;
  sramHandle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  sramHandle.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  sramHandle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  sramHandle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  sramHandle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  sramHandle.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  sramHandle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  sramHandle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  sramHandle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  sramHandle.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  sramHandle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  sramHandle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
 //  sramHandle.Init.PageSize = FSMC_PAGE_SIZE_NONE;

  /* Timing
    IS64LV25616-12T   12ns
	IS61LV25616AL-10T 10ns
	IS62WV51216BLL-55 55NS
  */
  Timing.AddressSetupTime      = 2;	  //  6ns(1/168M)*(HCLK+1) ns	
  Timing.AddressHoldTime       = 1;   //  FSMC_ACCESS_MODE_A unused 
  Timing.DataSetupTime         = 2;   //  14ns(1/72M)* (1+1) 28ns  for IS64LV25616-10T/12T
  Timing.BusTurnAroundDuration = 1;
  Timing.CLKDivision           = 2;
  Timing.DataLatency           = 2;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&sramHandle, &Timing, NULL) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }
}

NOR_HandleTypeDef norHandle;
uint8_t STM_FSMC_NOR_Init(void)
{ 	
  static FSMC_NORSRAM_TimingTypeDef Timing;
  norHandle.Instance = FSMC_NORSRAM_DEVICE;
  norHandle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  
  STM_FSMC_GPIO_Init();
  
  /* Timing */
  Timing.AddressSetupTime = 5;
  Timing.AddressHoldTime = 1;
  Timing.DataSetupTime = 7;   
  Timing.BusTurnAroundDuration = 1;
  Timing.CLKDivision = 2;
  Timing.DataLatency = 2;
  Timing.AccessMode = FSMC_ACCESS_MODE_B;

  norHandle.Init.NSBank 			= FSMC_NORSRAM_BANK2;   		//BANK2 
  norHandle.Init.DataAddressMux 	= FSMC_DATA_ADDRESS_MUX_DISABLE;
  norHandle.Init.MemoryType 		= FSMC_MEMORY_TYPE_NOR;
  norHandle.Init.MemoryDataWidth	= FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  norHandle.Init.BurstAccessMode	= FSMC_BURST_ACCESS_MODE_DISABLE;
  norHandle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  norHandle.Init.WrapMode 			= FSMC_WRAP_MODE_DISABLE;
  norHandle.Init.WaitSignalActive 	= FSMC_WAIT_TIMING_BEFORE_WS;
  norHandle.Init.WriteOperation 	= FSMC_WRITE_OPERATION_ENABLE;
  norHandle.Init.WaitSignal 		= FSMC_WAIT_SIGNAL_DISABLE;
  norHandle.Init.ExtendedMode 		= FSMC_EXTENDED_MODE_DISABLE;
  norHandle.Init.AsynchronousWait 	= FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  norHandle.Init.WriteBurst 		= FSMC_WRITE_BURST_DISABLE;

  /* ExtTiming */

  if(HAL_NOR_Init(&norHandle, &Timing, &Timing) != HAL_OK)
  {
    return HAL_ERROR;
  }
  else
  {
    return HAL_OK;  // return 0
  }
}

NAND_HandleTypeDef nandHandle;
void STM_FSMC_NAND_Init(void)
{ 	
  FSMC_NAND_PCC_TimingTypeDef Timing;

  STM_FSMC_GPIO_Init();
  
  nandHandle.Instance  = FSMC_NAND_DEVICE;
  
  /*NAND Configuration */  
  Timing.SetupTime     = 0U;
  Timing.WaitSetupTime = 2U; 
  Timing.HoldSetupTime = 1U;
  Timing.HiZSetupTime  = 0U;
  
  nandHandle.Init.NandBank        = FSMC_NAND_BANK2;
  nandHandle.Init.Waitfeature     = FSMC_NAND_PCC_WAIT_FEATURE_ENABLE;
  nandHandle.Init.MemoryDataWidth = FSMC_NAND_PCC_MEM_BUS_WIDTH_8;
  nandHandle.Init.EccComputation  = FSMC_NAND_ECC_ENABLE;
  nandHandle.Init.ECCPageSize     = FSMC_NAND_ECC_PAGE_SIZE_512BYTE;
  nandHandle.Init.TCLRSetupTime   = 0U;
  nandHandle.Init.TARSetupTime    = 0U;
  
  nandHandle.Config.BlockNbr      = NAND_MAX_PLANE;
  nandHandle.Config.BlockSize     = NAND_BLOCK_SIZE;
  nandHandle.Config.PlaneSize     = NAND_PLANE_SIZE;
  nandHandle.Config.PageSize      = NAND_PAGE_SIZE; 
  nandHandle.Config.SpareAreaSize = NAND_SPARE_AREA_SIZE;
  
  /* NAND controller initialization */
//  NAND_MspInit();
  HAL_NAND_Init(&nandHandle, &Timing, &Timing);
}

#ifndef  LCD_ADDR_SETUPTIME
# define LCD_ADDR_SETUPTIME 20
#endif
#ifndef  LCD_DATA_SETUPTIME
# define LCD_DATA_SETUPTIME 45
#endif

void STM_FSMC_LCD_Init(void)
{
	STM_FSMC_LCD_TimeSet(LCD_ADDR_SETUPTIME, LCD_DATA_SETUPTIME);
#ifdef LCDBL_PIN
    pinMode(LCDBL_PIN,OUTPUT);
# ifdef LCDBL_ON
	digitalWrite(LCDBL_PIN, LCDBL_ON); //backlight on if can set
# else	
	digitalWrite(LCDBL_PIN, HIGH); //backlight on if can set
# endif	
#endif	
}

//void preinitVariant() {

//}

#ifndef DATA_IN_ExtSRAM
void initVariant() {
	STM_FSMC_SRAM_Init();
//  setHeapAtSram();
}
#endif

extern void setHeap(unsigned char* s, unsigned char* e);
void setHeapAtSram(void){
 setHeap((unsigned char*)SRAM_START, (unsigned char*)(SRAM_START +SRAM_LENGTH));
}
