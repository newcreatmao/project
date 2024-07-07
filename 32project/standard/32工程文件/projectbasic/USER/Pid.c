// #include "stm32f10x.h"

// // PID参数
// float Kp = 0.5;
// float Ki = 0.2;
// float Kd = 0.1;

// // 目标位置
// float targetPosition = 0;

// // 当前位置
// float currentPosition = 0;

// // PID控制器变量
// float lastError = 0;
// float integral = 0;

// // PID控制函数
// void PID_Control()
// {
//     // 计算当前误差
//     float error = targetPosition - currentPosition;

//     // 计算控制量
//     float control = Kp * error + Ki * integral + Kd * (error - lastError);

//     // 更新PID控制器变量
//     lastError = error;
//     integral += error;

//     // 执行控制动作
//     // TODO: 在这里添加控制动作的代码
// }

// int main()
// {
//     // 初始化硬件和参数设置
//     // TODO: 在这里添加初始化代码

//     while (1)
//     {
//         // 读取当前位置
//         // TODO: 在这里添加读取当前位置的代码

//         // 执行PID控制
//         PID_Control();

//         // 更新控制周期
//         // TODO: 在这里添加更新控制周期的代码
//     }

//     return 0;
// }

// typedef struct {
//     float Kp;     //比例系数
//     float Ki;     //积分系数
//     float Kd;     //微分系数
//     float target_val;     //目标值
//     float actual_val;     //实际值
//     float err;     //误差
//     float integral;     //误差累积
//     float err_last;     //上次误差
// } PID;

// float PID_realize(float temp_val) {
//     static PID pid;     //静态变量，保存上次的状态
    
//     pid.target_val = temp_val;
//     pid.err = pid.target_val - pid.actual_val;
//     float increment_val = pid.Kp * (pid.err - pid.err_last) + pid.Ki * pid.err + pid.Kd * (pid.err - 2 * pid.err_last + pid.err_next);
//     pid.actual_val += increment_val;
//     pid.err_last = pid.err_next;
//     pid.err_next = pid.err;
    
//     return pid.actual_val;
// }



#include"Pid.h"
PID pid;

/**************************************************************************
函数功能：PID数据初始化
入口参数：无
返回  值：无
**************************************************************************/
void PID_Init()
{
    /*平衡PID环控制参数初始化*/
    //P对应反应快慢
    pid.Sv =  0;
    pid.Kp =-97; //0_720,设置为168
    pid.Kd = -138;//190

////////								/*速度PID环控制参数初始化*/
    pid.Kp_speed =-1800;
    pid.Ki_speed = pid.Kp_speed/200;//-0.066
    pid.EK_speed = 0;
    pid.SEK_speed = 0;

    pid.left = 0;
    pid.right = 0;				//速度初始值
    //65 2
    /*转向PID环控制参数初始化*/
    pid.Kp_turn =0;
    pid.Angle_turn = 0;
    /*速度PID环控制参数初始化*/

}


/**************************************************************************
函数功能：以下三个函数，分别计算各个环的PID值，并返回
入口参数：未知
返回  值：无
**************************************************************************/


/*小车平衡环部分，微分+比例控制
微分变量为直接读取的加速度*/
extern short gyroy;
int balance(float Angle)
{

    signed  int  Bias;
    int balance;
    Bias=(Angle-pid.Sv)+pid.move;
    balance=pid.Kp*Bias+gyroy*pid.Kd/100;

    return balance;
}
/*
函数功能：速度PI控制
入口参数：encoder_left，左轮速度
					encoder_right，右轮速度
返回  值：速度控制PWM
作    者：强大的CSDN用户
*/
int velocity(int encoder_left,int encoder_right)
{
    static float Velocity,Encoder_Least,Encoder,Movement;
    static float Encoder_Integral;
//	  float kp=-90,ki=-0.45;
    //=============速度PI控制器=======================//
    Encoder_Least =(encoder_left+encoder_right)-0;                    //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零）
    Encoder *= 0.7;		                                                //===一阶低通滤波器
    Encoder += Encoder_Least*0.3;	                                    //===一阶低通滤波器
    Encoder_Integral +=Encoder;                                       //===积分出位移 积分时间：10ms
    Encoder_Integral=Encoder_Integral-Movement;                       //===接收遥控器数据，控制前进后退
    if(Encoder_Integral>10000)  	Encoder_Integral=10000;             //===积分限幅
    if(Encoder_Integral<-10000)	Encoder_Integral=-10000;              //===积分限幅
    Velocity=Encoder*pid.Kp_speed+Encoder_Integral*pid.Ki_speed;                          //===速度控制
    //return 0;//先调节直立
    return Velocity/10;
}


/**************************************************************************
函数功能：转向PD控制
入口参数：左轮编码器、右轮编码器、Z轴陀螺仪
返回  值：转向控制PWM
作    者：平衡小车之家
**************************************************************************/
int turn(int encoder_left,int encoder_right,float gyro)//转向控制
{
    static float Turn_Target,Turn,Encoder_temp,Turn_Convert=0.9,Turn_Count;
    float Turn_Amplitude=148/Flag_sudu,Kp=42,Kd=0;
    //=============遥控左右旋转部分=======================//
    if(1==Flag_Left||1==Flag_Right)                      //这一部分主要是根据旋转前的速度调整速度的起始速度，增加小车的适应性
    {
        if(++Turn_Count==1)
            Encoder_temp=myabs(encoder_left+encoder_right);
        Turn_Convert=50/Encoder_temp;
        if(Turn_Convert<0.6)Turn_Convert=0.6;
        if(Turn_Convert>3)Turn_Convert=3;
    }
    else
    {
        Turn_Convert=0.9;
        Turn_Count=0;
        Encoder_temp=0;
    }
    if(1==Flag_Left)	           Turn_Target-=Turn_Convert;
    else if(1==Flag_Right)	     Turn_Target+=Turn_Convert;
    else Turn_Target=0;

    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //===转向速度限幅
    if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
    if(Flag_Qian==1||Flag_Hou==1)  Kd=1;
    else Kd=0;   //转向的时候取消陀螺仪的纠正 有点模糊PID的思想
    //=============转向PD控制器=======================//
    Turn=-Turn_Target*Kp -gyro*Kd;                 //===结合Z轴陀螺仪进行PD控制
    return Turn;
}