#include <Arduino.h>
 
#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
 
BluetoothSerial SerialBT;

void setup(){
  Serial.begin(115200);

  SerialBT.begin("my system");//定义蓝牙名称
}
 
 
void loop(){
  if(SerialBT.available()){
    int data = SerialBT.read();
    Serial.println(data);
  }
}
