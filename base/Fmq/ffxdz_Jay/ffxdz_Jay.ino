#include <Arduino.h>
#define BUZZER_PIN 23//定义蜂鸣器连接的GPIO口
#define P	0
#define L1	1
#define L1_	2
#define L2	3
#define L2_	4
#define L3	5
#define L4	6
#define L4_	7
#define L5	8
#define L5_	9
#define L6	10
#define L6_	11
#define L7	12
#define M1	13
#define M1_	14
#define M2	15
#define M2_	16
#define M3	17
#define M4	18
#define M4_	19
#define M5	20
#define M5_	21
#define M6	22
#define M6_	23
#define M7	24
#define H1	25
#define H1_	26
#define H2	27
#define H2_	28
#define H3	29
#define H4	30
#define H4_	31
#define H5	32
#define H5_	33
#define H6	34
#define H6_	35
#define H7	36
#define MUSIC_SPEED 500
static int musicSelect = 0,peroidSelect = 0;

const unsigned int HalfPeroidTable[]={
	0, 
	1908,1805,1701,1608,1515,1433,1351,1276,1205,1136,1073,1008,
	956,903,852,804,759,716,676,638,602,568,536,506,
	478,451,426,402,379,358,338,319,301,284,268,263,
};
//反方向的钟高潮部分
const unsigned char  Music[]= {
	M6,2,
	M5,2,
	M3,2,
	M2,4+2,
	M3,2,
	M1,2+2,
	M2,4,
	M3,2+2,
	M5,4+2,
	M6,2,
	M5,2,
	M3,2,
	M2,4+2,
	M3,2,
	M2,2+4,
	M1,2,
	M2,4,
	M1,2+4,
	0XFF
};

void setup() {
  //设置BUZZER_PIN为输出模式
  pinMode(BUZZER_PIN,OUTPUT);
}

void loop() {
  //发出蜂鸣声
  // tone(BUZZER_PIN,1000);//发出100OHz的频率
  // delay(1000);//持续1秒钟
  // noTone(BUZZER_PIN);//停止发声
  // delay(100);//延迟1秒钟
  while(1){
    if(Music[musicSelect]!=0XFF){
        peroidSelect = Music[musicSelect]; //选择音阶频率
        tone(BUZZER_PIN,HalfPeroidTable[peroidSelect]);//发出指定频率
        delay(MUSIC_SPEED/4*Music[musicSelect+1]);
        noTone(BUZZER_PIN);//停止发声
        musicSelect+=2;
        delay(10);
    }
    else
    {
        musicSelect = 0;
        peroidSelect  = 0;
    }
  }
}
