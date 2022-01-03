#include "led.h"
#include "delay.h"
#include "oled.h"
#include "usart.h"
#include "dht11.h"
#include "rtc.h"
#include "time.h"
#include "exti.h"

u8 t;

int main(void)
{ 

	
	//按键中断标志初始化
	set_key = 0;
	up_key = 0;
	down_key = 0;
	ok_key = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(84);
	uart_init(115200);		//初始化串口波特率为115200
	LED_Init();
	OLED_Init();
	DHT11_Init();	//DHT11初始化	
	My_RTC_Init();		 		//初始化RTC
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//配置WAKE UP中断,1秒钟中断一次
	EXTIX_Init();
	

	while(1)
	{
		DisplayTime();
		if(t%10==0)//每100ms读取一次
		{	
			
			DisplayDht11();
			LED0=!LED0;
		}				   
	 	delay_ms(10);
		SetTime();
		t++;
		if(alarm_flag == 1)
		{
			LED3 = 0;
			BEEP = 1;
			delay_ms(500);
			LED3 = 1;
			BEEP = 0;
			alarm_flag = 0;
//		printf("ALARM A!\r\n");
		}
		if(t==20)
		{
			t=0;
		}
		
	}
}




