#include "input.h"
#include "delay.h"

//PA2 ���ó�����
void FIRE_Init(void)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ�� 
	JTAG_Set(JTAG_SWD_DISABLE);	//�ر�JTAG,SWD 
	GPIOA->CRL&=0XFFFFF0FF;	//PA2���ó�����	  
	GPIOA->CRL|=0X00000800; 	
	
	GPIOA->ODR|=1<<2;	   	//PA2����
} 
 

















