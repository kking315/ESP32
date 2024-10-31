#include "key.h"
#include "delay.h"

 	    
//按键初始化函数 
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟
	JTAG_Set(JTAG_SWD_DISABLE);	//关闭JTAG,SWD
	
	GPIOA->CRL&=0X000FFFFF;	//PA567设置成输入	  
	GPIOA->CRL|=0X88800000;   
	GPIOA->ODR|=1<<5;	   	//上拉
	GPIOA->ODR|=1<<6;	   	//上拉
	GPIOA->ODR|=1<<7;	   	//上拉
} 

















