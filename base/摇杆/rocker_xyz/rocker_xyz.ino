#include<Arduino.h>

int sensorPin = 5;
 
int value = 0;
void setup() {
  pinMode(0, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(115200);
}
void loop() {
  value = analogRead(4);//x
  Serial.print("X:");
  Serial.print(value, DEC);
  value = analogRead(0);//y
  Serial.print(" | Y:");
  Serial.print(value, DEC);
  value = analogRead(2);//z
  Serial.print(" | Z: ");
  Serial.println(value, DEC);
  delay(100);
}