/*#include <REGX52.H>
#include"delay.h"
sbit LED=P2^0;

int main ()
{
	unsigned char time,i;
	while(1)
	{
		for(time=0;time<100;time+=5)
		{
			for(i=0;i<20;i++)
			{
		LED=0;
		delayms(time);
		LED=1;
		delayms(100-time);//延时和为定值即周期固定，占空比即为两时间的比值
			}
	}}
			for(time=0;time<100;time+=5)
		{
			for(i=0;i<20;i++)
			{
		LED=1;
		delayms(time);
		LED=0;
		delayms(100-time);//延时和为定值即周期固定，占空比即为两时间的比值
			}
	}}

}
*/