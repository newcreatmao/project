/***************************************************************************
实验名称： 串行转并行实验

实验模块:  51单片机核心板、串行转并行区、LED显示区

实验接线： 51单片机核心板------串行转并行区
					P1.0---------SCK
					P1.1---------SDA
			串行转并行区------LED显示区
					 J10---------J4
现象描述：LED显示的数据进行累加

更新时间：2017.10.17
***************************************************************************/
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
                                                   
sbit CLK = P1^0;
sbit SDA = P1^1;



void mDelay(uint Delay)			//延时
{	uint i;
	for(;Delay > 0;Delay--)
		for(i = 0;i < 110;i++);
}

void sendbyte(uchar byte) 	   //发送字节的程序
{     
	uchar c;  
	for(c = 0; c < 8; c++) 		//发送8位段码
	{ 
		CLK = 0; 
		SDA = byte&0x80; 		//发送最高位数据
		CLK = 1; 
		byte<<=1; 				//数据左移一位
	       
	} 
} 


void main() //主程序
{
	uchar h = 0;
	while(1)
	{
		for(h = 0; h < 256; h++){   //发送的数据依次加1
			mDelay(50);				//调用延时程序，延时50毫秒 
			sendbyte(~h); 	 		//调用发送字节的程序
			mDelay(500);			//调用延时程序，延时500毫秒 
		} 
	}
}