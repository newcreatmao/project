/***************************************************************************
实验名称： 逻辑驱动型蜂鸣器实验

实验模块:  51单片机核心板、蜂鸣器区

实验接线： 51单片机核心板------蜂鸣器区

				P1.0------------------PUL
						
现象描述：蜂鸣器间断性鸣响

更新时间：2017.10.17
***************************************************************************/



#include<intrins.h>			  
#include<reg52.h>	\
#define uint unsigned int 
#define uchar unsigned char 
sbit P1_0 = P1 ^ 0;    		//定义管脚

void mDelay(uint Delay)		//延时
{	uint i;
	for(;Delay > 0;Delay--)
		for(i = 0;i < 110;i++);
}

main()
{
	while(1)
	{
		P1_0 = ~P1_0;							 //蜂鸣器间断报鸣
		mDelay(100);							 //产生报鸣的延迟
	}
}


