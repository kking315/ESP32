#include "output.h"
#include "delay.h"

//PD2 ���ó����
void DEVICE_Init(void)
{ 	 
	RCC->APB2ENR|=1<<5;    //ʹ��PORTDʱ��	   	 									  
	GPIOD->CRL&=0XFFFFF0FF;
	GPIOD->CRL|=0X00000300;//PD.2�������
	GPIOD->ODR|=1<<2;      //PD.2�����
} 
 

















