#ifndef __LIB_KEYS_H__
#define __LIB_KEYS_H__

#include <Arduino.h>

#ifdef BUTTON7
#define BUTTONS_LIST BUTTON,BUTTON1,BUTTON2,BUTTON3,BUTTON4,BUTTON5,BUTTON6,BUTTON7
#elif defined(BUTTON6)
#define BUTTONS_LIST BUTTON,BUTTON1,BUTTON2,BUTTON3,BUTTON4,BUTTON5,BUTTON6
#elif defined(BUTTON5)
#define BUTTONS_LIST BUTTON,BUTTON1,BUTTON2,BUTTON3,BUTTON4,BUTTON5
#elif defined(BUTTON4)
#define BUTTONS_LIST BUTTON,BUTTON1,BUTTON2,BUTTON3,BUTTON4
#elif defined(BUTTON3)
#define BUTTONS_LIST BUTTON,BUTTON1,BUTTON2,BUTTON3
#elif defined(BUTTON2)
#define BUTTONS_LIST BUTTON,BUTTON1,BUTTON2
#elif defined(BUTTON1)
#define BUTTONS_LIST BUTTON,BUTTON1
#elif defined(BUTTON)
#define BUTTONS_LIST BUTTON
#endif

#define KEY0	bit(0)
#define KEY1	bit(1)
#define KEY2	bit(2)
#define KEY3	bit(3)
#define KEY4	bit(4)
#define KEY5	bit(5)
#define KEY6	bit(6)
#define KEY7	bit(7)

#define KEY_UNPRESED 0
#define KEY_PRESED	 1


#ifdef __cplusplus

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
}ButtonMode_TypeDef;     

typedef struct {
    uint8_t  pins[16];       /**< pin max 16*/
    uint8_t  nr;             /**< keys num. */
    uint16_t on;             /**< on state, 1 high or 0 low on. */
    uint16_t mode;       /*mode bit 1/0 exti/gpio*/
} BUTTON_TypeDef;


class BUTTONClass
{
  public:
    BUTTONClass();
    BUTTONClass(uint16_t mask, uint8_t k0,
			    uint8_t k1=0xff, uint8_t k2=0xff, uint8_t k3=0xff,
			    uint8_t k4=0xff, uint8_t k5=0xff, uint8_t k6=0xff, uint8_t k7=0xff,
			    uint8_t k8=0xff, uint8_t k9=0xff, uint8_t k10=0xff,uint8_t k11=0xff,
			    uint8_t k12=0xff,uint8_t k13=0xff,uint8_t k14=0xff,uint8_t k15=0xff);
	void setKey(uint8_t pin,uint16_t on,ButtonMode_TypeDef mode = BUTTON_MODE_GPIO);
    void Init();
    uint8_t  getKey(uint8_t key);
    uint16_t scan(uint8_t mode = 1);
	BUTTON_TypeDef *pdata = &BUTTONs;
  private:
    BUTTON_TypeDef BUTTONs;
};
#endif

#endif

