#include <Arduino.h>
 
#include "BluetoothA2DPSink.h"
 
BluetoothA2DPSink a2dp_sink;
 
void setup(){
 
 
  i2s_pin_config_t my_pin_config = {
        .bck_io_num = 26,    //输入 BCLK
        .ws_io_num = 27,    //输入 LRC
        .data_out_num = 25, //输出 DIN
        .data_in_num = I2S_PIN_NO_CHANGE
  };

  a2dp_sink.set_pin_config(my_pin_config);
  a2dp_sink.start("my music");
 
}
 
 
void loop(){
 
}
