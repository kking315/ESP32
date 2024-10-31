#include<Arduino.h>
int sensorPin = 5;
int freq_PWM = 50;
int res_PWM = 10;
int channel_PWM_A = 8;
int channel_PWM_B = 9;
int channel_PWM_C = 11;
int channel_PWM_D = 12;
const int  PWM_PIN_A = 13;//右前
const int  PWM_PIN_B = 12;//右后
const int  PWM_PIN_C = 14;//左前
const int  PWM_PIN_D = 27;//左后
const int  wait = 200;

int calculatePWM(int degree) //定义函数用于输出PWM的占空比
{ //0-180度
 //20ms周期内，高电平持续时长0.5-2.5ms，对应0-180度舵机角度，参考上面的180度对应图。
  const float deadZone = 25.6;//对应0.5ms（0.5ms/(20ms/1024）)
  const float max = 128;//对应2.5ms（2.5ms/（20ms/256））
  if (degree < 0)
    degree = 0;
  if (degree > 180)
    degree = 180;
  return (int)(((max - deadZone) / 180) * degree + deadZone); //返回度数对应的高电平的数值
}

void init_PWM(){
  ledcWrite(channel_PWM_A,calculatePWM(90));
  ledcWrite(channel_PWM_B,calculatePWM(90));
  ledcWrite(channel_PWM_C,calculatePWM(90));
  ledcWrite(channel_PWM_D,calculatePWM(90));
}

void A145(){ledcWrite(channel_PWM_A,calculatePWM(145));}
void A130(){ledcWrite(channel_PWM_A,calculatePWM(130));}
void A110(){ledcWrite(channel_PWM_A,calculatePWM(110));}
void A90(){ledcWrite(channel_PWM_A,calculatePWM(90));}
void A50(){ledcWrite(channel_PWM_A,calculatePWM(50));}
void B130(){ledcWrite(channel_PWM_B,calculatePWM(130));}
void B90(){ledcWrite(channel_PWM_B,calculatePWM(90));}
void B50(){ledcWrite(channel_PWM_B,calculatePWM(50));}
void C130(){ledcWrite(channel_PWM_C,calculatePWM(130));}
void C90(){ledcWrite(channel_PWM_C,calculatePWM(90));}
void C50(){ledcWrite(channel_PWM_C,calculatePWM(50));}
void D130(){ledcWrite(channel_PWM_D,calculatePWM(130));}
void D90(){ledcWrite(channel_PWM_D,calculatePWM(90));}
void D50(){ledcWrite(channel_PWM_D,calculatePWM(50));}

void forward(){
  A130();D50();delay(wait);
  B50();C130();delay(wait);
  A90();D90();delay(wait);
  B90();C90();delay(wait);

  B130();C50();delay(wait);
  A50();D130();delay(wait);
  B90();C90();delay(wait);
  A90();D90();delay(wait);
}

void backward(){
  A50();D130();delay(wait);
  B130();C50();delay(wait);
  A90();D90();delay(wait);
  B90();C90();delay(wait);

  B50();C130();delay(wait);
  A130();D50();delay(wait);
  B90();C90();delay(wait);
  A90();D90();delay(wait);
}

void right(){
  A130();D130();delay(wait);
  B50();C50();delay(wait);
  A90();D90();delay(wait);
  B90();C90();delay(wait);
}

void left(){
  A50();D50();delay(wait);
  B130();C130();delay(wait);
  A90();D90();delay(wait);
  B90();C90();delay(wait);
}

void swing(){
  A130();B130();C50();D50();delay(wait);
  A90();B90();C90();D90();delay(wait);
  A50();B50();C130();D130();delay(wait);
  A90();B90();C90();D90();delay(wait);
}

void hello(){
  A110();delay(wait);
  A90();delay(wait);
  A145();delay(wait);
  A90();delay(wait);
  A145();delay(wait);
}

int value_x, value_y, value_z;
void setup() {
  ledcSetup(channel_PWM_A,freq_PWM,res_PWM);  //设置通道
  ledcAttachPin(PWM_PIN_A,channel_PWM_A);  //将引脚绑定到通道上
  ledcSetup(channel_PWM_B,freq_PWM,res_PWM);  //设置通道
  ledcAttachPin(PWM_PIN_B,channel_PWM_B);  //将引脚绑定到通道上
  ledcSetup(channel_PWM_C,freq_PWM,res_PWM);  //设置通道
  ledcAttachPin(PWM_PIN_C,channel_PWM_C);  //将引脚绑定到通道上
  ledcSetup(channel_PWM_D,freq_PWM,res_PWM);  //设置通道
  ledcAttachPin(PWM_PIN_D,channel_PWM_D);  //将引脚绑定到通道上
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
  if(value_z == 0){ hello();  }
  else if(value_y>3000){  left(); }
  else if(value_y<2800){  right();  }
  else if(value_x<1750){  forward();  }
  else if(value_x>1950){  backward(); }
  else{ A90();B90();C90();D90();  }
  delay(wait);
}