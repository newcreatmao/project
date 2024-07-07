#include <REGX52.H>
//发数据给单片机
void uart()
{
	PCON |= 0x80;		//波特率倍速
	SCON = 0x40;		//8位数据,可变波特率,允许接收
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF3;		//设置定时初始值
	TH1 = 0xF3;		//设置定时重载值
	ET1 = 0;		//禁止定时器ET中断，开启中断接收会增大误差
	TR1 = 1;		//定时器1开始计时

}
void UartInit(void)		//4800bps@11.0592MHz，51单片机是低功率的，要用8位（0-255，将两寄存器分开，自动重装）定时器计算
{//定时器1
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50;		//8位数据,可变波特率,允许接收
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xFA;		//设置定时初始值
	TH1 = 0xFA;		//设置定时重载值
	ET1 = 0;		//禁止定时器ET中断，开启中断接收会增大误差
	TR1 = 1;		//定时器1开始计时
	EA=1;//使能定时器中断
	ES=1;//使能串口中断
}
void sendbyte(unsigned char byte)
{
	SBUF=byte;//SBUF数据接收器
	while(TI==0);//TI发送标志位，0为等待发送数据，1为发送完成
	TI=0;
}
/*void routine() interrupt 4
{
	if(RI==1)
	{
		P2=SBUF;
		sendbyte(P2);
		RI=0;
	}

}*///使用时放入主函数中即可