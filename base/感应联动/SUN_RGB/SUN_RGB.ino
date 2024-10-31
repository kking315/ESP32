#include <Arduino.h>

#define Sensor_AO 27
int led1=14;//R
int led2=12;//G
int led3=13;//B

unsigned int sensorValue = 0;

void setup()
{
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  Serial.begin(115200);
}

void setColor(int red,int green,int blue)
{
  analogWrite(led1,255-red);
  analogWrite(led2,255-green);
  analogWrite(led3,255-blue);
}

void loop()
{
  sensorValue = analogRead(Sensor_AO);
  Serial.print("Sensor AO Value = ");
  Serial.println(sensorValue);
  if(sensorValue<1500){
    setColor(255,0,255); //Green
  }
  else{
    setColor(0,255,255); //Red
  }

  delay(200);
}
