#ifndef _STM32_IO_MACRO_H_
#define _STM32_IO_MACRO_H_


#ifndef _BV
#define _BV(A)       (1U<<(A))
#endif

#ifdef STM32GENERIC

#define GPIO_ASSIGN			    	STM32_GPIO_ASSIGN
#define GPIO_ASSIGN_POLARITY		STM32_GPIO_ASSIGN_POLARITY
#define GPIO_ALIAS_ASSIGN			STM32_ALIAS_ASSIGN
#define GPIO_ALIAS_ASSIGN_POLARITY	STM32_ALIAS_ASSIGN_POLARITY

//fast_io
#ifdef STM32H7
#define PORTPIN_IN(p,n)     ((GPIO##p##->IDR) &(1<<n))
#define PORTPIN_LOW(p,n)    ((GPIO##p->BSRRL) = (1<<n))
#define PORTPIN_HIGH(p,n)   ((GPIO##p->BSRRH) = (1<<n))
#define PORTPIN_TOGGLE(p,n) ((GPIO##p->ODR) ^=(1<<n))
#define PORTPIN_Mode(p,n,x) pinMode(P##p##n,x)
#else
#define PORTPIN_IN(p,n)      LL_GPIO_IsInputPinSet(GPIO##p,LL_GPIO_PIN_##n)
#define PORTPIN_LOW(p,n)     LL_GPIO_ResetOutputPin(GPIO##p,LL_GPIO_PIN_##n)
#define PORTPIN_HIGH(p,n)    LL_GPIO_SetOutputPin(GPIO##p,LL_GPIO_PIN_##n)
#define PORTPIN_TOGGLE(p,n)  LL_GPIO_TogglePin(GPIO##p,LL_GPIO_PIN_##n)
#define PORTPIN_Mode(p,n,x)  pinModeLL(GPIO##p,LL_GPIO_PIN_##n,x)
#endif

#define STM32_GPIO_ASSIGN(A, C)\
static inline void     P##A##C##_Set(void)          {PORTPIN_HIGH(A,C);}\
static inline void     P##A##C##_Clr(void)          {PORTPIN_LOW(A,C);}\
static inline void     P##A##C##_High(void)         {PORTPIN_HIGH(A,C);}\
static inline void     P##A##C##_Low(void)          {PORTPIN_LOW(A,C);}\
static inline void     P##A##C##_Toggle(void)       {PORTPIN_TOGGLE(A,C);}\
static inline void     P##A##C##_Mode(uint8_t mode) {PORTPIN_Mode(A,C,mode);}\
static inline uint8_t  P##A##C##_ReadIn(void)       {return (PORTPIN_IN(A,C) != 0);}\
static inline uint8_t  P##A##C##_Read(void)         {return P##A##C##_ReadIn();}\
static inline uint8_t  P##A##C##_ReadOut(void)      {return ((GPIO##A->ODR & _BV( C)) != 0);}\
static inline void	   P##A##C##_Out(uint8_t x)     {(x)?(P##A##C##_Set()):(P##A##C##_Clr());}\
static inline uint8_t  P##A##C##_IsOutHigh(void)    {return P##A##C##_ReadOut();}\
static inline uint8_t  P##A##C##_IsOutLow(void)     {return !P##A##C##_ReadOut();}

#define STM32_GPIO_ASSIGN_POLARITY(A, C, X) \
STM32_GPIO_ASSIGN(A, C)\
static inline void     P##A##C##_On(void)           {(X)?(P##A##C##_Set()):(P##A##C##_Clr());}\
static inline void     P##A##C##_Off(void)          {(!X)?(P##A##C##_Set()):(P##A##C##_Clr());}\
static inline uint8_t  P##A##C##_IsOn(void)         {return (X)?P##A##C##_IsOutHigh():P##A##C##_IsOutLow();}\
static inline uint8_t  P##A##C##_IsOff(void)        {return (!X)?P##A##C##_IsOutHigh():P##A##C##_IsOutLow();}

#define STM32_ALIAS_ASSIGN(N, A, C)\
static inline void     N##_Set(void)          {PORTPIN_HIGH(A,C);}\
static inline void     N##_Clr(void)          {PORTPIN_LOW(A,C);}\
static inline void     N##_High(void)         {PORTPIN_HIGH(A,C);}\
static inline void     N##_Low(void)          {PORTPIN_LOW(A,C);}\
static inline void     N##_Toggle(void)       {PORTPIN_TOGGLE(A,C);}\
static inline void     N##_Mode(uint8_t mode) {PORTPIN_Mode(A,C,mode);}\
static inline uint8_t  N##_ReadIn(void)       {return (PORTPIN_IN(A,C) != 0);}\
static inline uint8_t  N##_Read(void)         {return N##_ReadIn();}\
static inline uint8_t  N##_ReadOut(void)      {return ((GPIO##A->ODR & _BV( C)) != 0);}\
static inline void     N##_Out(uint8_t x)     {(x)?(N##_Set()):(N##_Clr());}\
static inline uint8_t  N##_IsOutHigh(void)    {return N##_ReadOut();}\
static inline uint8_t  N##_IsOutLow(void)     {return !N##_ReadOut();}


#define STM32_GNAME_ASSIGN_POLARITY(N, A, C, X) \
STM32_ALIAS_ASSIGN(A, C)\
static inline void     N##_On(void)           {(X)?(N##_Set()):(N##_Clr());}\
static inline void     N##_Off(void)          {(!X)?(N##_Set()):(N##_Clr());}\
static inline uint8_t  N##_IsOn(void)         {return  (X)?N##_IsOutHigh():N##_IsOutLow();}\
static inline uint8_t  N##_IsOff(void)        {return (!X)?N##_IsOutHigh():N##_IsOutLow();}

#elif  ARDUINO_ARCH_STM8

#define GPIO_ASSIGN			    STM8_GPIO_ASSIGN
#define GPIO_ASSIGN_POLARITY	STM8_GPIO_ASSIGN_POLARITY
#define GPIO_ALIAS_ASSIGN	    STM8_ALIAS_ASSIGN
#define GPIO_ALIAS_ASSIGN_POLARITY	STM8_ALIAS_ASSIGN_POLARITY


#define STM8_GPIO_ASSIGN(A, C)\
static  void   P##A##C##_Set(void)            {GPIO##A->ODR |=  _BV( C);}\
static  void   P##A##C##_Clr(void)            {GPIO##A->ODR &= ~_BV( C);}\
static  void   P##A##C##_Toggle(void)         {GPIO##A->ODR ^=  _BV( C);}\
static  void   P##A##C##_MakeOut(void)        {GPIO##A->DDR |=  _BV( C);}\
static  void   P##A##C##_MakeIn(void)         {GPIO##A->DDR &= ~_BV( C);}\
static  void   P##A##C##_SetCR1(void)         {GPIO##A->CR1 |=  _BV( C);}\
static  void   P##A##C##_ClrCR1(void)         {GPIO##A->CR1 &= ~_BV( C);}\
static  void   P##A##C##_SetCR2(void)         {GPIO##A->CR2 |=  _BV( C);}\
static  void   P##A##C##_ClrCR2(void)         {GPIO##A->CR2 &= ~_BV( C);}\
static  void   P##A##C##_MakeInputFloatingWithoutInterrupt(void)  {P##A##C##_MakeIn(); P##A##C##_ClrCR1(); P##A##C##_ClrCR2();}\
static  void   P##A##C##_MakeInputPullupWithoutInterrupt(void)    {P##A##C##_MakeIn(); P##A##C##_SetCR1(); P##A##C##_ClrCR2();}\
static  void   P##A##C##_MakeInputFloatingWithInterrupt(void)     {P##A##C##_MakeIn(); P##A##C##_ClrCR1(); P##A##C##_SetCR2();}\
static  void   P##A##C##_MakeInputPullupWithInterrupt(void)       {P##A##C##_MakeIn(); P##A##C##_SetCR1(); P##A##C##_SetCR2();}\
static  void   P##A##C##_MakeOutputOpenDrainSlow(void)            {P##A##C##_MakeOut();P##A##C##_ClrCR1(); P##A##C##_ClrCR2();}\
static  void   P##A##C##_MakeOutputPushPullSlow(void)             {P##A##C##_MakeOut();P##A##C##_SetCR1(); P##A##C##_ClrCR2();}\
static  void   P##A##C##_MakeOutputOpenDrainFast(void)            {P##A##C##_MakeOut();P##A##C##_ClrCR1(); P##A##C##_SetCR2();}\
static  void   P##A##C##_MakeOutputPushPullFast(void)             {P##A##C##_MakeOut();P##A##C##_SetCR1(); P##A##C##_SetCR2();}\
static  uint8_t  P##A##C##_ReadIn(void)       {return ((GPIO##A->IDR & _BV( C)) != 0);}\
static  uint8_t  P##A##C##_Read(void)         {return P##A##C##_ReadIn();}\
static  uint8_t  P##A##C##_ReadOut(void)      {return ((GPIO##A->ODR & _BV( C)) != 0);}\
static  uint8_t  P##A##C##_ReadDir(void)      {return ((GPIO##A->DDR & _BV( C)) != 0);}\
static  void   	 P##A##C##_Out(uint8_t x)     {(x)?(P##A##C##_Set()):(P##A##C##_Clr());}\
static  uint8_t  P##A##C##_IsOutHigh(void)    {return P##A##C##_ReadOut();}\
static  uint8_t  P##A##C##_IsOutLow(void)     {return !P##A##C##_ReadOut();}


#define STM8_GPIO_ASSIGN_POLARITY(A, C, X) \
STM8_GPIO_ASSIGN(A, C)\
static  void     P##A##C##_On(void)           { (X)?(P##A##C##_Set()):(P##A##C##_Clr());}\
static  void     P##A##C##_Off(void)          {(!X)?(P##A##C##_Set()):(P##A##C##_Clr());}\
static  uint8_t  P##A##C##_IsOn(void)         {return  (X)?P##A##C##_IsOutHigh():P##A##C##_IsOutLow();}\
static  uint8_t  P##A##C##_IsOff(void)        {return (!X)?P##A##C##_IsOutHigh():P##A##C##_IsOutLow();}

#define STM8_ALIAS_ASSIGN(N, A, C)\
static  void   N##_Set(void)            {GPIO##A->ODR |=  _BV( C);}\
static  void   N##_Clr(void)            {GPIO##A->ODR &= ~_BV( C);}\
static  void   N##_Toggle(void)         {GPIO##A->ODR ^=  _BV( C);}\
static  void   N##_MakeOut(void)        {GPIO##A->DDR |=  _BV( C);}\
static  void   N##_MakeIn(void)         {GPIO##A->DDR &= ~_BV( C);}\
static  void   N##_SetCR1(void)         {GPIO##A->CR1 |=  _BV( C);}\
static  void   N##_ClrCR1(void)         {GPIO##A->CR1 &= ~_BV( C);}\
static  void   N##_SetCR2(void)         {GPIO##A->CR2 |=  _BV( C);}\
static  void   N##_ClrCR2(void)         {GPIO##A->CR2 &= ~_BV( C);}\
static  void   N##_MakeInputFloatingWithoutInterrupt(void)  {N##_MakeIn(); N##_ClrCR1(); N##_ClrCR2();}\
static  void   N##_MakeInputPullupWithoutInterrupt(void)    {N##_MakeIn(); N##_SetCR1(); N##_ClrCR2();}\
static  void   N##_MakeInputFloatingWithInterrupt(void)     {N##_MakeIn(); N##_ClrCR1(); N##_SetCR2();}\
static  void   N##_MakeInputPullupWithInterrupt(void)       {N##_MakeIn(); N##_SetCR1(); N##_SetCR2();}\
static  void   N##_MakeOutputOpenDrainSlow(void)            {N##_MakeOut();N##_ClrCR1(); N##_ClrCR2();}\
static  void   N##_MakeOutputPushPullSlow(void)             {N##_MakeOut();N##_SetCR1(); N##_ClrCR2();}\
static  void   N##_MakeOutputOpenDrainFast(void)            {N##_MakeOut();N##_ClrCR1(); N##_SetCR2();}\
static  void   N##_MakeOutputPushPullFast(void)             {N##_MakeOut();N##_SetCR1(); N##_SetCR2();}\
static  uint8_t  N##_ReadIn(void)       {return ((GPIO##A->IDR & _BV( C)) != 0);}\
static  uint8_t  N##_Read(void)         {return N##_ReadIn();}\
static  uint8_t  N##_ReadOut(void)      {return ((GPIO##A->ODR & _BV( C)) != 0);}\
static  uint8_t  N##_ReadDir(void)      {return ((GPIO##A->DDR & _BV( C)) != 0);}\
static  void   	 N##_Out(uint8_t x)     {(x)?(N##_Set()):(N##_Clr());}\
static  uint8_t  N##_IsOutHigh(void)    {return N##_ReadOut();}\
static  uint8_t  N##_IsOutLow(void)     {return !N##_ReadOut();}


#define STM8_ALIAS_ASSIGN_POLARITY(N, A, C, X) \
STM8_ALIAS_ASSIGN(A, C)\
static  void     N##_On(void)           { (X)?(N##_Set()):(N##_Clr());}\
static  void     N##_Off(void)          {(!X)?(N##_Set()):(N##_Clr());}\
static  uint8_t  N##_IsOn(void)         {return  (X)?N##_IsOutHigh():N##_IsOutLow();}\
static  uint8_t  N##_IsOff(void)        {return (!X)?N##_IsOutHigh():N##_IsOutLow();}
#elif  ARDUINO_ARCH_STM8


#else
// !other here!	 add me
#endif  // ARDUINO_ARCH_STM8


#endif //_STM8_FASTIO_H_
