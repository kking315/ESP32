const int trigPin = 22;
const int echoPin = 23;
const int Led = 25;

void setup() {
  //设置超声波引脚为输入/输出
  pinMode(trigPin, OUTPUT);
  pinMode(Led, OUTPUT);
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
    digitalWrite(Led,LOW);
  }
  else if(distance < 10)
  {
    digitalWrite(Led,HIGH);
  }
  
  //输出物体的距离
  Serial.println(distance);

  delay(700);
}
