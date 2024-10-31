#include <Arduino.h>
int PWM = 0;
int INA = 12;
int INB = 27;
 
void setup()
{
  Serial.begin(115200);
  pinMode(INA,OUTPUT);
  pinMode(INB,OUTPUT);
}
 
void loop()
{
  /*
    int analogReadVal = analogRead(A0);
    int PWM = map(analogReadVal,0,1023,0,255);
    //模拟数字信号版
    //正转 200+
    for(int i=25;i>=0;i--){
      Serial.println(i);
      analogWrite(INA, 0);
      analogWrite(INB, i*10);
      delay(300);
    }
    //反转 200+
    for(int i=0;i<=25;i++){
      Serial.println(i);
      analogWrite(INA, i*10);
      analogWrite(INB, 0);
      delay(300);
    }
    //停止
    analogWrite(INA, 0);
    analogWrite(INB, 0);
    delay(1000);
    */
    analogWrite(PWM, 60);
    digitalWrite(INA,LOW);
    digitalWrite(INB,HIGH);
    delay(1000);
    digitalWrite(INA,LOW);
    digitalWrite(INB,LOW);
    delay(1000);
}
