#ifndef _TIME_H
#define _TIME_H

#include "sys.h"

extern u8 set_key,up_key,down_key,ok_key,alarm_flag;;


void DisplayTime(void);
void DisplayDht11(void);
void SetTime(void);
void Display(u8 ui);


#endif


