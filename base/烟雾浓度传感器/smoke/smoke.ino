#include <Arduino.h>

#define Sensor_AO 21
#define Sensor_DO 19

unsigned int sensorValue = 0;

void setup()
{
  pinMode(Sensor_DO, INPUT);
  Serial.begin(115200);
}

void loop()
{
  sensorValue = analogRead(Sensor_AO);
  Serial.print("Sensor AO Value = ");
  Serial.println(sensorValue);

  if (digitalRead(Sensor_DO) == LOW)
  {
    Serial.println("Alarm!");
  }
  delay(1000);
}
