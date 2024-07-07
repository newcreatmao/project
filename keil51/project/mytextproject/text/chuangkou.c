#include <REGX52.H>
void UartInit(void)		//4800bps@11.0592MHz，51单片机是低功率的，要用8位定时器计算
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率,允许接收
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;		//设置定时初始值
	TH1 = 0xFA;		//设置定时重载值
	ET1 = 0;		//禁止定时器%d中断
	TR1 = 1;		//定时器1开始计时
	EA=1;//使能中断
	ES=1;//使能中断
}
void sendbyte(unsigned char byte)
{
	SBUF=byte;
	while(TI==0);
	TI=0;
}