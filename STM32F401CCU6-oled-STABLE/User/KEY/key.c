#include "key.h"
#include "delay.h"

/**
  * @brief  按键初始化
  * @param  None
  * @retval None
  */
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  //速度
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //输入模式
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//上拉
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}


//mode:0,不支持连续按;1,支持连续按;
//按键扫描
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!

uint8_t KEY_Scan(u8 mode)
{
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
		else if(KEY2==0)return 3;
		else if(KEY3==0)return 4;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
 	return 0;// 无按键按下
}



