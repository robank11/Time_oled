#include "key.h"
#include "delay.h"

/**
  * @brief  ������ʼ��
  * @param  None
  * @retval None
  */
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //����ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;  //�ٶ�
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//����
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;  //����ģʽ
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	//����
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}


//mode:0,��֧��������;1,֧��������;
//����ɨ��
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!

uint8_t KEY_Scan(u8 mode)
{
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
		else if(KEY2==0)return 3;
		else if(KEY3==0)return 4;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1)key_up=1; 	    
 	return 0;// �ް�������
}



