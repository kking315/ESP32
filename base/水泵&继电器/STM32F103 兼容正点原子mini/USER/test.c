#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   //LED 

#include "oled.h" //OLED��ʾ��
#include "key.h"  //����
#include "output.h"//����豸�ӿ�


int main(void)
{			

	Stm32_Clock_Init(9); //ϵͳʱ������
	delay_init(72);	     //��ʱ��ʼ��
	uart_init(72,9600);  //���ڳ�ʼ�� 
	
	KEY_Init(); //������ʼ��
	DEVICE_Init();//�豸��ʼ��
		
	OLED_GPIO_Init();//��ʾ����ʼ��
  OLED_Init();//OLED��ʼ��
  LED_Init();//LED��ʼ��
	OLED_P16x16Ch(0,0,0);//��ʾ���� ��������
	OLED_P16x16Ch(16,0,1); 
  OLED_P16x16Ch(32,0,2); 
	OLED_P16x16Ch(48,0,3); 
	
	OLED_P8x16Str(64,0,"STM32F10"); //��ʾ��������STM32F10
	OLED_P8x16Str(0,4,"DEV=0FF"); //��ʾ�ر�
  while(1)
	{
		
	  if(KEY1==0) //������
		{
			DEVICE=0;
			OLED_P8x16Str(0,4,"DEV=ON "); //��ʾ����
		}else if(KEY2==0) //������
		{
			DEVICE=1;
			OLED_P8x16Str(0,4,"DEV=0FF"); //��ʾ�ر�
		} 
		
	  delay_ms(200);
		LED0=!LED0; //LED��˸��ʾ
	}
	
}
		













