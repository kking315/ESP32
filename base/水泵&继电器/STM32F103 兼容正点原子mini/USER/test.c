#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   //LED 

#include "oled.h" //OLED显示屏
#include "key.h"  //按键
#include "output.h"//输出设备接口


int main(void)
{			

	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72);	     //延时初始化
	uart_init(72,9600);  //串口初始化 
	
	KEY_Init(); //按键初始化
	DEVICE_Init();//设备初始化
		
	OLED_GPIO_Init();//显示屏初始化
  OLED_Init();//OLED初始化
  LED_Init();//LED初始化
	OLED_P16x16Ch(0,0,0);//显示汉字 测试例程
	OLED_P16x16Ch(16,0,1); 
  OLED_P16x16Ch(32,0,2); 
	OLED_P16x16Ch(48,0,3); 
	
	OLED_P8x16Str(64,0,"STM32F10"); //显示测试例程STM32F10
	OLED_P8x16Str(0,4,"DEV=0FF"); //显示关闭
  while(1)
	{
		
	  if(KEY1==0) //按键开
		{
			DEVICE=0;
			OLED_P8x16Str(0,4,"DEV=ON "); //显示开启
		}else if(KEY2==0) //按键关
		{
			DEVICE=1;
			OLED_P8x16Str(0,4,"DEV=0FF"); //显示关闭
		} 
		
	  delay_ms(200);
		LED0=!LED0; //LED闪烁提示
	}
	
}
		













