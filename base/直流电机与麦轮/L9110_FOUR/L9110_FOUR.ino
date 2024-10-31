#include <Arduino.h>
#define INA1 12
#define INA2 13
#define INB1 14
#define INB2 27
#define INC1 25
#define INC2 26
#define IND1 33
#define IND2 32
 
void initMotor();
void stop();
void forward();

void setup()
{
  Serial.begin(115200);
  initMotor();
}
 
void loop()
{
  forward();
  delay(1000);
  stop();
  delay(1000);
}

void initMotor(){
  pinMode(INA1,OUTPUT);
  pinMode(INA2,OUTPUT);

  pinMode(INB1,OUTPUT);
  pinMode(INB2,OUTPUT);

  pinMode(INC1,OUTPUT);
  pinMode(INC2,OUTPUT);

  pinMode(IND1,OUTPUT);
  pinMode(IND2,OUTPUT);
}

void forward(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,HIGH);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,HIGH);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,HIGH);
}

void stop(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,LOW);
}
