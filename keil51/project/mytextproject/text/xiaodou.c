#include <REGX52.H>
#include"delay.h"
int dou1()
{
	const char mm=0;
	if(P3_1==0)//һ��Ҫ==
			{
				delayms(20);
				while(P3_1==0);//��������
				delayms(20);//��������
			}
		return mm;
}

void dou2()
{
	if(P3_2==0)//һ��Ҫ==
			{
				delayms(20);
				while(P3_2==0);//��������
				delayms(20);//��������
			}
}