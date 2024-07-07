#include <REGX52.H>
#include"delay.h"
int dou1()
{
	const char mm=0;
	if(P3_1==0)//一定要==
			{
				delayms(20);
				while(P3_1==0);//按下消抖
				delayms(20);//松手消抖
			}
		return mm;
}

void dou2()
{
	if(P3_2==0)//一定要==
			{
				delayms(20);
				while(P3_2==0);//按下消抖
				delayms(20);//松手消抖
			}
}