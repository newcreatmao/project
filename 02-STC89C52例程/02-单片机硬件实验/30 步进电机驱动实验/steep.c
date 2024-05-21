/***************************************************************************
实验名称： 	步进电机驱动实验

实验模块:  	51单片机核心板、步进电机区、拨码开关区

实验接线：  51单片机核心板 --------- 步进电机区
					P0.0 ------------ A
					P0.1 ------------ B
					P0.2 ------------ C
					P0.3 ------------ D
					
			51单片机核心板 --------- 拨码开关区
					P0.4 ------------  SW1

现象描述：	步进电机根据SW1的设置顺时针转动或逆时针转动

更新时间：	2017.10.17
***************************************************************************/

#include<reg52.h> 
#define uint unsigned int 
#define uchar unsigned char 

// 定义步进电机的四相控制
sbit ap = P0^0;
sbit cp = P0^1;
sbit bp = P0^2;
sbit dp = P0^3;
// 定义正反转控制
sbit tp = P0^4;

void mDelay(uint Delay)	//延时
{
	uint i;
	for(;Delay > 0;Delay--)	 
		for(i = 0;i < 210;i++);
}

void ff_setp()
{
	ap = 1;
	bp = 0;
	cp = 0;
	dp = 1;
	mDelay(10);
	bp = 1;
	dp = 0;
	mDelay(10);
	cp = 1;
	ap = 0;
	mDelay(10);
	dp = 1;
	bp = 0;
	mDelay(10);	
}

void bw_setp()
{
	ap = 1;
	bp = 1;
	cp = 0;
	dp = 0;
	mDelay(10);
	bp = 0;
	dp = 1;
	mDelay(10);
	ap = 0;
	cp = 1;
	mDelay(10);
	dp = 0;
	bp = 1;
	mDelay(10);		
}


void main()
{
	ap = 1;
	bp = 1;
	cp = 1;
	dp = 1;

	while(1)
	{ 
		if(!tp)
			ff_setp();
		else
			bw_setp();
	  mDelay(300);		// 延时，调整电机转速
	  	
	}

}







