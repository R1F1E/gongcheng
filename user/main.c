#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "OLED.h"
#include "DS18B20.h"
#include "FMQ.h"
#include "Serial.h"

int main(void)
{
	 
	 OLED_Init();
	 DS18B20_Init();
	 mfq_Init();
	 Serial_Init();
	 uint16_t Temp;
	
	OLED_ShowString(36,0,"DS18B20",OLED_8X16);
	OLED_ShowString(50,16,"+",OLED_8X16);
	OLED_ShowChinese(0, 16, "温度：");
	OLED_ShowChinese(100, 16, "℃");
	OLED_Update();

	while(1)
	{
		if(DS18B20_Reset()==0)
		{
			Temp = DS18B20_ReadTemp();

				OLED_ClearArea(0,47,128,15);
				OLED_ShowString(84,16,".",OLED_8X16);
				OLED_ShowNum(60,16,Temp/10%100,3,OLED_8X16);
				OLED_ShowNum(87,16,Temp%10,1,OLED_8X16);
				OLED_Update();
				fmq(Temp/10%100);
		
		}
		else
		{
			OLED_ClearArea(0,47,128,15);
			OLED_ShowString(0,47,"No   sensor  ",OLED_8X16);
			OLED_Update();
			printf("DS18B20断开连接！！！");
		}
		
		 //fmq(Temp);
		 printf("温度= +%d.%d ℃\r\n",Temp/10%100,Temp%10);

	}
}
