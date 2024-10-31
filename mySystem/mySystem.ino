#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <DHT_U.h>
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;//创建蓝牙对象
int BTdata;//存储蓝牙数据

#define DHTPIN 0 // 设置获取数据的引脚

#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);     //创建一个DHT对象

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
float h = 0.00, t = 0.00, f = 0.00; //dht11的温度和湿度
// Declaration for an SSD1306 d isplay connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define BUZZER_PIN 15

#define trigPin 23
#define echoPin 22
float distance = 0;

int channel_PWM = 8;  
int freq_PWM = 50;  
int res_PWM = 10;  
const int  PWM_PIN = 32; //使用32号引脚
int servoFlag = 0;

uint8_t Data[20]=" ";//传输数据

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World");
  //启动蓝牙，定义蓝牙名称
  SerialBT.begin("my system");
  ledcSetup(channel_PWM,freq_PWM,res_PWM);  //设置通道
  ledcAttachPin(PWM_PIN,channel_PWM);  //将引脚绑定到通道上
  //设置超声波引脚为输入/输出
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  oled_init();
  dht.begin();
}

void loop() {
  get_BTdata();
  get_dht();
  ultrasonic();
  oled_show();
  send_BT();
  delay(1000);
}

//接收手机蓝牙传送的数据
void get_BTdata(){
  if(SerialBT.available()){
    BTdata = SerialBT.read();
    Serial.println(BTdata);
    //风扇开关判断
    if(BTdata == 'F'){                
      ledcWrite(channel_PWM,26);
      servoFlag = 1;
    }
    else if(BTdata == 'f'){
      ledcWrite(channel_PWM,77);
      servoFlag = 1;
    }
    else if(BTdata == 'O'){
      servoFlag = 0;
    }
  }
}

//蓝牙发送数据给手机
void send_BT(){
  //.print()发送的是字符
  //.write()发送的是字节
  //String Data=dataCheck(h)+" "+dataCheck(t)+" "+dataCheck(sun);
  dataCheck();
  SerialBT.write(Data,15);
}

void dataCheck(){
  int hh = h*100;
  Data[4] = hh%10+'0';hh/=10;
  Data[3] = hh%10+'0';hh/=10;
  Data[2] = '.';
  Data[1] = hh%10+'0';hh/=10;
  Data[0] = hh%10+'0';

  int tt = t*100;
  Data[9] = tt%10+'0';tt/=10;
  Data[8] = tt%10+'0';tt/=10;
  Data[7] = '.';
  Data[6] = tt%10+'0';tt/=10;
  Data[5] = tt%10+'0';

  int dd = distance*100;
  Data[14] = dd%10+'0';dd/=10;
  Data[13] = dd%10+'0';dd/=10;
  Data[12] = '.';
  Data[11] = dd%10+'0';dd/=10;
  Data[10] = dd%10+'0';
}

//OLED初始化
void oled_init(){
  Wire.begin(18,19);//SDA,SCL引脚
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C,false,false)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1000);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(WHITE);//开像素点发光
  oled.clearDisplay();//清屏
  oled.setTextSize(2); //设置字体大小
  oled.print("welcome");
  oled.setCursor(20, 40);//设置显示位置
  oled.display();
  delay(3000);    ///延时3秒
}

//OLED显示获取数据
void oled_show(){
  oled.clearDisplay();
  oled.setTextSize(1); //设置字体大小
  //显示距离
  oled.setCursor(0, 0);
  oled.print("distance: ");
  oled.print(distance);
  oled.print("cm");
  //显示湿度数据
  oled.setCursor(0, 20);
  oled.print("H: ");
  oled.print(h);
  oled.print("%");
  //显示温度数据
  oled.setCursor(0, 30);
  oled.print("T: ");
  oled.print(t);
  oled.print("C");
  oled.display();
}

//获取温湿传感器数据
void get_dht(){
  h = dht.readHumidity();
  Serial.println(h);
  t = dht.readTemperature();
  Serial.println(t);
  f = dht.readTemperature(true);
}

void ultrasonic(){
  //发出超声波脉冲
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  
  //计算超声波回波的时间
  long duration = pulseIn(echoPin, HIGH);
  
  //计算物体的距离
  distance = duration * 0.034 / 2;

  if(servoFlag == 0){
    if(distance >= 10)
    {
      ledcWrite(channel_PWM,26); //20ms⾼电平为0.5ms左右 ，也就是0.5/20*1024 = 26，此时180度舵机角度为0°
      digitalWrite(BUZZER_PIN, HIGH);
    }
    else if(distance < 10)
    {
      ledcWrite(channel_PWM, 77); //20ms⾼电平为1.5ms左右 ，也就是1.5/20*1024 = 77，此时180度舵机角度为90°
      digitalWrite(BUZZER_PIN, LOW);
    }
  }
  Serial.println(distance);
}