void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  PID(30,40);
}

struct _pid
{
  int pv;         // integer that contains the process value 过程量 
  int sp;         // integer that contains the set point   设定值 
  float integral; // 积分值 －－ 偏差累计值 
  float pgain;
  float igain;
  float dgain;
  int deadband;   //死区 
  int last_error;
};

struct _pid warm, *pid;
int process_point, set_point, dead_band;
float p_gain, i_gain, d_gain, integral_val, new_integ;

void pid_init( struct _pid *warm, int process_point, int set_point )
{
  struct _pid *pid;
  pid = warm;
  pid->pv = process_point;
  pid->sp = set_point;
}

//PID死区参数
void pid_tune( struct _pid *pid,
  float p_gain,
  float i_gain,
  float d_gain,
  int dead_band )
{
  pid->pgain = p_gain;
  pid->igain = i_gain;
  pid->dgain = d_gain;
  pid->deadband = dead_band;
  pid->integral = integral_val;
  pid->last_error = 0;
}

void pid_setinteg( struct _pid *pid, float new_integ )
{
  pid->integral = new_integ;
  pid->last_error = 0;
}

void pid_bumpless( struct _pid *pid )
{
  pid->last_error = ( pid->sp ) - ( pid->pv );  //设定值与反馈值偏差 
}

//位置式PID，采用抗积分饱和限制运算
float pid_calc( struct _pid *pid )
{
  int err;
  float pterm, dterm, result, ferror;
  
  // 计算偏差 
  err = ( pid->sp ) - ( pid->pv );
  
  // 判断是否大于死区 
  if ( abs( err ) > pid->deadband )
  {
    ferror = (float) err;   //do integer to float conversion only once 数据类型转换 
      
    // 比例项 
    pterm = pid->pgain * ferror;
    
    if ( pterm > 100 || pterm < -100 )
    {
      pid->integral = 0.0;
    }
    else
    {
      // 积分项 
      pid->integral += pid->igain * ferror;
      
      // 输出为0－－100% 
      // 如果计算结果大于100，则等于100 
      if ( pid->integral > 100.0 )
      {
        pid->integral = 100.0;
      }
      // 如果计算结果小于0.0，则等于0 
      else if ( pid->integral < 0.0 )
        pid->integral = 0.0;
      
    }
    
    // 微分项 
    dterm = ( (float) ( err - pid->last_error ) ) * pid->dgain;
    
    result = pterm + pid->integral + dterm;
  }
  else
    result = pid->integral; // 在死区范围内，保持现有输出 
      
  // 保存上次偏差 
  pid->last_error = err;
  
  // 输出PID值(0-100) 
  return ( result );
}


//数据监测与处理
void PID(int data_value,int data_set){
  float display_value;
  int count = 0;
  pid = &warm;
  // 初始化参数 
  process_point = data_value;
  set_point = data_set;
  p_gain = (float) ( 5.2 );
  i_gain = (float) ( 0.77 );
  d_gain = (float) ( 0.18 );
  dead_band = 2;
  integral_val = (float) ( 0.01 );
  while ( count <= 20 )
  {
    // 设定PV,SP 值 
    pid_init( &warm, process_point, set_point );
    
    // 初始化PID 参数值 
    pid_tune( &warm, p_gain, i_gain, d_gain, dead_band );
    
    // 初始化PID 输出值 
    pid_setinteg( &warm, 0.0 );
    
    //pid_setinteg(&warm,30.0); 
    //Get input value for process point 
    pid_bumpless( &warm );
    
    // how to display output 
    display_value = pid_calc( &warm );
    
    Serial.println(display_value);
    
    count++;
  }
}