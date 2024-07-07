#include <REGX52.H>
#include "Delay.h"
#include "EX0.h"

unsigned char i,Mode=0;


void LED_1()
{
	
	for(;i<8;i++)
	{
		if(i==7)
			i=0;
		if(Mode){	//模式1
			P2=~(0x01<<i);
			Delay(30);
		}
		else 
		{
			i=7-i;
			break;
		}
		//模式0则退出LED_1
	}
}


void LED_0()
{
	for(;i<8;i++)
	{	
		if(i==7)
			i=0;
		if(Mode==0){
			P2=~(0x80>>i);
			Delay(30);
		}
		else 
		{
			i=7-i;
			break;
		}
	//模式1则退出LED_0
	}
}

void main()
{

	EX0_Init();
	
	while(1)
	{
		if(Mode==0)LED_0();	//右往左
		if(Mode==1)LED_1();	//左往右
	}
}

void EX0_ISR() interrupt 0
{
	if(P3_2==0){		//按键消抖
		Delay(10);		//不消抖可能导致重复进入中断
		while(P3_2==0);
		Delay(10);
		
//		if(Mode)Mode =0;	//模式转换
//		else Mode=1;
		Mode=(Mode+1)%2;	//模式(0、1)切换

//三个模式:
//		Mode=(Mode+1)%2;	//模式(0、1、2)
//		Mode=(Mode+1)%2+1;	//模式(1、2、3)
	}

}
//Mode = ~Mode;		计算错误（Mode为 un char型)  ~0 = 1111 1111  ~1=1111 1110









