#include<Arduino.h>
int sensorPin = 5;
int freq_PWM = 50;
int res_PWM = 10;
int channel_PWM_r1 = 8;
int channel_PWM_r2 = 9;
const int  PWM_PIN_r1 = 13;
const int  PWM_PIN_r2 = 12;

int value_x, value_y, value_z;
void setup() {
  ledcSetup(channel_PWM_r1,freq_PWM,res_PWM);  //设置通道
  ledcAttachPin(PWM_PIN_r1,channel_PWM_r1);  //将引脚绑定到通道上
  ledcSetup(channel_PWM_r2,freq_PWM,res_PWM);  //设置通道
  ledcAttachPin(PWM_PIN_r2,channel_PWM_r2);  //将引脚绑定到通道上
  pinMode(0, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);
}
void loop() {
  //max = 4095
  value_x = analogRead(4);//x = 1880
  Serial.print("X:");
  Serial.print(value_x, DEC);
  value_y = analogRead(0);//y = 2940
  Serial.print(" | Y:");
  Serial.print(value_y, DEC);
  value_z = analogRead(2);//z = 1100
  Serial.print(" | Z: ");
  Serial.println(value_z, DEC);
  if(value_x<1750){
    ledcWrite(channel_PWM_r1,65-(1880-value_x)/64);
    ledcWrite(channel_PWM_r2,90+(1880-value_x)/64);
  }else if(value_x>1950){
    ledcWrite(channel_PWM_r1,90+(value_x-1880)/74);
    ledcWrite(channel_PWM_r2,65-(value_x-1880)/74);
  }else{
    ledcWrite(channel_PWM_r1,77);
    ledcWrite(channel_PWM_r2,77);
  }
  delay(100);
}