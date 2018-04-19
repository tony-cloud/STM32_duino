#ifndef _STM32_IO_MACRO_H_
#define _STM32_IO_MACRO_H_


#ifndef _BV
#define _BV(A)       (1U<<(A))
#endif

#ifdef STM32GENERIC

#define GPIO_ASSIGN			    STM32_GPIO_ASSIGN
#define GPIO_ASSIGN_POLARITY	STM32_GPIO_ASSIGN_POLARITY
#define ARDUINO_ASSIGN			STM32_GNAME_ASSIGN
#define ARDUINO_ASSIGN_POLARITY	STM32_GNAME_ASSIGN_POLARITY

//fast_io
#define PORTPIN_IN(p,n)     ((GPIO##p##->IDR) &(1<<n))
#define PORTPIN_LOW(p,n)    ((GPIO_TypeDef*)GPIO##p##->ODR &=~(1<<n))
#define PORTPIN_HIGH(p,n)   ((GPIO_TypeDef*)GPIO##p##->ODR |=(1<<n))
#define PORTPIN_TOGGLE(p,n) ((GPIO_TypeDef*)GPIO##p##->ODR ^=(1<<n))

#define STM32_GPIO_ASSIGN(A, C)\
static inline void   P##A##C##_Set(void)            {GPIO##A->ODR |=  _BV( C);}\
static inline void   P##A##C##_Clr(void)            {GPIO##A->ODR &= ~_BV( C);}\
static inline void   P##A##C##_Toggle(void)         {GPIO##A->ODR ^=  _BV( C);}\
static inline uint8_t  P##A##C##_ReadIn(void)       {return ((GPIO##A->IDR & _BV( C)) != 0);}\
static inline uint8_t  P##A##C##_Read(void)         {return P##A##C##_ReadIn();}\
static inline uint8_t  P##A##C##_ReadOut(void)      {return ((GPIO##A->ODR & _BV( C)) != 0);}\
static inline void   	 P##A##C##_Out(uint8_t x)     {(x)?(P##A##C##_Set()):(P##A##C##_Clr());}\
static inline uint8_t  P##A##C##_IsOutHigh(void)    {return P##A##C##_ReadOut();}\
static inline uint8_t  P##A##C##_IsOutLow(void)     {return !P##A##C##_ReadOut();}

#define STM32_GPIO_ASSIGN_POLARITY(A, C, X) \
STM8_GPIO_ASSIGN(A, C)\
static inline void     P##A##C##_On(void)           { (X)?(P##A##C##_Set()):(P##A##C##_Clr());}\
static inline void     P##A##C##_Off(void)          {(!X)?(P##A##C##_Set()):(P##A##C##_Clr());}\
static inline uint8_t  P##A##C##_IsOn(void)         {return  (X)?P##A##C##_IsOutHigh():P##A##C##_IsOutLow();}\
static inline uint8_t  P##A##C##_IsOff(void)        {return (!X)?P##A##C##_IsOutHigh():P##A##C##_IsOutLow();}

#define STM32_GNAME_ASSIGN(N, A, C)\
static inline void   N##_Set(void)            {GPIO##A->ODR |=  _BV( C);}\
static inline void   N##_Clr(void)            {GPIO##A->ODR &= ~_BV( C);}\
static inline void   N##_Toggle(void)         {GPIO##A->ODR ^=  _BV( C);}\
static inline uint8_t  N##_ReadIn(void)       {return ((GPIO##A->IDR & _BV( C)) != 0);}\
static inline uint8_t  N##_Read(void)         {return N##_ReadIn();}\
static inline uint8_t  N##_ReadOut(void)      {return ((GPIO##A->ODR & _BV( C)) != 0);}\
static inline uint8_t  N##_ReadDir(void)      {return ((GPIO##A->DDR & _BV( C)) != 0);}\
static inline void   	 N##_Out(uint8_t x)     {(x)?(N##_Set()):(N##_Clr());}\
static inline uint8_t  N##_IsOutHigh(void)    {return N##_ReadOut();}\
static inline uint8_t  N##_IsOutLow(void)     {return !N##_ReadOut();}


#define STM32_GNAME_ASSIGN_POLARITY(N, A, C, X) \
STM32_GPIO_ASSIGN(A, C)\
static inline void     N##_On(void)           { (X)?(N##_Set()):(N##_Clr());}\
static inline void     N##_Off(void)          {(!X)?(N##_Set()):(N##_Clr());}\
static inline uint8_t  N##_IsOn(void)         {return  (X)?N##_IsOutHigh():N##_IsOutLow();}\
static inline uint8_t  N##_IsOff(void)        {return (!X)?N##_IsOutHigh():N##_IsOutLow();}

#elif  ARDUINO_ARCH_STM8

#define GPIO_ASSIGN			    STM8_GPIO_ASSIGN
#define GPIO_ASSIGN_POLARITY	STM8_GPIO_ASSIGN_POLARITY
#define SDUINO_ASSIGN			STM8_GNAME_ASSIGN
#define SDUINO_ASSIGN_POLARITY	STM8_GNAME_ASSIGN_POLARITY


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

#define STM8_GNAME_ASSIGN(N, A, C)\
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


#define STM8_GNAME_ASSIGN_POLARITY(N, A, C, X) \
STM8_GPIO_ASSIGN(A, C)\
static  void     N##_On(void)           { (X)?(N##_Set()):(N##_Clr());}\
static  void     N##_Off(void)          {(!X)?(N##_Set()):(N##_Clr());}\
static  uint8_t  N##_IsOn(void)         {return  (X)?N##_IsOutHigh():N##_IsOutLow();}\
static  uint8_t  N##_IsOff(void)        {return (!X)?N##_IsOutHigh():N##_IsOutLow();}
#elif  ARDUINO_ARCH_STM8

#define GPIO_ASSIGN			    STM8_GPIO_ASSIGN
#define GPIO_ASSIGN_POLARITY	STM8_GPIO_ASSIGN_POLARITY
#define SDUINO_ASSIGN			STM8_GNAME_ASSIGN
#define SDUINO_ASSIGN_POLARITY	STM8_GNAME_ASSIGN_POLARITY


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

#define STM8_GNAME_ASSIGN(N, A, C)\
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


#define STM8_GNAME_ASSIGN_POLARITY(N, A, C, X) \
STM8_GPIO_ASSIGN(A, C)\
static  void     N##_On(void)           { (X)?(N##_Set()):(N##_Clr());}\
static  void     N##_Off(void)          {(!X)?(N##_Set()):(N##_Clr());}\
static  uint8_t  N##_IsOn(void)         {return  (X)?N##_IsOutHigh():N##_IsOutLow();}\
static  uint8_t  N##_IsOff(void)        {return (!X)?N##_IsOutHigh():N##_IsOutLow();}

#else
// !other here!	 add me
#endif  // ARDUINO_ARCH_STM8

#define PIN_IN(p)     (*portInputRegister(digitalPinToPort(p))& digitalPinToBitMask(p))
#define PIN_LOW(p)    *portOutputRegister(digitalPinToPort(p)) &=~ digitalPinToBitMask(p)
#define PIN_HIGH(p)   *portOutputRegister(digitalPinToPort(p)) |= digitalPinToBitMask(p)
#define PIN_TOGGLE(p) *portOutputRegister(digitalPinToPort(p)) ^= digitalPinToBitMask(p)

#ifdef PA0
#define       pinMode_PA0(n)     pinMode(PA0,n)
#define   digitalRead_PA0()   PORTPIN_IN(A,0)
#define  digitalWrite_PA0(n) ((n)?PORTPIN_HIGH(A,0):PORTPINPORTPIN_LOW(A,0))
#define digitalToggle_PA0() PORTPIN_TOGGLE(A,0)
#endif

#ifdef PA1
#define       pinMode_PA1(n)     pinMode(PA1,n)
#define   digitalRead_PA1()   PORTPIN_IN(A,1)
#define  digitalWrite_PA1(n) ((n)?PORTPIN_HIGH(A,1):PORTPINPORTPIN_LOW(A,1))
#define digitalToggle_PA1() PORTPIN_TOGGLE(A,1)
#endif

#ifdef PA2
#define       pinMode_PA2(n)     pinMode(PA2,n)
#define   digitalRead_PA2()   PORTPIN_IN(A,2)
#define  digitalWrite_PA2(n) ((n)?PORTPIN_HIGH(A,2):PORTPINPORTPIN_LOW(A,2))
#define digitalToggle_PA2() PORTPIN_TOGGLE(A,2)
#endif

#ifdef                PA3
#define       pinMode_PA3(n)\
              pinMode(PA3,n)
#define   digitalRead_PA3()\
           PORTPIN_IN(A,3)
#define  digitalWrite_PA3(n)\
    ((n)?PORTPIN_HIGH(A,3):\
   PORTPINPORTPIN_LOW(A,3))
#define digitalToggle_PA3()\
       PORTPIN_TOGGLE(A,3)
#endif

#ifdef                PA4
#define       pinMode_PA4(n)\
              pinMode(PA4,n)
#define   digitalRead_PA4()\
           PORTPIN_IN(A,4)
#define  digitalWrite_PA4(n)\
    ((n)?PORTPIN_HIGH(A,4):\
   PORTPINPORTPIN_LOW(A,4))
#define digitalToggle_PA4()\
       PORTPIN_TOGGLE(A,4)
#endif

#ifdef                PA5
#define       pinMode_PA5(n)\
              pinMode(PA5,n)
#define   digitalRead_PA5()\
           PORTPIN_IN(A,5)
#define  digitalWrite_PA5(n)\
    ((n)?PORTPIN_HIGH(A,5):\
   PORTPINPORTPIN_LOW(A,5))
#define digitalToggle_PA5()\
       PORTPIN_TOGGLE(A,5)
#endif

#ifdef                PA6
#define       pinMode_PA6(n)\
              pinMode(PA6,n)
#define   digitalRead_PA6()\
           PORTPIN_IN(A,6)
#define  digitalWrite_PA6(n)\
    ((n)?PORTPIN_HIGH(A,6):\
   PORTPINPORTPIN_LOW(A,6))
#define digitalToggle_PA6()\
       PORTPIN_TOGGLE(A,6)
#endif

#ifdef                PA7
#define       pinMode_PA7(n)\
              pinMode(PA7,n)
#define   digitalRead_PA7()\
           PORTPIN_IN(A,7)
#define  digitalWrite_PA7(n)\
    ((n)?PORTPIN_HIGH(A,7):\
   PORTPINPORTPIN_LOW(A,7))
#define digitalToggle_PA7()\
       PORTPIN_TOGGLE(A,7)
#endif

#ifdef                PB0
#define       pinMode_PB0(n)\
              pinMode(PB0,n)
#define   digitalRead_PB0()\
           PORTPIN_IN(B,0)
#define  digitalWrite_PB0(n)\
    ((n)?PORTPIN_HIGH(B,0):\
   PORTPINPORTPIN_LOW(B,0))
#define digitalToggle_PB0()\
       PORTPIN_TOGGLE(B,0)
#endif

#ifdef                PB1
#define       pinMode_PB1(n)\
              pinMode(PB1,n)
#define   digitalRead_PB1()\
           PORTPIN_IN(B,1)
#define  digitalWrite_PB1(n)\
    ((n)?PORTPIN_HIGH(B,1):\
   PORTPINPORTPIN_LOW(B,1))
#define digitalToggle_PB1()\
       PORTPIN_TOGGLE(B,1)
#endif

#ifdef                PB2
#define       pinMode_PB2(n)\
              pinMode(PB2,n)
#define   digitalRead_PB2()\
           PORTPIN_IN(B,2)
#define  digitalWrite_PB2(n)\
    ((n)?PORTPIN_HIGH(B,2):\
   PORTPINPORTPIN_LOW(B,2))
#define digitalToggle_PB2()\
       PORTPIN_TOGGLE(B,2)
#endif

#ifdef                PB3
#define       pinMode_PB3(n)\
              pinMode(PB3,n)
#define   digitalRead_PB3()\
           PORTPIN_IN(B,3)
#define  digitalWrite_PB3(n)\
    ((n)?PORTPIN_HIGH(B,3):\
   PORTPINPORTPIN_LOW(B,3))
#define digitalToggle_PB3()\
       PORTPIN_TOGGLE(B,3)
#endif

#ifdef                PB4
#define       pinMode_PB4(n)\
              pinMode(PB4,n)
#define   digitalRead_PB4()\
           PORTPIN_IN(B,4)
#define  digitalWrite_PB4(n)\
    ((n)?PORTPIN_HIGH(B,4):\
   PORTPINPORTPIN_LOW(B,4))
#define digitalToggle_PB4()\
       PORTPIN_TOGGLE(B,4)
#endif

#ifdef                PB5
#define       pinMode_PB5(n)\
              pinMode(PB5,n)
#define   digitalRead_PB5()\
           PORTPIN_IN(B,5)
#define  digitalWrite_PB5(n)\
    ((n)?PORTPIN_HIGH(B,5):\
   PORTPINPORTPIN_LOW(B,5))
#define digitalToggle_PB5()\
       PORTPIN_TOGGLE(B,5)
#endif

#ifdef                PB6
#define       pinMode_PB6(n)\
              pinMode(PB6,n)
#define   digitalRead_PB6()\
           PORTPIN_IN(B,6)
#define  digitalWrite_PB6(n)\
    ((n)?PORTPIN_HIGH(B,6):\
   PORTPINPORTPIN_LOW(B,6))
#define digitalToggle_PB6()\
       PORTPIN_TOGGLE(B,6)
#endif

#ifdef                PB7
#define       pinMode_PB7(n)\
              pinMode(PB7,n)
#define   digitalRead_PB7()\
           PORTPIN_IN(B,7)
#define  digitalWrite_PB7(n)\
    ((n)?PORTPIN_HIGH(B,7):\
   PORTPINPORTPIN_LOW(B,7))
#define digitalToggle_PB7()\
       PORTPIN_TOGGLE(B,7)
#endif

#ifdef                PC0
#define       pinMode_PC0(n)\
              pinMode(PC0,n)
#define   digitalRead_PC0()\
           PORTPIN_IN(C,0)
#define  digitalWrite_PC0(n)\
    ((n)?PORTPIN_HIGH(C,0):\
   PORTPINPORTPIN_LOW(C,0))
#define digitalToggle_PC0()\
       PORTPIN_TOGGLE(C,0)
#endif

#ifdef                PC1
#define       pinMode_PC1(n)\
              pinMode(PC1,n)
#define   digitalRead_PC1()\
           PORTPIN_IN(C,1)
#define  digitalWrite_PC1(n)\
    ((n)?PORTPIN_HIGH(C,1):\
   PORTPINPORTPIN_LOW(C,1))
#define digitalToggle_PC1()\
       PORTPIN_TOGGLE(C,1)
#endif

#ifdef                PC2
#define       pinMode_PC2(n)\
              pinMode(PC2,n)
#define   digitalRead_PC2()\
           PORTPIN_IN(C,2)
#define  digitalWrite_PC2(n)\
    ((n)?PORTPIN_HIGH(C,2):\
   PORTPINPORTPIN_LOW(C,2))
#define digitalToggle_PC2()\
       PORTPIN_TOGGLE(C,2)
#endif

#ifdef                PC3
#define       pinMode_PC3(n)\
              pinMode(PC3,n)
#define   digitalRead_PC3()\
           PORTPIN_IN(C,3)
#define  digitalWrite_PC3(n)\
    ((n)?PORTPIN_HIGH(C,3):\
   PORTPINPORTPIN_LOW(C,3))
#define digitalToggle_PC3()\
       PORTPIN_TOGGLE(C,3)
#endif

#ifdef                PC4
#define       pinMode_PC4(n)\
              pinMode(PC4,n)
#define   digitalRead_PC4()\
           PORTPIN_IN(C,4)
#define  digitalWrite_PC4(n)\
    ((n)?PORTPIN_HIGH(C,4):\
   PORTPINPORTPIN_LOW(C,4))
#define digitalToggle_PC4()\
       PORTPIN_TOGGLE(C,4)
#endif

#ifdef                PC5
#define       pinMode_PC5(n)\
              pinMode(PC5,n)
#define   digitalRead_PC5()\
           PORTPIN_IN(C,5)
#define  digitalWrite_PC5(n)\
    ((n)?PORTPIN_HIGH(C,5):\
   PORTPINPORTPIN_LOW(C,5))
#define digitalToggle_PC5()\
       PORTPIN_TOGGLE(C,5)
#endif

#ifdef                PC6
#define       pinMode_PC6(n)\
              pinMode(PC6,n)
#define   digitalRead_PC6()\
           PORTPIN_IN(C,6)
#define  digitalWrite_PC6(n)\
    ((n)?PORTPIN_HIGH(C,6):\
   PORTPINPORTPIN_LOW(C,6))
#define digitalToggle_PC6()\
       PORTPIN_TOGGLE(C,6)
#endif

#ifdef                PC7
#define       pinMode_PC7(n)\
              pinMode(PC7,n)
#define   digitalRead_PC7()\
           PORTPIN_IN(C,7)
#define  digitalWrite_PC7(n)\
    ((n)?PORTPIN_HIGH(C,7):\
   PORTPINPORTPIN_LOW(C,7))
#define digitalToggle_PC7()\
       PORTPIN_TOGGLE(C,7)
#endif

#ifdef                PD0
#define       pinMode_PD0(n)\
              pinMode(PD0,n)
#define   digitalRead_PD0()\
           PORTPIN_IN(D,0)
#define  digitalWrite_PD0(n)\
    ((n)?PORTPIN_HIGH(D,0):\
   PORTPINPORTPIN_LOW(D,0))
#define digitalToggle_PD0()\
       PORTPIN_TOGGLE(D,0)
#endif

#ifdef                PD1
#define       pinMode_PD1(n)\
              pinMode(PD1,n)
#define   digitalRead_PD1()\
           PORTPIN_IN(D,1)
#define  digitalWrite_PD1(n)\
    ((n)?PORTPIN_HIGH(D,1):\
   PORTPINPORTPIN_LOW(D,1))
#define digitalToggle_PD1()\
       PORTPIN_TOGGLE(D,1)
#endif

#ifdef                PD2
#define       pinMode_PD2(n)\
              pinMode(PD2,n)
#define   digitalRead_PD2()\
           PORTPIN_IN(D,2)
#define  digitalWrite_PD2(n)\
    ((n)?PORTPIN_HIGH(D,2):\
   PORTPINPORTPIN_LOW(D,2))
#define digitalToggle_PD2()\
       PORTPIN_TOGGLE(D,2)
#endif

#ifdef                PD3
#define       pinMode_PD3(n)\
              pinMode(PD3,n)
#define   digitalRead_PD3()\
           PORTPIN_IN(D,3)
#define  digitalWrite_PD3(n)\
    ((n)?PORTPIN_HIGH(D,3):\
   PORTPINPORTPIN_LOW(D,3))
#define digitalToggle_PD3()\
       PORTPIN_TOGGLE(D,3)
#endif

#ifdef                PD4
#define       pinMode_PD4(n)\
              pinMode(PD4,n)
#define   digitalRead_PD4()\
           PORTPIN_IN(D,4)
#define  digitalWrite_PD4(n)\
    ((n)?PORTPIN_HIGH(D,4):\
   PORTPINPORTPIN_LOW(D,4))
#define digitalToggle_PD4()\
       PORTPIN_TOGGLE(D,4)
#endif

#ifdef                PD5
#define       pinMode_PD5(n)\
              pinMode(PD5,n)
#define   digitalRead_PD5()\
           PORTPIN_IN(D,5)
#define  digitalWrite_PD5(n)\
    ((n)?PORTPIN_HIGH(D,5):\
   PORTPINPORTPIN_LOW(D,5))
#define digitalToggle_PD5()\
       PORTPIN_TOGGLE(D,5)
#endif

#ifdef                PD6
#define       pinMode_PD6(n)\
              pinMode(PD6,n)
#define   digitalRead_PD6()\
           PORTPIN_IN(D,6)
#define  digitalWrite_PD6(n)\
    ((n)?PORTPIN_HIGH(D,6):\
   PORTPINPORTPIN_LOW(D,6))
#define digitalToggle_PD6()\
       PORTPIN_TOGGLE(D,6)
#endif

#ifdef                PD7
#define       pinMode_PD7(n)\
              pinMode(PD7,n)
#define   digitalRead_PD7()\
           PORTPIN_IN(D,7)
#define  digitalWrite_PD7(n)\
    ((n)?PORTPIN_HIGH(D,7):\
   PORTPINPORTPIN_LOW(D,7))
#define digitalToggle_PD7()\
       PORTPIN_TOGGLE(D,7)
#endif

#ifdef                PE0
#define       pinMode_PE0(n)\
              pinMode(PE0,n)
#define   digitalRead_PE0()\
           PORTPIN_IN(E,0)
#define  digitalWrite_PE0(n)\
    ((n)?PORTPIN_HIGH(E,0):\
   PORTPINPORTPIN_LOW(E,0))
#define digitalToggle_PE0()\
       PORTPIN_TOGGLE(E,0)
#endif


#ifdef                PE1
#define       pinMode_PE1(n)\
              pinMode(PE1,n)
#define   digitalRead_PE1()\
           PORTPIN_IN(E,1)
#define  digitalWrite_PE1(n)\
    ((n)?PORTPIN_HIGH(E,1):\
   PORTPINPORTPIN_LOW(E,1))
#define digitalToggle_PE1()\
       PORTPIN_TOGGLE(E,1)
#endif


#ifdef                PE2
#define       pinMode_PE2(n)\
              pinMode(PE2,n)
#define   digitalRead_PE2()\
           PORTPIN_IN(E,2)
#define  digitalWrite_PE2(n)\
    ((n)?PORTPIN_HIGH(E,2):\
   PORTPINPORTPIN_LOW(E,2))
#define digitalToggle_PE2()\
       PORTPIN_TOGGLE(E,2)
#endif


#ifdef                PE3
#define       pinMode_PE3(n)\
              pinMode(PE3,n)
#define   digitalRead_PE3()\
           PORTPIN_IN(E,3)
#define  digitalWrite_PE3(n)\
    ((n)?PORTPIN_HIGH(E,3):\
   PORTPINPORTPIN_LOW(E,3))
#define digitalToggle_PE3()\
       PORTPIN_TOGGLE(E,3)
#endif


#ifdef                PE4
#define       pinMode_PE4(n)\
              pinMode(PE4,n)
#define   digitalRead_PE4()\
           PORTPIN_IN(E,4)
#define  digitalWrite_PE4(n)\
    ((n)?PORTPIN_HIGH(E,4):\
   PORTPINPORTPIN_LOW(E,4))
#define digitalToggle_PE4()\
       PORTPIN_TOGGLE(E,4)
#endif


#ifdef                PE5
#define       pinMode_PE5(n)\
              pinMode(PE5,n)
#define   digitalRead_PE5()\
           PORTPIN_IN(E,5)
#define  digitalWrite_PE5(n)\
    ((n)?PORTPIN_HIGH(E,5):\
   PORTPINPORTPIN_LOW(E,5))
#define digitalToggle_PE5()\
       PORTPIN_TOGGLE(E,5)
#endif


#ifdef                PE6
#define       pinMode_PE6(n)\
              pinMode(PE6,n)
#define   digitalRead_PE6()\
           PORTPIN_IN(E,6)
#define  digitalWrite_PE6(n)\
    ((n)?PORTPIN_HIGH(E,6):\
   PORTPINPORTPIN_LOW(E,6))
#define digitalToggle_PE6()\
       PORTPIN_TOGGLE(E,6)
#endif


#ifdef                PE7
#define       pinMode_PE7(n)\
              pinMode(PE7,n)
#define   digitalRead_PE7()\
           PORTPIN_IN(E,7)
#define  digitalWrite_PE7(n)\
    ((n)?PORTPIN_HIGH(E,7):\
   PORTPINPORTPIN_LOW(E,7))
#define digitalToggle_PE7()\
       PORTPIN_TOGGLE(E,7)
#endif

#ifdef                PF0
#define       pinMode_PF0(n)\
              pinMode(PF0,n)
#define   digitalRead_PF0()\
           PORTPIN_IN(F,0)
#define  digitalWrite_PF0(n)\
    ((n)?PORTPIN_HIGH(F,0):\
   PORTPINPORTPIN_LOW(F,0))
#define digitalToggle_PF0()\
       PORTPIN_TOGGLE(F,0)
#endif

#ifdef                PF1
#define       pinMode_PF1(n)\
              pinMode(PF1,n)
#define   digitalRead_PF1()\
           PORTPIN_IN(F,1)
#define  digitalWrite_PF1(n)\
    ((n)?PORTPIN_HIGH(F,1):\
   PORTPINPORTPIN_LOW(F,1))
#define digitalToggle_PF1()\
       PORTPIN_TOGGLE(F,1)
#endif

#ifdef                PF2
#define       pinMode_PF2(n)\
              pinMode(PF2,n)
#define   digitalRead_PF2()\
           PORTPIN_IN(F,2)
#define  digitalWrite_PF2(n)\
    ((n)?PORTPIN_HIGH(F,2):\
   PORTPINPORTPIN_LOW(F,2))
#define digitalToggle_PF2()\
       PORTPIN_TOGGLE(F,2)
#endif

#ifdef                PF3
#define       pinMode_PF3(n)\
              pinMode(PF3,n)
#define   digitalRead_PF3()\
           PORTPIN_IN(F,3)
#define  digitalWrite_PF3(n)\
    ((n)?PORTPIN_HIGH(F,3):\
   PORTPINPORTPIN_LOW(F,3))
#define digitalToggle_PF3()\
       PORTPIN_TOGGLE(F,3)
#endif

#ifdef                PF4
#define       pinMode_PF4(n)\
              pinMode(PF4,n)
#define   digitalRead_PF4()\
           PORTPIN_IN(F,4)
#define  digitalWrite_PF4(n)\
    ((n)?PORTPIN_HIGH(F,4):\
   PORTPINPORTPIN_LOW(F,4))
#define digitalToggle_PF4()\
       PORTPIN_TOGGLE(F,4)
#endif

#ifdef                PF5
#define       pinMode_PF5(n)\
              pinMode(PF5,n)
#define   digitalRead_PF5()\
           PORTPIN_IN(F,5)
#define  digitalWrite_PF5(n)\
    ((n)?PORTPIN_HIGH(F,5):\
   PORTPINPORTPIN_LOW(F,5))
#define digitalToggle_PF5()\
       PORTPIN_TOGGLE(F,5)
#endif

#ifdef                PF6
#define       pinMode_PF6(n)\
              pinMode(PF6,n)
#define   digitalRead_PF6()\
           PORTPIN_IN(F,6)
#define  digitalWrite_PF6(n)\
    ((n)?PORTPIN_HIGH(F,6):\
   PORTPINPORTPIN_LOW(F,6))
#define digitalToggle_PF6()\
       PORTPIN_TOGGLE(F,6)
#endif

#ifdef                PF7
#define       pinMode_PF7(n)\
              pinMode(PF7,n)
#define   digitalRead_PF7()\
           PORTPIN_IN(F,7)
#define  digitalWrite_PF7(n)\
    ((n)?PORTPIN_HIGH(F,7):\
   PORTPINPORTPIN_LOW(F,7))
#define digitalToggle_PF7()\
       PORTPIN_TOGGLE(F,7)
#endif

#ifdef                PG0
#define       pinMode_PG0(n)\
              pinMode(PG0,n)
#define   digitalRead_PG0()\
           PORTPIN_IN(G,0)
#define  digitalWrite_PG0(n)\
    ((n)?PORTPIN_HIGH(G,0):\
   PORTPINPORTPIN_LOW(G,0))
#define digitalToggle_PG0()\
       PORTPIN_TOGGLE(G,0)
#endif

#ifdef                PG1
#define       pinMode_PG1(n)\
              pinMode(PG1,n)
#define   digitalRead_PG1()\
           PORTPIN_IN(G,1)
#define  digitalWrite_PG1(n)\
    ((n)?PORTPIN_HIGH(G,1):\
   PORTPINPORTPIN_LOW(G,1))
#define digitalToggle_PG1()\
       PORTPIN_TOGGLE(G,1)
#endif

#ifdef                PG2
#define       pinMode_PG2(n)\
              pinMode(PG2,n)
#define   digitalRead_PG2()\
           PORTPIN_IN(G,2)
#define  digitalWrite_PG2(n)\
    ((n)?PORTPIN_HIGH(G,2):\
   PORTPINPORTPIN_LOW(G,2))
#define digitalToggle_PG2()\
       PORTPIN_TOGGLE(G,2)
#endif

#ifdef                PG3
#define       pinMode_PG3(n)\
              pinMode(PG3,n)
#define   digitalRead_PG3()\
           PORTPIN_IN(G,3)
#define  digitalWrite_PG3(n)\
    ((n)?PORTPIN_HIGH(G,3):\
   PORTPINPORTPIN_LOW(G,3))
#define digitalToggle_PG3()\
       PORTPIN_TOGGLE(G,3)
#endif

#ifdef                PG4
#define       pinMode_PG4(n)\
              pinMode(PG4,n)
#define   digitalRead_PG4()\
           PORTPIN_IN(G,4)
#define  digitalWrite_PG4(n)\
    ((n)?PORTPIN_HIGH(G,4):\
   PORTPINPORTPIN_LOW(G,4))
#define digitalToggle_PG4()\
       PORTPIN_TOGGLE(G,4)
#endif

#ifdef                PG5
#define       pinMode_PG5(n)\
              pinMode(PG5,n)
#define   digitalRead_PG5()\
           PORTPIN_IN(G,5)
#define  digitalWrite_PG5(n)\
    ((n)?PORTPIN_HIGH(G,5):\
   PORTPINPORTPIN_LOW(G,5))
#define digitalToggle_PG5()\
       PORTPIN_TOGGLE(G,5)
#endif

#ifdef                PG6
#define       pinMode_PG6(n)\
              pinMode(PG6,n)
#define   digitalRead_PG6()\
           PORTPIN_IN(G,6)
#define  digitalWrite_PG6(n)\
    ((n)?PORTPIN_HIGH(G,6):\
   PORTPINPORTPIN_LOW(G,6))
#define digitalToggle_PG6()\
       PORTPIN_TOGGLE(G,6)
#endif

#ifdef                PG7
#define       pinMode_PG7(n)\
              pinMode(PG7,n)
#define   digitalRead_PG7()\
           PORTPIN_IN(G,7)
#define  digitalWrite_PG7(n)\
    ((n)?PORTPIN_HIGH(G,7):\
   PORTPINPORTPIN_LOW(G,7))
#define digitalToggle_PG7()\
       PORTPIN_TOGGLE(G,7)
#endif

#endif //_STM8_FASTIO_H_
