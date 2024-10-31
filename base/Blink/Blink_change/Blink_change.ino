int LED_BUILTIN[] = {5,17,16,4,0};
//Blink_key按键控制小灯
#define pushButton 13

int flag = true;
int ans = 1;
int change = 0;
int flagState = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (115200);
  pinMode(pushButton, INPUT_PULLUP);
  for(int i=0;i<5;i++)
    pinMode(LED_BUILTIN[i], OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(pushButton);
  Serial.print ("buttonState:");
  Serial.println (buttonState);
  Serial.print ("flag:");
  Serial.println (flag);
  //解决按键切换与控制的冲突
  if(ans >= 20){//超过两秒清零
    ans = 0;
    change = 0;
  }
  if(flagState != buttonState){
    if(change == 0)//第一次改变
      ans = 0;
    change++;
    if(change > 3){
      if(flag == 0) flag = 1;
      else if(flag == 1) flag = 2;
      else flag = 0;
      ans = 0;
      change = 0;
    }
  }
  Serial.print ("ans:");
  Serial.println (ans);
  Serial.print ("change:");
  Serial.println (change);
  Serial.print ("flagState:");
  Serial.println (flagState);
  if(flag == 2){
    if(buttonState) 
      for(int i=0;i<5;i++)
        digitalWrite(LED_BUILTIN[i], LOW);
    else 
      for(int i=0;i<5;i++)
        digitalWrite(LED_BUILTIN[i], HIGH);
  }
  else if(flag == 1){
    for(int i=0;i<5;i++){
      digitalWrite(LED_BUILTIN[i], HIGH); 
      digitalWrite(LED_BUILTIN[(i+2)%5], HIGH); 
      delay(300);                     
      digitalWrite(LED_BUILTIN[i], LOW);  
      digitalWrite(LED_BUILTIN[(i+2)%5], LOW);
      //delay(100);                      
    }
  }
  else{
    for(int i=0;i<5;i++){
      digitalWrite(LED_BUILTIN[i], HIGH);  
      delay(100);                     
      digitalWrite(LED_BUILTIN[i], LOW);  
      //delay(100);                      
    }
  }
  flagState = buttonState;
  ans++;
  delay(100);
}
