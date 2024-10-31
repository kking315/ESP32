#include <Arduino.h>
 
#include "BluetoothA2DPSink.h"
 
BluetoothA2DPSink a2dp_sink;
 
void avrc_metadata_callback(uint8_t data1, const uint8_t *data2)
{
  // Serial.printf("AVRC metadata rsp: attribute id 0x%x, %s\n", data1, data2);
 
  //String strData2=getStringFromChars(data2,sizeof(data2));
  String strData2 = (const char *)data2;
  
  if (data1 == 2){  Serial.printf("歌名：%s\n", data2); }
  if (data1 == 4){  Serial.printf("专辑：%s\n", data2); }
  if (data1 == 1){  Serial.printf("歌词：%s\n", data2); }
}

void setup(){
 
  Serial.begin(115200);

  i2s_pin_config_t my_pin_config = {
        .bck_io_num = 26,    //输入 BCLK
        .ws_io_num = 27,    //输入 LRC
        .data_out_num = 25, //输出 DIN
        .data_in_num = I2S_PIN_NO_CHANGE
  };

  a2dp_sink.set_avrc_metadata_attribute_mask(ESP_AVRC_MD_ATTR_TITLE | ESP_AVRC_MD_ATTR_ARTIST | ESP_AVRC_MD_ATTR_ALBUM | ESP_AVRC_MD_ATTR_TRACK_NUM | ESP_AVRC_MD_ATTR_NUM_TRACKS  );
  a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);

  a2dp_sink.set_pin_config(my_pin_config);
  a2dp_sink.start("my music");
 
}
 
 
void loop(){
 
}
