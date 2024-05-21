/***************************************************************************
实验名称： 数码管动态扫描实验

实验模块:  51单片机核心板、动态扫描数码管区

实验接线：  51单片机核心板------动态扫描数码管区
					P0----------------J6
					P2----------------J5
						
现象描述：	8位数码管从左向右依次显示“0~7”

更新时间：2017.10.17
***************************************************************************/


#include <REGX51.H>
#define uchar unsigned char 	//宏定义，为方便编程
#define uint unsigned int
#define DIGI P0 				//宏定义，将P0口定义为数码管段选接口
#define SELECT P2 				//宏定义，将P2定义为数码管选择口

uchar digivalue[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07};
//显示的数字数组，依次为0，1，..，7
uchar select[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; //选择数码管数组，依次选择1，2，..，8

uchar sno[]={2,2,3,4,0,2,2,5};
uchar date[]={2,0,2,4,0,5,2,1};

void Timer0_Init(void)		//100??@11.0592MHz
{
	TMOD &= 0xF0;			//???????
	TL0 = 0x70;				//???????
	TH0 = 0xDD;				//???????
	TF0 = 0;				//??TF0??
	TR0 = 1;				//???0????
}

void delay() //延迟函数，决定数码管跳变的间隔时间
{ 
	uchar ii=200; //若发现数码管闪烁，调节这里即可
	while(ii--);
}

main() //主函数
{
	uchar i=0;
	while(1)
	{ 
		if(P1_0==0){
		for(i=0;i<8;i++) 		//8个数码管轮流显示
		{
			SELECT=select[i]; 	//选择第i个数码管
			DIGI=0x90;
			DIGI=digivalue[sno[i]]; 	//显示i
			delay();
		} 
	  }
		else if(P1_0==1){
		for(i=0;i<8;i++) 		//8个数码管轮流显示
		{
			SELECT=select[i]; 	//选择第i个数码管
			DIGI=0x90;
			DIGI=digivalue[date[i]]; 	//显示i
			delay();
		} 
		}
	}
}

void user() interrupt 1
{
	TL0 = 0x70;				//???????
	TH0 = 0xDD;				//???????
}
