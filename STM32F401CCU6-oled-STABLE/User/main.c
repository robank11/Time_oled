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

	
	//�����жϱ�־��ʼ��
	set_key = 0;
	up_key = 0;
	down_key = 0;
	ok_key = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(84);
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();
	OLED_Init();
	DHT11_Init();	//DHT11��ʼ��	
	My_RTC_Init();		 		//��ʼ��RTC
	RTC_Set_WakeUp(RTC_WakeUpClock_CK_SPRE_16bits,0);		//����WAKE UP�ж�,1�����ж�һ��
	EXTIX_Init();
	

	while(1)
	{
		DisplayTime();
		if(t%10==0)//ÿ100ms��ȡһ��
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




