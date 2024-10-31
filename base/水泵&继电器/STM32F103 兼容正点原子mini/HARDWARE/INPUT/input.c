#include "input.h"
#include "delay.h"

//PA2 设置成输入
void FIRE_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟 
	JTAG_Set(JTAG_SWD_DISABLE);	//关闭JTAG,SWD 
	GPIOA->CRL&=0XFFFFF0FF;	//PA2设置成输入	  
	GPIOA->CRL|=0X00000800; 	
	
	GPIOA->ODR|=1<<2;	   	//PA2上拉
} 
 

















