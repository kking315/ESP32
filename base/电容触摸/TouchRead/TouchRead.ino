// ESP32 Touch Test
// Just test touch pin - Touch0 is T0 which is on GPIO 4.
int led1=14;//R
int led2=12;//G
int led3=13;//B
int ans = 0;
int ftx = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  delay(1000); // give me time to bring up serial monitor
  Serial.println("ESP32 Touch Test");
}

void setColor(int red,int green,int blue)
{
  analogWrite(led1,255-red);
  analogWrite(led2,255-green);
  analogWrite(led3,255-blue);
}

void loop()
{
  int tx = touchRead(T0);  // get value using T0
  int rx = touchRead(T2);
  Serial.printf("tx = %d\n",tx);
  Serial.printf("rx = %d\n",rx);
  
  if(tx < 15) ans = min(255,ans+50);
  if(rx < 15) ans = max(0,ans-50);
  setColor(ans,255,ans);
  delay(1000);

  /*
  if(tx < 15 && ftx > 15) ans = min(2,ans+1);
  if(rx < 15) ans = 0;

  if(ans == 1){
    setColor(0,255,0);  //Purple
    delay(500);
    setColor(255,255,255);
    delay(400);
  }
  else if(ans == 2){
    setColor(0,255,0);  //Purple
    delay(200);
    setColor(255,255,255);
  delay(100);
  }
  delay(100);
  ftx = tx;
  */

}
