unsigned char LED_0F [ ]={ 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8e,0xff,0xbf};  
// 共阳极的数码管的字模表 0	 1	 2	3	4  5	6	7	8	 9	  A	   b	C    d	  E    F    -    
unsigned char LED[4];	//用于LED的4位显示缓存
unsigned char LED_0F1[] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
// 0.   1.    2.    3.  4.  5.   6.    7.  8.  9.   
#define SCLK  17    //数据写入时钟
#define RCLK  18    //数据锁存显示时钟
#define DIO   19    //数据信号
#define pinX  27    //遥感x
#define buzzer 2
int value = 0;
unsigned long buzzerLastToggle = 0; // 用于记录蜂鸣器最后切换状态的时间


void setup ()
{
  pinMode(SCLK,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(DIO,OUTPUT); //让三个管脚都是输出状态
  pinMode(pinX,OUTPUT);
  pinMode(buzzer,OUTPUT);
  Serial.begin(115200);
}
void loop()
{
  value = analogRead(pinX);//x
  Serial.print("X:");
  Serial.println(value, DEC);
  value = 3.3*value/4095*1000;
  fmq();
  LED[0]=value/1000;
  LED[1]=value/100%10;
  LED[2]=value/10%10;
  LED[3]=value%10;
  LED4_Display (); 	   
}

void fmq() // 蜂鸣器报警，使用millis函数
{
  unsigned long currentMillis = millis(); // 获取当前时间

  // 检查是否到了切换蜂鸣器状态的时间点
  if (currentMillis - buzzerLastToggle >= 500) // 300毫秒为一个响铃周期
  {
    buzzerLastToggle = currentMillis; // 更新最后切换状态的时间
    Serial.printf("buzzerLastToggle:%d\n",buzzerLastToggle);

    // 切换蜂鸣器的状态
    if (value < 2000) {
      digitalWrite(buzzer, LOW); // 如果当前是高电平，即蜂鸣器关闭，就打开它
    } else {
      digitalWrite(buzzer, HIGH); // 如果当前是低电平，即蜂鸣器打开，就关闭它
    }
  }
}


void LED4_Display (void)
{
  unsigned char *led_table;          // 查表指针
  unsigned char i;
  //显示第1位
  led_table = LED_0F1 + LED[0];
  i = *led_table;
  LED_OUT(i);			
  LED_OUT(0x08); //0000 1000		
    digitalWrite(RCLK,LOW); // RCK是上升沿的时候数据锁存显示
    digitalWrite(RCLK,HIGH);
  //显示第2位
  led_table = LED_0F + LED[1];
  i = *led_table;
  LED_OUT(i);		
  LED_OUT(0x04);		
    digitalWrite(RCLK,LOW);
    digitalWrite(RCLK,HIGH);
  //显示第3位
  led_table = LED_0F + LED[2];
  i = *led_table;
  LED_OUT(i);			
  LED_OUT(0x02);	
    digitalWrite(RCLK,LOW);  
    digitalWrite(RCLK,HIGH);
  //显示第4位
  led_table = LED_0F + LED[3];
  i = *led_table;
  LED_OUT(i);			
  LED_OUT(0x01);		
    digitalWrite(RCLK,LOW);
    digitalWrite(RCLK,HIGH);
}    
void LED_OUT(unsigned char X)
{
  unsigned char i;
  for(i=8;i>=1;i--)
  {
    if (X&0x80)     //1000 0000
            {
              digitalWrite(DIO,HIGH);
              }  
            else 
            {
              digitalWrite(DIO,LOW);
            }
    X<<=1;
            digitalWrite(SCLK,LOW);
            digitalWrite(SCLK,HIGH);
  }
}
