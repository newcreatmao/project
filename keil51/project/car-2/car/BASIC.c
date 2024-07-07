#include <REG52.H>
#include "HEAD.H"	
void forward()			//前进
{
	left_motor_go;
	right_motor_go;
}

void backward()			//后退
{
	left_motor_back;
	right_motor_back;
}

void stop()				//停止
{
	left_motor_stop;
	right_motor_stop;
}

void left()				//左转
{
	left_motor_stop;
	right_motor_go;
}

void right()			//右转
{
	right_motor_stop;
	left_motor_go;
}

void left_rapidly()		//高速左转
{
	right_motor_go;
	left_motor_back;	
}

void right_rapidly()	//高速右转
{
	left_motor_go;
	right_motor_back;	
}

void back_right()		//车屁股向右
{
	left_motor_back;
	right_motor_stop;
}

void back_left()		//车屁股向左
{
	left_motor_stop;
	right_motor_back;
}

//周期=定时器溢出时间*占空比 ，100HZ，T=10 000 us，占空比最大256，溢出时间39.0625us,需要的定时器计数39.0625/1.085=36次
void timer0(void)		//39微秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xA4;		//设置定时初始值
	TH0 = 0xFF;		//设置定时重载值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	ET0=1;			//1允许定时器中断
	EA=1;			//允许总中断
	PT0=0;			//中断优先级
}


