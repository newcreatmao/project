/***************************************************************************
实验名称： 并行转串行实验

实验模块:  51单片机核心板、并行转串行区、拨码开关区、LED显示区

实验接线：  51单片机核心板------并行转串行区
					P1.0---------SLK
					P1.1---------SDA
					P1.2---------SFT_LD
					
			51单片机核心板------LED显示区
					P0  ---------J4
					
			并行转串行区------拨码开关区
					J8	--------- J1
						
现象描述：	拨动开关SW1~SW8控制LED灯D1~D8的亮灭

更新时间�	�2017.10.17
***************************************************************************/

#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
                                                   
sbit CLK = P1^0;
sbit SDA = P1^1;
sbit SF  = P1^2;


void mDelay(uint Delay)	//延时
{	uint i;
	for(;Delay > 0;Delay--)
		for(i = 0;i < 110;i++);
}

uchar receive() 	   //收取字节的程序
{     
	uchar byte = 0,c;  
	for(c = 0; c < 8; c++) 		
	{ 
		byte = byte<<1; 		//数据左移一位
		CLK = 1;
		CLK = 0;
		if(SDA) 				//收取最低位数据
			byte = byte|0x01; 		
		CLK = 1;

	       
	} 
	return(byte);
} 


void main() //主程序
{
	uchar a = 0;
	while(1)
	{
		SF = 1;			   		//锁入数据
		SF = 0;
		SF = 1;
		a = receive();
		P0 = a;
 
	}
}

