#include <Arduino.h>
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>
#include "BluetoothSerial.h"
#include "motorTyre.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;//创建蓝牙对象
uint16_t BTdata;//存储蓝牙数据

#if defined(APPLICATION_PIN)
#define DEBUG_BUTTON_PIN    APPLICATION_PIN // if low, print timing for each received data set
#else
#define DEBUG_BUTTON_PIN   6
#endif
//红外控制标记
bool openFlag = false;

void generateTone();
void handleOverflow();
bool detectLongPress(uint16_t aLongPressDurationMillis);
void initIr();
void getIrReceive();
void control(uint16_t hex);
//超声波测距
const int trigPin = 0;
const int echoPin = 2;
long distance = 0;
//RGB
int led1=16;//R
int led2=17;//G
int led3=5;//B

int fmq = 19;

void setup() {
  Serial.begin(115200);
  //设置超声波引脚为输入/输出
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //RGB
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  //fmq
  pinMode(fmq,OUTPUT);
  initMotor();
  initIrReceive();
  //启动蓝牙，定义蓝牙名称
  SerialBT.begin("my Car");
}

void loop() {
  getBTdata();
  if (IrReceiver.decode()) {
    Serial.println("接收到红外信号");
    #if FLASHEND < 0x3FFF
      IrReceiver.printIRResultMinimal(&Serial);
    #else
      if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
          handleOverflow();
      } else {
        if ((IrReceiver.decodedIRData.protocol != SONY) &&
            (IrReceiver.decodedIRData.protocol != PULSE_WIDTH) &&
            (IrReceiver.decodedIRData.protocol != PULSE_DISTANCE) &&
            (IrReceiver.decodedIRData.protocol != UNKNOWN) &&
            digitalRead(DEBUG_BUTTON_PIN) != LOW) {
            generateTone();
        }

        if (IrReceiver.decodedIRData.protocol == UNKNOWN || digitalRead(DEBUG_BUTTON_PIN) == LOW) {
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        } else {
            IrReceiver.printIRResultShort(&Serial);
            IrReceiver.printIRSendUsage(&Serial);
        }
      }
    #endif
    IrReceiver.resume();

    if (IrReceiver.decodedIRData.address == 0) {
      //红外控制开关 防止其他信号干扰
      if(IrReceiver.decodedIRData.command == 0x47)
        openFlag = true;
      if(openFlag){
        control(IrReceiver.decodedIRData.command); 
      }
    }

    // if (detectLongPress(1000)) {
    //     Serial.print(F("Command 0x"));
    //     Serial.print(IrReceiver.decodedIRData.command, HEX);
    //     Serial.println(F(" was repeated for more than 2 seconds"));
    // }
  }
  getDis();
}

void getBTdata(){
  if(SerialBT.available()){
    BTdata = uint16_t(SerialBT.read());
    Serial.println(BTdata);
    //中断红外控制
    // if(openFlag) openFlag = false;
    control(BTdata);
  }
}

void control(uint16_t hex){
  switch (hex) {
    case 0x45://停止红外控制
        openFlag = false;
        Serial.println("Stop!");
        stop();
        break;
    case 0x40://向前
        Serial.println("forward!");
        stop();
        forward();
        break;
    case 0x19://向后
        Serial.println("back!");
        stop();
        back();
        break;
    case 0x7://横向左移
        Serial.println("left!");
        stop();
        left();
        break;
    case 0x9://横向右移
        Serial.println("right!");
        stop();
        right();
        break;
    case 0x15://原地转圈
        Serial.println("Circle!");
        stop();
        circle();
        break;
    case 0x44://右前
        Serial.println("rightFront!");
        stop();
        rightFront();
        break;
    case 0x43://左前
        Serial.println("leftFront!");
        stop();
        leftFront();
        break;
    case 0x16://右后
        Serial.println("rightBack!");
        stop();
        rightBack();
        break;
    case 0xD://左后
        Serial.println("leftBack!");
        stop();
        leftBack();
        break;
    default:
        Serial.printf("hex = %x\n",hex);
        stop();
        break;
  }
}

void getDis(){
  //发出超声波脉冲
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  //计算超声波回波的时间
  long duration = pulseIn(echoPin, HIGH);
  
  //计算物体的距离
  distance = duration * 0.034 / 2;
  
  //输出物体的距离
  Serial.printf("distance = %ld\n", distance);
  if(distance >= 40||distance == 0){
    setColor(0,180,0); //Green
    analogWrite(fmq, 255);
  }
  else if(distance >= 15){
    setColor(90,0,0); //Red
    analogWrite(fmq, 150);
  }
  else{
    setColor(180,0,0); //Red-
    analogWrite(fmq, 50);
  }
}

void setColor(int red,int green,int blue){
  analogWrite(led1,green);
  analogWrite(led2,red);
  analogWrite(led3,blue);
}


void initIrReceive(){
  pinMode(DEBUG_BUTTON_PIN, INPUT_PULLUP);
  #if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) || defined(USBCON) || defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
      delay(4000);
  #endif
      Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
      Serial.println(F("Enabling IRin..."));
      IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
      Serial.print(F("Ready to receive IR signals of protocols: "));
      printActiveIRProtocols(&Serial);
  #if defined(IR_RECEIVE_PIN_STRING)
      Serial.println(F("at pin " IR_RECEIVE_PIN_STRING));
  #else
      Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
  #endif

  #if FLASHEND >= 0x3FFF
      Serial.print(F("If you connect debug pin "));
  #if defined(APPLICATION_PIN_STRING)
      Serial.print(APPLICATION_PIN_STRING);
  #else
      Serial.print(DEBUG_BUTTON_PIN);
  #endif
      Serial.println(F(" to ground, raw data is always printed"));
      Serial.print(RECORD_GAP_MICROS);
      Serial.println(F(" us is the (minimum) gap, after which the start of a new IR packet is assumed"));
      Serial.print(MARK_EXCESS_MICROS);
      Serial.println(F(" us are subtracted from all marks and added to all spaces for decoding"));
  #endif
}
//此函数无用↓
void getIrReceive(){
  if (IrReceiver.decode()) {
    Serial.println();
    #if FLASHEND < 0x3FFF
      IrReceiver.printIRResultMinimal(&Serial);
    #else
      if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
          handleOverflow();
      } else {
        if ((IrReceiver.decodedIRData.protocol != SONY) &&
            (IrReceiver.decodedIRData.protocol != PULSE_WIDTH) &&
            (IrReceiver.decodedIRData.protocol != PULSE_DISTANCE) &&
            (IrReceiver.decodedIRData.protocol != UNKNOWN) &&
            digitalRead(DEBUG_BUTTON_PIN) != LOW) {
            generateTone();
        }

        if (IrReceiver.decodedIRData.protocol == UNKNOWN || digitalRead(DEBUG_BUTTON_PIN) == LOW) {
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        } else {
            IrReceiver.printIRResultShort(&Serial);
            IrReceiver.printIRSendUsage(&Serial);
        }
      }
    #endif
    IrReceiver.resume();

    if (IrReceiver.decodedIRData.address == 0) {
      switch (IrReceiver.decodedIRData.command) {
        case 0x10:
            // do something
            break;
        case 0x11:
            // do something else
            break;
        default:
            Serial.printf("command = %x\n",IrReceiver.decodedIRData.command);
            break;
      }
    }

    if (detectLongPress(1000)) {
        Serial.print(F("Command 0x"));
        Serial.print(IrReceiver.decodedIRData.command, HEX);
        Serial.println(F(" was repeated for more than 2 seconds"));
    }
  }
}

void generateTone() {
  #if !defined(ESP8266) && !defined(NRF5)
    #if defined(ESP32)
        tone(TONE_PIN, 2200, 5);
    #else
        IrReceiver.stopTimer();
        tone(TONE_PIN, 2200, 8);
        delay(8);
        IrReceiver.restartTimer(8000);
    #endif
  #endif
}

void handleOverflow() {
    Serial.println(F("Overflow detected"));
    Serial.println(F("Try to increase the \"RAW_BUFFER_LENGTH\" value of " STR(RAW_BUFFER_LENGTH) " in " __FILE__));

  #if !defined(ESP8266) && !defined(NRF5)
    #if defined(ESP32)
        tone(TONE_PIN, 1100, 10);
        delay(50);
        tone(TONE_PIN, 1100, 10);
    #else
        IrReceiver.stopTimer();
        tone(TONE_PIN, 1100, 10);
        delay(50);
        tone(TONE_PIN, 1100, 10);
        delay(50);
        IrReceiver.restartTimer(100000);
    #endif
  #endif
}

bool detectLongPress(uint16_t aLongPressDurationMillis) {
    static bool sLongPressJustDetected = false;
    static unsigned long sMillisOfFirstReceive = 0;

    if (!sLongPressJustDetected && (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
        if (millis() - sMillisOfFirstReceive > aLongPressDurationMillis) {
            sLongPressJustDetected = true;
        }
    } else {
        sMillisOfFirstReceive = millis();
        sLongPressJustDetected = false;
    }
    return sLongPressJustDetected;
}