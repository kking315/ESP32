#define INA1 13//左后
#define INA2 12
#define INB1 27//左前
#define INB2 14
#define INC1 26//右前
#define INC2 25
#define IND1 32//右后
#define IND2 33

void initMotor(){
  pinMode(INA1,OUTPUT);
  pinMode(INA2,OUTPUT);

  pinMode(INB1,OUTPUT);
  pinMode(INB2,OUTPUT);

  pinMode(INC1,OUTPUT);
  pinMode(INC2,OUTPUT);

  pinMode(IND1,OUTPUT);
  pinMode(IND2,OUTPUT);
}

void stop(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,LOW);
}

void back(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,HIGH);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,HIGH);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,HIGH);
}

void forward(){
  digitalWrite(INA1,HIGH);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,HIGH);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,HIGH);
  digitalWrite(IND2,LOW);
}

void left(){
  digitalWrite(INA1,HIGH);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,HIGH);
  digitalWrite(INC1,HIGH);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,HIGH);
}

void right(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,HIGH);
  digitalWrite(IND1,HIGH);
  digitalWrite(IND2,LOW);
}

void circle(){
  digitalWrite(INA1,HIGH);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,HIGH);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,HIGH);
}

void rightBack(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,HIGH);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,HIGH);
}

void rightFront(){
  digitalWrite(INA1,HIGH);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,HIGH);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,LOW);
}

void leftBack(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,HIGH);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,LOW);
}

void leftFront(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,HIGH);
  digitalWrite(IND2,LOW);
}
