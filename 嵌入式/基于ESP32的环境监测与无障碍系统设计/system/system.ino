#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 0 // 设置获取数据的引脚
#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);     //创建一个DHT对象

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 d isplay connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int trigPin = 16;
const int echoPin = 17;
const int fmq = 25;


void setup() {
  //设置超声波引脚为输入/输出
  pinMode(trigPin, OUTPUT);
  pinMode(fmq, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(115200);
  dht.begin();               //初始化DHT传感器
  //OLED
  Wire.begin(23,22);//SDA,SCL

  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C,false,false)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1000);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(WHITE);
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.print("Hello!");
  oled.setCursor(20, 20);
  // Display static text
  oled.display();
  delay(3000);    ///延时3秒
}

void loop() {
  //发出超声波脉冲
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //计算超声波回波的时间
  long duration = pulseIn(echoPin, HIGH);
  //计算物体的距离，控制蜂鸣器状态
  long distance = duration * 0.034 / 2;
  if(distance >= 10){digitalWrite(fmq,HIGH);}
  else if(distance < 10){digitalWrite(fmq,LOW);}
  Serial.println(distance);
  //温湿度数据
  float h = dht.readHumidity();          //读取湿度
  Serial.println(h);
  float t = dht.readTemperature();       //读取摄氏度
  Serial.println(t);
  float f = dht.readTemperature(true);   //读取华氏度
  if (isnan(h) || isnan(t) || isnan(f)) {    //如果读取错误
    Serial.println("读取传感器失败");         //读取失败提示
    return;
  }
  //输出物体的距离
  oled.clearDisplay();
  oled.setTextSize(2); //设置字体大小
  oled.setCursor(0, 0);
  oled.print("dis: ");
  oled.print(distance);
  oled.print("cm");
  //显示湿度数据
  oled.setCursor(0, 20);
  oled.print("H: ");
  oled.print(h);
  oled.print("%");
  //显示温度数据
  oled.setCursor(0, 40);
  oled.print("T: ");
  oled.print(t);
  oled.print("C");
  oled.display();
  delay(1000);
}
