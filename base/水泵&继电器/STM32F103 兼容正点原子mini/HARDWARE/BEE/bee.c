#include "sys.h"   
#include "bee.h"
 	    
//  IO初始化
void BEE_Init(void)
{
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟	    	 
	GPIOA->CRL&=0XFFFFFF0F; 
	GPIOA->CRL|=0X00000030;//PA1 推挽输出   	 
  GPIOA->ODR|=1<<1;      //PA1 输出高
											  
}






