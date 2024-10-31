#include <Arduino.h> 
const int trigPin = 22;
const int echoPin = 23;
int channel_PWM = 8;  //使用3号通道 定时器1  总共16个通道 
// 舵机频率，那么周期也就是1/50，也就是20ms ，PWM⼀共有16个通道，0-7位⾼速通道由80Mhz时钟驱动，后⾯8个为低速通道由1Mhz
int freq_PWM = 50;  //50HZ pwm波
// PWM分辨率，取值为 0-20 之间  ，这⾥填写为10，那么后⾯的ledcWrite 这个⾥⾯填写的pwm值就在 0 - 2的10次⽅ 之间 也就是 0-1024，如果是要求不⾼的东西你可以直接拿1000去算了
int res_PWM = 10;  //分辨率  0-1024  共1025
const int  PWM_PIN = 18; //使用18号引脚

void setup() {
  ledcSetup(channel_PWM,freq_PWM,res_PWM);  //设置通道
  ledcAttachPin(PWM_PIN,channel_PWM);  //将引脚绑定到通道上
  //设置超声波引脚为输入/输出
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
}

void loop() {
  //发出超声波脉冲
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //计算超声波回波的时间
  long duration = pulseIn(echoPin, HIGH);
  
  //计算物体的距离
  long distance = duration * 0.034 / 2;

  if(distance >= 10)
  {
    ledcWrite(channel_PWM,26); //20ms⾼电平为0.5ms左右 ，也就是0.5/20*1024 = 26，此时180度舵机角度为0°
  }
  else if(distance < 10)
  {
    ledcWrite(channel_PWM, 77); //20ms⾼电平为1.5ms左右 ，也就是1.5/20*1024 = 77，此时180度舵机角度为90°
  }
  Serial.println(distance);
  delay(500);
} 
