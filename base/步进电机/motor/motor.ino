const int a = 19;
const int b = 18;
const int c = 5;
const int d = 17;
 
void setup() {
  Serial.begin(115200);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
}
 
void digitalwrite_a_output(){
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    delayMicroseconds(2000);
}

void digitalwrite_b_output(){
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    delayMicroseconds(2000);
}

void digitalwrite_c_output(){
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    delayMicroseconds(2000);
}

void digitalwrite_d_output(){
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    delayMicroseconds(2000);
}

void digitalwrite_ab_output(){
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, LOW);
    delayMicroseconds(2000);
}

void digitalwrite_bc_output(){
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    delayMicroseconds(2000);
}

void digitalwrite_cd_output(){
    digitalWrite(a, LOW);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    delayMicroseconds(2000);
}

void digitalwrite_ad_output(){
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    delayMicroseconds(2000);
}

void loop() {
  Serial.println("Spinning Clockwise...");
  //四拍
  /*{
    digitalwrite_a_output();
    digitalwrite_b_output();
    digitalwrite_c_output();
    digitalwrite_d_output();
  }*/

  //反向四拍
  /*{
    digitalwrite_d_output();
    digitalwrite_c_output();
    digitalwrite_b_output();
    digitalwrite_a_output();
  }*/

  //双四拍
  /*{
    digitalwrite_ab_output();
    digitalwrite_bc_output();
    digitalwrite_cd_output();
    digitalwrite_ad_output();
  }*/

  //反向双四拍
  /*{
    digitalwrite_ad_output();
    digitalwrite_cd_output();
    digitalwrite_bc_output();
    digitalwrite_ab_output();
  }*/

  //八拍
  {
    digitalwrite_a_output();
    digitalwrite_ab_output();
    digitalwrite_b_output();
    digitalwrite_bc_output();
    digitalwrite_c_output();
    digitalwrite_cd_output();
    digitalwrite_d_output();
    digitalwrite_ad_output();
  }
}