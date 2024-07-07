#include <REGX52.H>
#include "basic.h"
#include"delay.h"
#include"LCD1602.h"

sbit EN1A = P1^5;
sbit EN1B = P0^4;//L298N使能引脚

unsigned char count;//计数器
unsigned char speech=20;//速度
void prepare ()
{
	ET0 = 1;//定时器0中断允许开关
	EA = 1;//定时器总开关
	PT0 =0;//定时器0中断优先级
}
void init()//100微秒@11。0592MHZ
{
	TMOD &= 0xF0;//设置定时器模式
	TMOD |= 0x01;//设置定时器模式
	TL0 = 0xA4;//设置定时器初始值
	TH0 = 0xFF;//设置定时器初始值
	TF0 = 0;//消除TF0标志
	TR0 = 1;//定时器0开始计时
	prepare();
}//定时器中断初处理
void go ()
{
	car_lf_go();
	car_rg_go();
}
void main ()
{
	myinit();
	init();
	mystring(1,1,"myspeech");
	while(1)
	{
	if(P3_1==0)
	{
			delayms(20);
			while(P3_1==0);
			delayms(20);
			speech++;
	}
	if(P3_2==0)
	{
			delayms(20);
			while(P3_1==0);
			delayms(20);
			speech--;
	}
	go();
	}
	mychar(2,2,speech);
	//一边高一边低，高低电平，形成电流，就可以转动
	//正转倒转用前后赋值来控制
	//判断车轮位置可一个个输入01来判断
}

void mywant () interrupt 1 //中断函数，1为定时器0中断模式
{
	TL0 = 0xA4;
	TH0 = 0xFF;//定时器回归初始值
	count++;
	if(count >=100)
	{
		count=0;
	}//时间计数器，100为周期
	if(count<speech)
	{
		EN1A = 1;
		EN1B = 1;//使能引脚，1供能，0断能
	}
	else
	{
		EN1A = 0;
		EN1B = 0;
	}
}
