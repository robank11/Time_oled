#ifndef _LED_H
#define _LED_H

#include "sys.h"

#define LED0 PBout(12)
#define LED1 PBout(10)
#define LED2 PBout(12)
#define LED3 PBout(12)
#define BEEP PBout(6)

void LED_Init(void);


#endif




