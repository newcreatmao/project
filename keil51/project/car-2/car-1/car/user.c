#include "REG52.h"
#include "BASIC.h"
#include "HEAD.h"
#include "delay.h"
int sum;//超声波测距结果
unsigned int mark=1;
int kkkk=0;
unsigned int limit=15;//小车与障碍物的限制限制距离
unsigned char lochoice[9]={0x00,0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};//由左到右
unsigned char displaynum[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};//0-9

int opration(int num)
{
		
	int n=0;
	if(num==0)
	{return 1;}
	while(num)
	{
		num=num/10;
		n++;
	}

	return n;
}

void display(int Data,int location)
{
	int n=0;
	int pp=0;
	for(n=location+opration(Data)-1;n>=location;n--)
{
	P0=0xFF;
	WS=1;//打开位控
	P0=lochoice[n];
	WS=0;//关闭位控
	
	pp=0;
	pp=Data%10;
	Data/=10;
	MS=1;//打开段控
	P0=displaynum[pp];
	MS=0;//关闭段控
	delayms(2);
}
}
void xunji()
{
	if(left_led==1 && right_led==1)
		back_left();
	if(left_led==1 && right_led==0)
	{left();delayms(200);}
	if(left_led==0 && right_led==1)
	{right();delayms(200);}
	if(left_led==0 && right_led==0)
		forward();
}
	
void opration1()
{
	TMOD = 0x11;//设置定时器模式
	TL1 = 0;//设置定时器初始值
	TH1 = 0;//设置定时器初始值
	
	TRIG = 1;
	Delay20us();//发射一段脉冲，至少20us
	TRIG = 0;
	while(!ECHO);//等待超声波模块返回脉冲
	TR1=1;//打开定时器
	while(ECHO);//等待超声波定时器返回脉冲结束
	TR1 = 0;//停止计数器，计时结束
	
	sum=((TH1*256+TL1)*0.034)/2+1;//计算距离
}
void judge()
{
	opration1();
	if(limit<sum&&mark==1)
	{forward();}
	if(limit>sum&&mark==1)
	{
		back_left();
		while(kkkk<100)
		{
		delayms(1);
		kkkk++;
		display(sum,5);
		}
  }
	if(le_led==0&&rg_led==1)
	{
		if(mark==1)
		{backward();delayms(500);}
		right();
		delayms(200);
		mark=0;
	}//直角右转
	if(rg_led==0&&le_led==1)
	{
		if(mark==1)
		{backward();delayms(500);}
		left();
		delayms(200);
		mark=0;
	}
		if(le_led==1&&rg_led==1&&mark==0)
		{
			forward();
			mark=1;
		}//直角左转
		if(le_led==0&&rg_led==0)
		{back_left();delayms(500);}
		kkkk=0;
		display(sum,5);
}
void magic_hand()
{
	opration1();
	if(sum>limit&&mark==1)
	{forward();display(sum,5);}
	if(sum<limit&&mark==1)
	{backward();display(sum,5);}
	if(rg_led==0&&le_led==1)
	{
		right();
		mark=0;
	}
	if(le_led==0&&rg_led==1)
	{
		left();
		mark=0;
	}
	if(rg_led==1&&le_led==1)
	{mark=1;}
}
void key_begin()	//按下松开响音
{	
	for(;;)
	{
		if(key2==0)
		{
			delayms(5);
			if(key2==0)
			{	
				delayms(10);
				beep=0;
				delayms(200);
				beep=1;
				break;
			}
		}
	}
}
