#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 0 // 设置获取数据的引脚

#define DHTTYPE DHT11 // DHT 11
DHT dht(DHTPIN, DHTTYPE);     //创建一个DHT对象

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
float h = 0.00, t = 0.00, f = 0.00; //dht11的温度和湿度
// Declaration for an SSD1306 d isplay connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define LED_y  12
#define LED_r  14

void setup() {
  Serial.begin(115200);
  Serial.println("Hello World");
  pinMode(LED_y, OUTPUT);
  pinMode(LED_r, OUTPUT);
  oled_init();
  dht.begin();
}

void oled_init(){
  Wire.begin(17,16);//SDA,SCL
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

void oled_show(){
  oled.clearDisplay();
  oled.setTextSize(2); //设置字体大小
  oled.setCursor(0, 0);
  oled.print("H: ");
  oled.print(h);
  oled.print("%");
  oled.setCursor(0, 20);
  oled.print("T: ");
  oled.print(t);
  oled.print("C");
  oled.setCursor(0, 40);
  oled.print("F: ");
  oled.print(f);
  oled.print("F");
  oled.display();
}

void get_dht()
{
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
}

void loop() {
  get_dht();
  oled_show();
  if(t>30.00){
    digitalWrite(LED_r, HIGH);
    digitalWrite(LED_y, LOW);
  }
  else{
    
    digitalWrite(LED_y, HIGH);
    digitalWrite(LED_r, LOW);
  }
}
