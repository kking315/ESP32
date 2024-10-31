#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TFT_eSPI.h>
#include <U8g2lib.h>

#include "common.h"
#ifdef U8X8_HAVE_HW_I2C
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 d isplay connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  tft.init();
  pinMode(9, OUTPUT);
  digitalWrite(9, 0);	// default output in I2C mode for the SSD1306 test shield: set the i2c adr to 0

  u8g2.begin();
  Serial.begin(115200);
  Wire.begin(23,22);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C,false,false)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  delay(2000);
  display.clearDisplay();

  // display.setTextSize(1);
  // display.setTextColor(WHITE);
  // display.setCursor(0, 10);
  // Display static text
  //tft.println("\nHello World!");
  //DrawStr(tft,10, 2, "空气温度：", TFT_GREEN);
  u8g2.println("你好！");
  display.display(); 
}

void loop() {
  
}