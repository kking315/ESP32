#include "timer.h"
#include "led.h"
 
//TIM8_CH1 PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM8_PWM_Init(u16 arr,u16 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	RCC->APB2ENR|=1<<13; 	//TIM8ʱ��ʹ��  
  	 
	RCC->APB2ENR|=1<<4;    //ʹ��PORTCʱ��	 
	
	GPIOC->CRL&=0X00FFFFFF;	//PC67���֮ǰ������
	GPIOC->CRL|=0XBB000000;	//���ù������ 
	
	TIM8->ARR=arr;			//�趨�������Զ���װֵ 
	TIM8->PSC=psc;			//Ԥ��Ƶ������
  
	TIM8->CCMR1|=6<<4;  	//CH1 PWM2ģʽ		0110 0000 
	TIM8->CCMR1|=1<<3; 		//CH1Ԥװ��ʹ��	  ---- 1--- 0111 1000
 	TIM8->CCER|=1<<0;   	//OC1 ���ʹ��	    ---- ---1 

	TIM8->CCMR1|=6<<12;  	//CH2 PWM2ģʽ		0110 0000 
	TIM8->CCMR1|=1<<11; 		//CH2Ԥװ��ʹ��	  ---- 1--- 0111 1000
 	TIM8->CCER|=1<<4;   	//OC2 ���ʹ��	    ---- ---1 
	
  
	TIM8->CR1=0x0080;   	//ARPEʹ��
	TIM8->BDTR|=1<<15;      //�����ʹ�� 
	TIM8->CR1|=0x01;    	//ʹ�ܶ�ʱ��

}  


extern int t_miao;	//��
int jishu=0;
//��ʱ��3�жϷ������	 
void TIM3_IRQHandler(void)
{ 		    		  			    
	if(TIM3->SR&0X0001)//����ж�
	{
			jishu++;
			if(jishu>=2)	   //2��1s
			{
				jishu=0;				
				t_miao++;
			}
			
	}				   
	TIM3->SR&=~(1<<0);//����жϱ�־λ 	    
}
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM3_Int_Init(u16 arr,u16 psc)
{
	RCC->APB1ENR|=1<<1;	//TIM3ʱ��ʹ��    
 	TIM3->ARR=arr;  	//�趨�������Զ���װֵ 
	TIM3->PSC=psc;  	//Ԥ��Ƶ������
	TIM3->DIER|=1<<0;   //��������ж�				
	TIM3->CR1|=0x01;    //ʹ�ܶ�ʱ��3 TIM3->CR1|=0x01;
  MY_NVIC_Init(1,3,TIM3_IRQn,2);//��ռ1�������ȼ�3����2									 
}












