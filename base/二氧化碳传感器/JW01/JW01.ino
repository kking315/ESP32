#include <SoftwareSerial.h>

// 定义软件串口的RX和TX引脚
const int rxPin = 3; // 这个引脚需要连接到传感器的TX
const int txPin = 1; // 这个引脚需要连接到传感器的RX

// 设置软件串口
SoftwareSerial co2Sensor(rxPin, txPin);

void setup() {
  // 初始化串口
  Serial.begin(115200);

  // 启动传感器串口
  co2Sensor.begin(115200);
  Serial.println("CO2 Sensor started");
}

void loop() {
  // 传感器的数据包大小
  const int packetSize = 6;
  byte packet[packetSize];

  // 读取数据
  if (co2Sensor.available()) {
    for (int i = 0; i < packetSize; i++) {
      // 读取传感器数据
      packet[i] = co2Sensor.read();
    }

    // 校验和检验，就是检验发送时的数据总和和接收时的数据总和是否一致，以此判断数据是否丢失
    if (packet[5] == (byte)(packet[0] + packet[1] + packet[2] + packet[3] + packet[4]) % 256) {
      // 计算CO2浓度
      int co2 = (packet[1] * 256) + packet[2];
      Serial.print("CO2 Concentration: ");
      Serial.print(co2);
      Serial.println(" PPM");
    } else {
      Serial.println("Checksum error");
    }
  }

  // 传感器数据读取间隔
  delay(2000);
}