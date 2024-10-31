#include <Arduino.h>
//定义蜂鸣器连接的GPIO口
#define BUZZER_PIN 23
void setup() {
  //设置BUZZER_PIN为输出模式
  pinMode(BUZZER_PIN,OUTPUT);}
void loop() {
  //发出蜂鸣声
  tone(BUZZER_PIN,1000);//发出1000Hz的频率
  delay(1000);//持续1秒钟
  noTone(BUZZER_PIN);//停止发声
  delay(1000);//延迟1秒钟
}
