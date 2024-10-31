#include <lvgl.h>
#include <demos/lv_demos.h>
#include <examples/lv_examples.h>
#include <TFT_eSPI.h> 
#include "touch.h"

//use psram or not
#define USE_PSRAM 1 //0-not use , 1-use
#define CENTER 240

static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;
static lv_disp_draw_buf_t disp_buf;
static lv_color_t *buf;
static lv_disp_drv_t disp_drv;
static lv_indev_drv_t indev_drv;
   
TFT_eSPI my_lcd = TFT_eSPI();

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);
    my_lcd.setAddrWindow(area->x1, area->y1,  w, h);
    my_lcd.pushColors((uint16_t *)&color_p->full, w*h, true);
    lv_disp_flush_ready(disp);
}

/* Reading input device (simulated encoder here) */
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  if (touch_has_signal())
  {
    if (touch_touched())
    {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
    }
    else if (touch_released())
    {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void setup()
{
    Serial.begin(115200); /* prepare for possible serial debug */
    String LVGL_Arduino = "Hello Arduino! ";
    LVGL_Arduino += String('V') + lv_version_major() + "." + lv_version_minor() + "." + lv_version_patch();
    my_lcd.init();
    my_lcd.setRotation(1);  
    touch_init(my_lcd.width(), my_lcd.height(),my_lcd.getRotation());
    lv_init();
    delay(10);

#if USE_PSRAM != 0
    buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * screenHeight , MALLOC_CAP_SPIRAM);
#else
    buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth*20 , MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
#endif
  if (!buf)
  {
    my_lcd.fillScreen(TFT_WHITE);
    my_lcd.setTextColor(TFT_RED);
    my_lcd.drawCentreString("LVGL display draw buffer allocate failed!",CENTER,my_lcd.height()/2-8,4);
  }
  else
  {
#if USE_PSRAM != 0
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, screenWidth * screenHeight);
#else
    lv_disp_draw_buf_init(&disp_buf, buf, NULL, screenWidth*20);
#endif
    /*Initialize the display*/
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = my_lcd.width();
    disp_drv.ver_res = my_lcd.height();
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &disp_buf;
    lv_disp_drv_register(&disp_drv);

    /*Initialize the (dummy) input device driver*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_drv_register(&indev_drv);

    /* Create simple label */
    //lv_obj_t *label = lv_label_create( lv_scr_act() );
    //lv_label_set_text( label, LVGL_Arduino.c_str() );
   // lv_obj_align( label, LV_ALIGN_CENTER, 0, 0 );

    // uncomment one of these demos
     lv_demo_widgets();            // OK
    // lv_demo_benchmark();          // OK
    // lv_demo_keypad_encoder();     // works, but I haven't an encoder
    // lv_demo_music();              // NOK
    // lv_demo_stress();             // seems to be OK
  }
}


void loop()
{

    lv_task_handler(); /* let the GUI do its work */
    delay(5);
}
