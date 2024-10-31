#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
   

//通过改变TIM8->CCR1的值来改变占空比，从而控制LED0的亮度
#define PWM1_VAL TIM8->CCR1    //2路PWM控制小车运动 
#define PWM2_VAL TIM8->CCR2  

void TIM8_PWM_Init(u16 arr,u16 psc);//定时器8 初始化
void TIM3_Int_Init(u16 arr,u16 psc);
#endif























