#include "sys.h"   
#include "bee.h"
 	    
//  IO��ʼ��
void BEE_Init(void)
{
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��	    	 
	GPIOA->CRL&=0XFFFFFF0F; 
	GPIOA->CRL|=0X00000030;//PA1 �������   	 
  GPIOA->ODR|=1<<1;      //PA1 �����
											  
}






