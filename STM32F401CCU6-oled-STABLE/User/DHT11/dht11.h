#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   




//IO��������
#define DHT11_IO_IN()  {GPIOB->MODER&=~(3<<(1*2));GPIOB->MODER|=0<<1*2;}	//PG9����ģʽ
#define DHT11_IO_OUT() {GPIOB->MODER&=~(3<<(1*2));GPIOB->MODER|=1<<1*2;} 	//PG9���ģʽ 
////IO��������											   
#define	DHT11_DQ_OUT PBout(1) //���ݶ˿�	PG9 
#define	DHT11_DQ_IN  PBin(1)  //���ݶ˿�	PG9 

u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11    
#endif














