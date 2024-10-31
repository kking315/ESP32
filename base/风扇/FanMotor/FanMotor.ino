#define FanPinA 22
#define FanPinB 23

void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);
}

void loop() {
  //正转
  analogWrite(FanPinA,100);
  analogWrite(FanPinB,0);
  delay(500);
  //停
  analogWrite(FanPinA,0);
  analogWrite(FanPinB,0);
  delay(1000);
}
