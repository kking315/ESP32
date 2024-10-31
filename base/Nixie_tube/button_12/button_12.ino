unsigned char LED_0F[] =     { 0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,0xFF, 0xbf};	  // 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
unsigned char LED[4];	//用于LED的4位显示缓存
int SCLK = 17;//数据写入脉冲
int RCLK = 18; //数据锁存脉冲
int DIO = 19; //数据输入
int buttonPin = 12;  
volatile int num = 0;
bool flag = false;  
void count();
void LED4_Display ();
void setup ()
{
  Serial.begin(115200);
  pinMode(SCLK,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(DIO,OUTPUT); //让三个脚都是输出状态
  pinMode(buttonPin,INPUT_PULLUP);
  attachInterrupt(buttonPin,count,FALLING);
}
void loop()
{
  LED4_Display (); 
  if(flag){
    delay(10);
    if(flag){
        num++;
        Serial.println(num);
        if(num>100) num=0;
    }          
  }
  flag = false;      
  LED[0]=num/10;
  LED[1]=num%10;
}

void count()
{
  flag=true;      
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