#include <Arduino.h>
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

#if defined(APPLICATION_PIN)
#define DEBUG_BUTTON_PIN    APPLICATION_PIN // if low, print timing for each received data set
#else
#define DEBUG_BUTTON_PIN   6
#endif

bool openFlag = false;

void generateTone();
void handleOverflow();
bool detectLongPress(uint16_t aLongPressDurationMillis);
void initIr();
void getIrReceive();

#define INA1 12//左后
#define INA2 13
#define INB1 14//左前
#define INB2 27
#define INC1 25//右前
#define INC2 26
#define IND1 33//右后
#define IND2 32

void initMotor();
void stop();
void forward();
void back();
void left();
void right();
void circle();

void setup() {
  Serial.begin(115200);
  initMotor();
  initIrReceive();
}

void loop() {
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
      //红外控制开关 防止其他信号干扰
      if(IrReceiver.decodedIRData.command == 0x47)
        openFlag = true;
      if(openFlag){
        switch (IrReceiver.decodedIRData.command) {
          case 0x45://停止红外控制
              openFlag = false;
              Serial.println("Stop!");
              stop();
              break;
          case 0x40://向前
              Serial.println("forward!");
              forward();
              break;
          case 0x19://向后
              Serial.println("back!");
              back();
              break;
          case 0x7://横向左移
              Serial.println("left!");
              left();
              break;
          case 0x9://横向右移
              Serial.println("right!");
              right();
              break;
          case 0x15://原地转圈
              Serial.println("Circle!");
              circle();
              break;
          case 0x44://右前
              Serial.println("rightFront!");
              rightFront();
              break;
          case 0x43://左前
              Serial.println("leftFront!");
              leftFront();
              break;
          case 0x16://右后
              Serial.println("rightBack!");
              rightBack();
              break;
          case 0xD://左后
              Serial.println("leftBack!");
              leftBack();
              break;
          default:
              Serial.printf("command = %x\n",IrReceiver.decodedIRData.command);
              stop();
              break;
        }
      }
    }

    if (detectLongPress(1000)) {
        Serial.print(F("Command 0x"));
        Serial.print(IrReceiver.decodedIRData.command, HEX);
        Serial.println(F(" was repeated for more than 2 seconds"));
    }
  }
}

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

void forward(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,HIGH);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,HIGH);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,HIGH);
}

void back(){
  digitalWrite(INA1,HIGH);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,HIGH);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,HIGH);
  digitalWrite(IND2,LOW);
}

void right(){
  digitalWrite(INA1,HIGH);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,HIGH);
  digitalWrite(INC1,HIGH);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,HIGH);
}

void left(){
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

void leftFront(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,HIGH);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,HIGH);
}

void leftBack(){
  digitalWrite(INA1,HIGH);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,HIGH);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,LOW);
}

void rightFront(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,HIGH);
  digitalWrite(INB1,LOW);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,HIGH);
  digitalWrite(IND1,LOW);
  digitalWrite(IND2,LOW);
}

void rightBack(){
  digitalWrite(INA1,LOW);
  digitalWrite(INA2,LOW);
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  digitalWrite(INC1,LOW);
  digitalWrite(INC2,LOW);
  digitalWrite(IND1,HIGH);
  digitalWrite(IND2,LOW);
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