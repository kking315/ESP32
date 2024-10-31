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

void setup() {
    Serial.begin(115200);
    initIrReceive();
}

void loop() {
  //getIrReceive();
  //Serial.printf("command = %d\n",IrReceiver.decodedIRData.command);
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
      //红外控制开关
      if(IrReceiver.decodedIRData.command == 0x47)
        openFlag = true;
      if(openFlag){
        switch (IrReceiver.decodedIRData.command) {
          case 0x45://停止红外控制
              openFlag = false;
              Serial.println("Stop!");
              break;
          case 0x40://向前
              Serial.println("forward!");
              break;
          case 0x19://向后
              Serial.println("back!");
              break;
          case 0x7://向左
              Serial.println("left!");
              break;
          case 0x9://向右
              Serial.println("right!");
              break;
          case 0x15://转圈
              Serial.println("Circle!");
              break;
          default:
              Serial.printf("command = %x\n",IrReceiver.decodedIRData.command);
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