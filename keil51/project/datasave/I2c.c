//六个模块
#include <REGX52.H>
sbit SCL = P2^1;
sbit SDA = P2^0;
//除写周期需要5ms外，其余的操作时间都很短，对于51不需要延时

//开始
void start()
{
	SCL=SDA=1;//确保SDA和SCL为高，相当于初始化
	SDA=0;
	SCL=0;//注意要按时序图的顺序
}

//停止
void stop()
{
	SDA=0;
	SCL=1;
	SDA=1;
}

//发送一个bit
void sendbyte(unsigned char byte)
{
	int i;
	for(i=0;i<8;i++)
	{
	SDA=byte&(0x80>>i)://取最高位
	SCL=1;
	SDA=0;
	}
}

//接收一个bit
unsigned char receivebyte()
{
	unsigned char byte=0x00,i;//初始化byte才能结合下面的sda判断
	
	SDA=1;//释放总线，好让从机操作总线，要不从机传输的都是0，程序控制的主要是主机
	for(i=0;i<8;i++)
	{
		//在这里面读数据是从sda上读
	SCL=1;//scl拉高后sda的值变为数据的最高位，每次scl拉高，sda接收对应位置的数据
	if(SDA){byte|=(0x80>>i);}//SDA返回的输入的数据也是010101的，故只需要判断sda值就可将一个byte的值逐个接收，是1则按位给1
	//现在需要读取从机返回的数据，从机现在控制sda，所以需要把sda的状态写进byte中，主机读取byte即可直到从机返回的值了
	SCL=0;
	return byte;
	}
}

//发送应答
void endack(unsigned char ack)
{
	SDA=ack;
	SCL=1;
	SCL=0;
}

//接收应答
unsigned char receiveack()
{
	unsigned char ackbit;
	SDA=1;
	SCL=1;
	if(SDA)ackbit=1;
	SCL=0;
	return ackbit;//0为应答，1为无应答
}