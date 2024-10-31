#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 0 // 设置获取数据的引脚
 
// 对应DHT的版本，选择一个取消注释
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);     //创建一个DHT对象
 
void setup() {
   Serial.begin(115200);
   dht.begin();               //初始化DHT传感器
}
 
void loop() {
   delay(2000); // 暂停2秒，读取数据官方说明需要250毫秒
   float h = dht.readHumidity();          //读取湿度
   float t = dht.readTemperature();       //读取摄氏度
   float f = dht.readTemperature(true);   //读取华氏度
   if (isnan(h) || isnan(t) || isnan(f)) {    //如果读取错误
      Serial.println("读取传感器失败");         //读取失败提示
      return;
   }
   float hif = dht.computeHeatIndex(f, h);  //计算华氏度的热指数
   float hic = dht.computeHeatIndex(t, h, false); //计算摄氏度的热指数
 
   Serial.print ("湿度: ");
   Serial.print (h);
   Serial.print ("% | ");
   Serial.print ("摄氏度: ");
   Serial.print (t);
   Serial.print ("*C | 华氏度:");
   Serial.print (f);
   Serial.print ("*F ");
   Serial.print (" | 摄氏热指数: ");
   Serial.print (hic);
   Serial.print ("*C  | 华氏热指数");
   Serial.print (hif);
   Serial.println ("*F");
}