#include <REGX52.H>
#include <INTRINS.H>
#include"delay.h"
unsigned char mod=0;
void uart()
{
	PCON |= 0x80;		//波特率倍速
	SCON = 0x40;		//8位数据,可变波特率,允许接收
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF3;		//设置定时初始值
	TH1 = 0xF3;		//设置定时重载值
	ET1 = 0;		//禁止定时器ET1中断，开启中断接收会增大误差
	TR1 = 1;		//定时器1开始计时

}
void timer()
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	TL0 = 0x18;
	TH0 = 0xFC;
	TF0 = 0;
	TR0 = 1;
	
	ET0 = 1;
	EA = 1;
  PT0  = 0;	
}


void sendbyte(unsigned char byte)
{
	SBUF=byte;//SBUF数据接收器
	while(TI==0);//TI发送标志位，0为等待发送数据，1为发送完成
	TI=0;
}

int main ()
{	
	P2=0xFE;
	timer();
uart();
	while(1)
	{
		if(P3_1==0)
		{
			delayms(20);
			while(P3_1==0);
			delayms(20);
			mod++;
			mod%=2;
		}
	}
}

void Timer0_Routine() interrupt 1
{	
	static unsigned int Tcount;
	TL0 = 0x18;
	TH0 = 0xFC;
	
	Tcount++;

	if(Tcount>=500)//500ms
	{	sendbyte(mod);
		Tcount=0;
	if(mod==0)
	{
		P2=_crol_(P2,1);
	}
	if(mod==1)
	{
	P2=_cror_(P2,1);
	}}
}

