#include "time.h"
#include "oled.h"
#include "rtc.h"
#include "dht11.h"
#include "delay.h"
#include "key.h"
#include "exti.h"
	
	
RTC_TimeTypeDef RTC_TimeStruct;
RTC_DateTypeDef RTC_DateStruct;
RTC_AlarmTypeDef RTC_AlarmStruct;



//显示时间日期
void DisplayTime(void)
{
	
	RTC_GetAlarm(RTC_Format_BIN,RTC_Alarm_A,&RTC_AlarmStruct);
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	OLED_ShowString(15,0,"--",16);
	OLED_ShowNum(31,0,RTC_TimeStruct.RTC_Hours,2,16);
	OLED_ShowChar(47,0,':',16);
	OLED_ShowNum(55,0,RTC_TimeStruct.RTC_Minutes,2,16);
	OLED_ShowChar(71,0,':',16);
	OLED_ShowNum(79,0,RTC_TimeStruct.RTC_Seconds,2,16);
	OLED_ShowString(95,0,"--",16);
	
	RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
	
	OLED_ShowNum(0,2,20,2,16);
	OLED_ShowNum(15,2,RTC_DateStruct.RTC_Year,2,16);
	OLED_ShowChar(31,2,'/',16);
	OLED_ShowNum(39,2,RTC_DateStruct.RTC_Month,2,16);
	OLED_ShowChar(55,2,'/',16);
	OLED_ShowNum(63,2,RTC_DateStruct.RTC_Date,2,16);
	
	OLED_ShowCHinese(87,2,0);
	switch(RTC_DateStruct.RTC_WeekDay)
	{
		case 1: OLED_ShowCHinese(103,2,1);
			break;
		case 2: OLED_ShowCHinese(103,2,2);
			break;
		case 3: OLED_ShowCHinese(103,2,3);
			break;
		case 4: OLED_ShowCHinese(103,2,4);
			break;
		case 5: OLED_ShowCHinese(103,2,5);
			break;
		case 6: OLED_ShowCHinese(103,2,6);
			break;
		case 7: OLED_ShowCHinese(103,2,7);
			break;
	}

}


//显示温湿度
void DisplayDht11(void)
{ extern u8 fsd;
	u8 temperature;  

	u8 humidity;
	
	DHT11_Read_Data(&temperature,&humidity);		//读取温湿度值					    
	
	OLED_ShowCHinese(0,4,8);
	OLED_ShowCHinese(15,4,9);
	OLED_ShowChar(31,4,':',16);
	OLED_ShowNum(39,4,temperature,2,16);
	OLED_ShowNum(62,4,fsd,2,16);
  OLED_ShowChar(55,4,'.',16);
	OLED_ShowChar(80,4,'o',12);
  OLED_ShowChar(88,4,'C',16);
//	OLED_ShowString(87,4,"^-^",16);
//	OLED_ShowString(78,4,"Author:",16);
	
	OLED_ShowCHinese(0,6,10);
	OLED_ShowCHinese(15,6,9);
	OLED_ShowChar(31,6,':',16);
	OLED_ShowNum(39,6,humidity,2,16);
	OLED_ShowChar(62,6,'%',16);
//	OLED_ShowString(87,6,">_<",16);
  OLED_ShowString(78,6,"PYX",16);
}


//界面显示
//ui,1-4对应界面2-5
void Display(u8 ui)
{

	switch (ui){
		case 1:  //帮助
		{
			OLED_ShowString(7,0,"**** HELP ****",16);
			OLED_ShowString(0,2,"K1:SET   K4:OK",16);
			OLED_ShowString(0,4,"K2:UP    K3:DOWN",16);
			OLED_ShowString(3,6,"PYX201202060116",16);
			
		}
			break;
		case 2: //设置时间
		{
			OLED_ShowCHinese(31,2,11);
			OLED_ShowCHinese(47,2,12);
			OLED_ShowCHinese(63,2,13);
			OLED_ShowCHinese(79,2,14);
			OLED_ShowNum(43,4,RTC_TimeStruct.RTC_Hours,2,16);
			OLED_ShowChar(59,4,':',16);
			OLED_ShowNum(67,4,RTC_TimeStruct.RTC_Minutes,2,16);
//			OLED_ShowString(68,6,"--",12);
//			OLED_ShowString(44,6,"--",12);
		}
			break;
		case 3: //设置日期
		{
			OLED_ShowCHinese(31,2,11);
			OLED_ShowCHinese(47,2,12);
			OLED_ShowCHinese(63,2,15);
			OLED_ShowCHinese(79,2,16);
			OLED_ShowString(23,4,"20",16);
			OLED_ShowNum(39,4,RTC_DateStruct.RTC_Year,2,16);
			OLED_ShowChar(55,4,'/',16);
			OLED_ShowNum(63,4,RTC_DateStruct.RTC_Month,2,16);
			OLED_ShowChar(79,4,'/',16);
			OLED_ShowNum(87,4,RTC_DateStruct.RTC_Date,2,16);
//			OLED_ShowString(24,6,"----",12);
//			OLED_ShowString(64,6,"--",12);
//			OLED_ShowString(88,6,"--",12);
		}
			break;
		case 4: //设置闹钟
		{
			OLED_ShowCHinese(31,2,11);
			OLED_ShowCHinese(47,2,12);
			OLED_ShowCHinese(63,2,17);
			OLED_ShowCHinese(79,2,18);
			OLED_ShowNum(43,4,RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours,2,16);
			OLED_ShowChar(59,4,':',16);
			OLED_ShowNum(67,4,RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes,2,16);
//			OLED_ShowString(68,6,"--",12);
//			OLED_ShowString(44,6,"--",12);
		}
			break;
	}
		
	
}







//设置时间
//不要问我下面这个函数是怎么实现的
//因为我也看不懂下面这段代码了
void SetTime(void)
{
	uint8_t set_hours,set_minutes,set_week;  //时间设置值
	uint8_t set_month,set_date;
	uint8_t alarm_hours,alarm_minutes;  //闹钟设置
	int set_year;
	u8 tab = 1;
	u8 key_count = 0;
	u8 set_flag = 0;
	
	
	if(set_key == 1 )
	{
		set_key = 0;
		ok_key = 0;
//		set_hours = RTC_TimeStruct.RTC_Hours;
//		set_minutes = RTC_TimeStruct.RTC_Minutes;
//		set_year = RTC_DateStruct.RTC_Year;
//		set_month = RTC_DateStruct.RTC_Month;
//		set_date = RTC_DateStruct.RTC_Date;
		
		OLED_Clear();
		while(1)
		{
//			alarm_hours = RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours;
//			alarm_minutes = RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes;

			if(set_flag == 0)
				Display(tab);
			else
			{
				switch (tab)
				{
					case 1:  //帮助
					{
						OLED_ShowString(7,0,"**** HELP ****",16);
						OLED_ShowString(0,2,"K1:SET   K4:OK",16);
						OLED_ShowString(0,4,"K2:UP    K3:DOWN",16);
						OLED_ShowString(3,6,"PYX201202060116",16);
						
					}
						break;
					case 2: //设置时间
					{
						OLED_ShowCHinese(31,2,11);
						OLED_ShowCHinese(47,2,12);
						OLED_ShowCHinese(63,2,13);
						OLED_ShowCHinese(79,2,14);
						OLED_ShowNum(43,4,RTC_TimeStruct.RTC_Hours,2,16);
						OLED_ShowChar(59,4,':',16);
						OLED_ShowNum(67,4,RTC_TimeStruct.RTC_Minutes,2,16);
						//			OLED_ShowString(68,6,"--",12);
						//			OLED_ShowString(44,6,"--",12);
					}
						break;
					case 3: //设置日期
					{
						OLED_ShowCHinese(31,2,11);
						OLED_ShowCHinese(47,2,12);
						OLED_ShowCHinese(63,2,15);
						OLED_ShowCHinese(79,2,16);
						OLED_ShowString(23,4,"20",16);
						OLED_ShowNum(39,4,RTC_DateStruct.RTC_Year,2,16);
						OLED_ShowChar(55,4,'/',16);
						OLED_ShowNum(63,4,RTC_DateStruct.RTC_Month,2,16);
						OLED_ShowChar(79,4,'/',16);
						OLED_ShowNum(87,4,RTC_DateStruct.RTC_Date,2,16);
						//			OLED_ShowString(24,6,"----",12);
						//			OLED_ShowString(64,6,"--",12);
						//			OLED_ShowString(88,6,"--",12);
					}
						break;
					case 4: //设置闹钟
					{
						OLED_ShowCHinese(31,2,11);
						OLED_ShowCHinese(47,2,12);
						OLED_ShowCHinese(63,2,17);
						OLED_ShowCHinese(79,2,18);
						OLED_ShowNum(43,4,RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours,2,16);
						OLED_ShowChar(59,4,':',16);
						OLED_ShowNum(67,4,RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes,2,16);
						//			OLED_ShowString(68,6,"--",12);
						//			OLED_ShowString(44,6,"--",12);
					}
						break;
				}
			}
			
			if(up_key == 1)
			{
				up_key = 0;
				tab++;
				OLED_Clear();
				if(tab == 5)
					tab = 1;
			}
			if(down_key == 1)
			{
				down_key = 0;
				tab--;
				OLED_Clear();
				if(tab == 0)
					tab = 4;
			}
			if(ok_key == 1)
			{
				ok_key = 0;
				OLED_Clear();
				break;
			}
			if(set_key == 1 && tab == 1)
					set_key = 0;
			if(set_key == 1 && tab != 1)
			{
				set_key = 0;
				ok_key = 0;
				set_flag = 0;
				key_count = 1;
				set_hours = RTC_TimeStruct.RTC_Hours;
				set_minutes = RTC_TimeStruct.RTC_Minutes;
				set_year = RTC_DateStruct.RTC_Year;
				set_month = RTC_DateStruct.RTC_Month;
				set_date = RTC_DateStruct.RTC_Date;
				alarm_hours = RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours;
				alarm_minutes = RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes;
				while(1)
				{
					
					
					switch (tab)
					{
						case 2:	//设置时间
						{
						
							OLED_ShowCHinese(31,2,11);
							OLED_ShowCHinese(47,2,12);
							OLED_ShowCHinese(63,2,13);
							OLED_ShowCHinese(79,2,14);
							OLED_ShowNum(43,4,set_hours,2,16);
							OLED_ShowChar(59,4,':',16);
							OLED_ShowNum(67,4,set_minutes,2,16);

							if(key_count == 1)
							{	
								OLED_ShowString(44,6,"  ",12);
								OLED_ShowString(68,6,"--",12);
							}
							if(key_count == 2)
							{
								OLED_ShowString(68,6,"  ",12);
								OLED_ShowString(44,6,"--",12);
							}
							if(up_key == 1)
							{
								up_key = 0;
								if(key_count == 1)
								{
									set_minutes++;
									if(set_minutes == 60)
										set_minutes = 0;
								}
								if(key_count == 2)
								{
									set_hours++;
									if(set_hours == 24)
										set_hours = 0;
								}
									
							}
							if(down_key == 1)
							{
								down_key = 0;
								if(key_count == 1)
								{
									set_minutes--;
									if(set_minutes == 0)
										set_minutes = 59;
								}
								if(key_count == 2)
								{
									set_hours--;
									if(set_hours == 0)
										set_hours = 23;
								}
							}
						}
							break;
						case 3:   //设置日期
						{
							OLED_ShowNum(39,4,set_year,2,16);
							OLED_ShowChar(55,4,'/',16);
							OLED_ShowNum(63,4,set_month,2,16);
							OLED_ShowChar(79,4,'/',16);
							OLED_ShowNum(87,4,set_date,2,16);
							if(key_count == 1)
							{
								OLED_ShowString(24,6,"----",12);
								OLED_ShowString(64,6,"  ",12);
								OLED_ShowString(88,6,"  ",12);
							}
							if(key_count == 2)
							{
								OLED_ShowString(24,6,"    ",12);
								OLED_ShowString(64,6,"--",12);
								OLED_ShowString(88,6,"  ",12);
							}
							if(key_count == 3)
							{
								OLED_ShowString(24,6,"    ",12);
								OLED_ShowString(64,6,"  ",12);
								OLED_ShowString(88,6,"--",12);
							}
							if(up_key == 1)
							{
								up_key = 0;
								if(key_count == 1)
								{
									set_year++;
									if(set_year == 99)
										set_year = 0;
								}
								if(key_count == 2)
								{
									set_month++;
									if(set_month == 13)
										set_month = 1;
								}		
								if(key_count == 3)
								{
									set_date++;
									if(((set_month==1||set_month ==3||set_month==5||set_month==7||set_month==8||set_month==10||set_month==12)
										&&(set_date == 32)) 
										||((set_month==4||set_month ==6||set_month==9||set_month==11)
										&&(set_date == 31)))
									{
										set_date = 1;
									}
									if(((set_year%4==0)&& 
										((set_year%100 != 0) ||(set_year%400==0)))
										&&(set_month == 2)&&(set_date == 30)
									||(((set_year%4!=0)|| 
										((set_year%100 == 0) &&(set_year%400!=0)))
										&&(set_month == 2)&&(set_date == 29)))
									{
										set_date = 1;
									}								
								}
							}
							
							if(down_key == 1)
							{
								down_key = 0;
								if(key_count == 1)
								{
									set_year--;
									if(set_year < 0)
										set_year = 99;
								}
								if(key_count == 2)
								{
									set_month--;
									if(set_month == 0)
										set_month = 12;
								}		
								if(key_count == 3)
								{
									set_date--;
									if(((set_month==1||set_month ==3||set_month==5||set_month==7||set_month==8||set_month==10||set_month==12))
										&&(set_date == 0)) //大月
										set_date = 31;
									if((set_month==4||set_month ==6||set_month==9||set_month==11)
										&&(set_date == 0)) //小月
										set_date = 30;
								
									if(((set_year%4==0)&& 
										((set_year%100 != 0) ||(set_year%400==0)))
										&&(set_month == 2)&&(set_date == 0)) //闰年
										set_date = 29;
									if(((set_year%4!=0)|| 
										((set_year%100 == 0) &&(set_year%400!=0)))
										&&(set_month == 2)&&(set_date == 0)) //平年
										set_date = 28;							
								}
							}
							
							
						}
							break;
						case 4:	//设置闹钟
						{
							OLED_ShowNum(43,4,alarm_hours,2,16);
							OLED_ShowChar(59,4,':',16);
							OLED_ShowNum(67,4,alarm_minutes,2,16);
							if(key_count == 1)
							{	
								OLED_ShowString(44,6,"  ",12);
								OLED_ShowString(68,6,"--",12);
							}
							if(key_count == 2)
							{
								OLED_ShowString(68,6,"  ",12);
								OLED_ShowString(44,6,"--",12);
							}
							
							if(up_key == 1)
							{
								up_key = 0;
								if(key_count == 1)
								{
									alarm_minutes++;
									if(alarm_minutes == 60)
										alarm_minutes = 0;
								}
								if(key_count == 2)
								{
									alarm_hours++;
									if(alarm_hours == 24)
										alarm_hours = 0;
								}
									
							}
							if(down_key == 1)
							{
								down_key = 0;
								if(key_count == 1)
								{
									alarm_minutes--;
									if(alarm_minutes == 0)
										alarm_minutes = 59;
								}
								if(key_count == 2)
								{
									alarm_hours--;
									if(alarm_hours == 0)
										alarm_hours = 23;
								}
							}
						}
							break;
						
					}
					
					
					if(set_key == 1)
					{
						set_key = 0;
						key_count++;
						if((tab == 2||tab == 4) && key_count == 3)
							key_count = 1;
						if(tab == 3 && key_count == 4)
							key_count = 1;
					}
					if(ok_key == 1 && set_key != 1)
					{
						ok_key = 0;
						set_flag = 1;
						OLED_Clear();
						set_week = ((set_date+2*set_month+3*(set_month+1)/5+set_year+set_year/4-set_year/100+set_year/400)%7)+1;
						
						if(set_hours != RTC_TimeStruct.RTC_Hours||set_minutes != RTC_TimeStruct.RTC_Minutes)
							RTC_Set_Time(set_hours,set_minutes,00,RTC_H12_AM);
						RTC_Set_Date(set_year,set_month,set_date,set_week);
						
						RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
						RTC_Set_AlarmA(RTC_DateStruct.RTC_WeekDay,alarm_hours,alarm_minutes,0);
						
						RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
						RTC_GetDate(RTC_Format_BIN, &RTC_DateStruct);
						RTC_GetAlarm(RTC_Format_BIN,RTC_Alarm_A,&RTC_AlarmStruct);
						break;
					}
				} //第二个while
			}
		}   //第一个while
	}
}










