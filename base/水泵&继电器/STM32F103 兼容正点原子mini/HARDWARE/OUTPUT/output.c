#include "output.h"
#include "delay.h"

//PD2 设置成输出
void DEVICE_Init(void)
{ 	 
	RCC->APB2ENR|=1<<5;    //使能PORTD时钟	   	 									  
	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X00000300;//PD.2推挽输出
	GPIOD->ODR|=1<<2;      //PD.2输出高
} 
 

















