#include "opti.h"
#include "delay.h"
   
//PA2 设置成输入
void OPTI_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟 
	JTAG_Set(SWD_ENABLE);	//关闭JTAG,开启SWD 
	GPIOA->CRL&=0XFFFFF0FF;	//PA2设置成输入	  
	GPIOA->CRL|=0X00000800; 	
	GPIOA->ODR|=1<<2;	   	//PA2上拉
} 
 

















