unsigned char LED_0F [ ]={ 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8e,0xff,0xbf};  
// 共阳极的数码管的字模表 0	 1	 2	3	4  5	6	7	8	 9	  A	   b	C    d	  E    F    -    
unsigned char LED[4];	//用于LED的4位显示缓存
unsigned char LED_0F1[] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
// 0.   1.    2.    3.  4.  5.   6.    7.  8.  9.   
#define SCLK  17    //数据写入时钟
#define RCLK  18    //数据锁存显示时钟
#define DIO   19    //数据信号
void setup ()
{
  pinMode(SCLK,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(DIO,OUTPUT); //让三个管脚都是输出状态
}
void loop()
{
  LED[0]=1;
  LED[1]=2;
  LED[2]=3;
  LED[3]=4;
  LED4_Display ();    	   
}

void LED4_Display (void)
{
  unsigned char *led_table;          // 查表指针
  unsigned char i;
  //显示第1位
  led_table = LED_0F + LED[0];
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
