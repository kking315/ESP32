#include "sys.h"   
#include "led.h"
 	   

//��ʼ��PA8Ϊ�����.��ʹ��	    
//LED IO��ʼ��
void LED_Init(void)
{
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��	
	JTAG_Set(JTAG_SWD_DISABLE);	//�ر�JTAG,SWD 
	
	GPIOA->CRH&=0XFFFFFFF0; 
	GPIOA->CRH|=0X00000003;//PA8 �������   	 
  GPIOA->ODR|=1<<8;      //PA8 �����
											  

}






