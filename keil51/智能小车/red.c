#include <REGX52.H>
#include "basic.h"
#include "delay.h"

sbit TRIG = P2^1;//定义超声波测距发送端
sbit ECHO = P2^2;//定义超声波测距接收端

unsigned int sum;//超声波测距结果
unsigned int limit;//小车与障碍物的限制限制距离

void red_control()
{
	TMOD = 0x11;//设置定时器模式
	TL1 = 0;//设置定时器初始值
	TH1 = 0;//设置定时器初始值
	
	TRIG = 1;
	delayus(20);//发射一段脉冲，至少20us
	TRIG = 0;
	
	while(!ECHO);//等待超声波模块返回脉冲
	TR1=1;//打开定时器
	while(ECHO);//等待超声波定时器返回脉冲结束
	TR1 = 0;//停止计数器，计时结束
	
	sum=((TH1*256+TL1)*0.034)/2+1;//计算距离
	
	if(limit>sum)
	{
		car_lf_stop();
		car_rg_stop();
		delayms(1000);
	}
}
