unsigned char LED_0F[] =     { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xFF, 0xbf};	  // 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
unsigned char LED[4];	//用于LED的4位显示缓存
int SCLK = 16;//数据写入脉冲
int RCLK = 4; //数据锁存脉冲
int DIO = 0; //数据输入
int buttonPin1 = 12, buttonPin2 = 14;  
volatile int num1 = 0, num2 = 0;
bool flag1 = false, flag2 = false;  
void count();
void LED4_Display ();
void setup ()
{
  Serial.begin(115200);
  pinMode(SCLK,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(DIO,OUTPUT); //让三个脚都是输出状态
  pinMode(buttonPin1,INPUT_PULLUP);
  pinMode(buttonPin2,INPUT_PULLUP);
  attachInterrupt(buttonPin1,count1,FALLING);
  attachInterrupt(buttonPin2,count2,FALLING);
}
void loop()
{
  LED4_Display (); 
  if(flag1){
    delay(10);
    if(flag1){
        num1++;
        Serial.println(num1);
        if(num1>100) num1=0;
    }          
  }
  flag1 = false;  
  if(flag2){
    delay(10);
    if(flag2){
        num2++;
        Serial.println(num2);
        if(num2>100) num2=0;
    }          
  }
  flag2 = false;    
  LED[0]=num1/10;
  LED[1]=num1%10; 
  LED[2]=num2/10;
  LED[3]=num2%10;
}

void count1()
{
  flag1=true;      
}

void count2()
{
  flag2=true;      
}

void LED4_Display ()
{
  unsigned char *led_table;          // 查表指针
  unsigned char i;
  //显示第1位
  led_table = LED_0F + LED[0];
  i = *led_table;
  LED_OUT(i);			
  LED_OUT(0x08);		
    digitalWrite(RCLK,LOW);
    digitalWrite(RCLK,HIGH);
    delay(5);
  //显示第2位
  led_table = LED_0F + LED[1];
  i = *led_table;
  LED_OUT(i);		
  LED_OUT(0x04);		
    digitalWrite(RCLK,LOW);
    digitalWrite(RCLK,HIGH);
    delay(5);
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
//74HC595的串行传输是从最高位开始，依次到最低位
void LED_OUT(unsigned char X)
{
  unsigned char i;
  for(i=8;i>=1;i--)
  {
    if (X&0x80)   //取出最高位
    {
      digitalWrite(DIO,HIGH);
      }  
    else 
    {
      digitalWrite(DIO,LOW);
    }
    X<<=1;  //左移一位，让次高位来到最高位
    digitalWrite(SCLK,LOW);  //SCK是上升沿的时候要把数据写入
    digitalWrite(SCLK,HIGH);
  }
}