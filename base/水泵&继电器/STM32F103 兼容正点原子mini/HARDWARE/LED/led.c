#include "sys.h"   
#include "led.h"
 	   

//初始化PA8为输出口.并使能	    
//LED IO初始化
void LED_Init(void)
{
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟	
	JTAG_Set(JTAG_SWD_DISABLE);	//关闭JTAG,SWD 
	
	GPIOA->CRH&=0XFFFFFFF0; 
	GPIOA->CRH|=0X00000003;//PA8 推挽输出   	 
  GPIOA->ODR|=1<<8;      //PA8 输出高
											  

}






