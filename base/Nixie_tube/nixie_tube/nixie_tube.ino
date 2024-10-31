#define SCLK 23 //串行时钟引脚定义
#define RCLK 22 //接收时钟引脚定义
#define DIO 21 //数据引脚定义
int segCount=4;//4位数码管
//定义段码，这里是共阳段码，可以使用数码管段码软件改变数组值或者任意显示形状
const unsigned char dofly_DuanMa[]={// 0   1    2    3  4  5    6    7  8    9    A    b  C    d    E    F    -
                                0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x98,0x8C,0xBF,0xC6,0xA1,0x86,0x8E,0xbf};
//位码
int segPins[] = {0x08,0x04,0x02,0x01};   //对应数码管的编号即位码，从左往右为第1个数码管，第2个数码管、第3个数码管，第4个数码管  
unsigned char displayTemp[4];//显示缓冲区，存放4位要显示的段码
void setup() {
// 把对应的端口都设置成输出
  pinMode(SCLK,OUTPUT);
  pinMode(RCLK,OUTPUT);
  pinMode(DIO,OUTPUT);
}
// 数据处理，把需要处理的byte数据（段码）写到对应的端口SCLK。
void deal(unsigned char value){
  for(int i=7;i>=0;i--){
    digitalWrite(DIO,bitRead(value,i));//使用了bitWrite函数，非常简单
    // !bitRead(value,i)，这里前面加！(非运算符号)，取决于使用的是共阴还是共阳数码管。
    digitalWrite(SCLK,LOW);
    digitalWrite(SCLK,HIGH);
  }
  delay(100);
  Timedisp();
}
// 时钟中断调用的显示程序
//每中断一次，显示displayTemp[0]—displayTemp[3]中的一个（即静态变量i）段码值一次
void Timedisp() {
  static int i;
  deal(displayTemp[i]);//将对应的段码值写到对应的数码管
  deal(segPins[i]);//将对应的数码管编号（位码）的段码值写到DIO口
  digitalWrite(RCLK,LOW);//复位RCLK
  digitalWrite(RCLK,HIGH);//触发RCLK，即选择相应的编码号为i的数码管
  i++;
  if(i==segCount) //4位结束后重新循环
    i=0;
}
//显示程序，在4位数码中显示num，num小于10000
void disp(unsigned long num) {
  num=num%10000;//取模运算，防止num超过9999
  displayTemp[0]=dofly_DuanMa[num/1000];       //将num的个位数段码值送到显示缓存displayTemp[0]中
  displayTemp[1]=dofly_DuanMa[(num%1000)/100];    //将num的十位数段码值送到显示缓存displayTemp[1]中
  displayTemp[2]=dofly_DuanMa[((num%1000)%100)/10]; //将num的百位数段码值送到显示缓存displayTemp[2]中
  displayTemp[3]=dofly_DuanMa[((num%1000)%100)%10]; //将num的千位数段码值送到显示缓存displayTemp[3]中
}
// 主循环
void loop() {
    static unsigned int num;//定义一个数据
    disp(num);//显示累加值num
    num++;
    delay(100); //延时100ms
}
