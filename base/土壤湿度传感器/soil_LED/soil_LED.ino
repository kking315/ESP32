int ASignal = 0;//传感器引脚
int LEDPin = 13;//LED引脚
int val = 900;//接收信号映射值上限
void setup(){
  pinMode(LEDPin, OUTPUT);
  pinMode(ASignal, INPUT);
  digitalWrite(LEDPin,LOW);
  Serial.begin(115200);
}

void loop(){
  int sensorValue = analogRead(ASignal); 
  if(analogRead(ASignal)> val){
    digitalWrite(LEDPin, HIGH);
    delay(300);
    digitalWrite(LEDPin, LOW);
    delay(300);
  }
  else{
    digitalWrite(LEDPin,LOW);
    delay(1000);
  }
}