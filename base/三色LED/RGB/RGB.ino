int led1=14;//R
int led2=12;//G
int led3=13;//B
void setup() 
{
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
}
void setColor(int red,int green,int blue)
{
  analogWrite(led1,255-red);
  analogWrite(led2,255-green);
  analogWrite(led3,255-blue);
}
void loop() 
{
  setColor(255,255,255); //White
  delay(100);
  // setColor(255,0,0);  //Blue
  // delay(300);
  // setColor(255,255,0); //Depth Bule
  // delay(300);
  // setColor(0,255,0);  //Purple
  // delay(300);
  // setColor(0,255,255); //Red
  // delay(300);
  // setColor(0,0,255);  //Yellow
  // delay(300);
  // setColor(255,0,255); //Green
  // delay(300);
  for(int i=25;i>=0;i--){
    setColor(i*10,i*10,i*10);
    delay(50);
  }
  for(int i=0;i<25;i++){
    setColor(i*10,0,0);
    delay(50);
  }
  for(int i=0;i<25;i++){
    setColor(255,i*10,0);
    delay(50);
  }
  for(int i=25;i>=0;i--){
    setColor(i*10,255,0);
    delay(50);
  }
  for(int i=0;i<25;i++){
    setColor(0,255,i*10);
    delay(50);
  }
  for(int i=25;i>=0;i--){
    setColor(0,i*10,255);
    delay(50);
  }
  for(int i=0;i<25;i++){
    setColor(i*10,0,255);
    delay(50);
  }

 }
