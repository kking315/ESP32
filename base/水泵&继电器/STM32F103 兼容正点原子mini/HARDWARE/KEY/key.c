#include "key.h"
#include "delay.h"

 	    
//������ʼ������ 
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��
	JTAG_Set(JTAG_SWD_DISABLE);	//�ر�JTAG,SWD
	
	GPIOA->CRL&=0X000FFFFF;	//PA567���ó�����	  
	GPIOA->CRL|=0X88800000;   
	GPIOA->ODR|=1<<5;	   	//����
	GPIOA->ODR|=1<<6;	   	//����
	GPIOA->ODR|=1<<7;	   	//����
} 

















