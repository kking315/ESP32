#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
   

//ͨ���ı�TIM8->CCR1��ֵ���ı�ռ�ձȣ��Ӷ�����LED0������
#define PWM1_VAL TIM8->CCR1    //2·PWM����С���˶� 
#define PWM2_VAL TIM8->CCR2  

void TIM8_PWM_Init(u16 arr,u16 psc);//��ʱ��8 ��ʼ��
void TIM3_Int_Init(u16 arr,u16 psc);
#endif























