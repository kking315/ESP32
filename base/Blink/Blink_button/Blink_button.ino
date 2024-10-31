//Blink_key按键控制小灯
#define pushButton 13//引脚与导线对角线放置
//按键控制小灯亮灭
#define ledPin1 5
void setup(){
  Serial.begin (115200);
  pinMode(pushButton, INPUT_PULLUP);
  pinMode(ledPin1, OUTPUT);
}
void loop() {
  int buttonState = digitalRead(pushButton);
  Serial.println (buttonState);
  delay (100) ;
  if(buttonState) digitalWrite(ledPin1,LOW);
  else digitalWrite (ledPin1,HIGH);
}
