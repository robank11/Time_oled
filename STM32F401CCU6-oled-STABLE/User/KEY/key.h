#ifndef _KEY_H
#define _KEY_H

#include "stm32f4xx.h"
#include "sys.h"


#define KEY0	PAin(0)
#define KEY1	PAin(2)
#define KEY2	PAin(3)
#define KEY3	PAin(4)


void KEY_Init(void);
uint8_t KEY_Scan(u8 mode);


#endif


