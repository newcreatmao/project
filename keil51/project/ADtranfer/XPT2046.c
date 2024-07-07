#include <REGX52.H>

sbit XPT2046_CS=P3^5;
sbit XPT2046_DCLK=P3^6;
sbit XPT2046_DIN=P3^4;
sbit XPT2046_DOUT=P3^7;

unsigned int READ(unsigned char command)//根据时序图操作
{
	int i;
	unsigned int value;
	XPT2046_CS=0;
	XPT2046_DCLK=0;
	for(i=0;i<8;i++)
	{
	XPT2046_DIN=command&(0x80>>i);//逐位发送
	
	XPT2046_DCLK=1;//将修高位发送
	//注意时间,ns可满足
	XPT2046_DCLK=0;
	}
	for(i=0;i<16;i++)
	{
	XPT2046_DCLK=1;//将修高位发送
	//注意时间,ns可满足
	XPT2046_DCLK=0;
		if(XPT2046_DOUT){value|=(0x8000>>i);}//读16位
	}
	XPT2046_DCLK=1;//结束时序
	if(command&0x08)
	return value>>8;//数据8位，但为了精确渎至16位，再移回去，0-255
	else
	return value>>4;//数据12位，0-4096
}

