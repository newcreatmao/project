/***************************************************************************
实验名称： 模拟电压测量实验（串行）

实验模块:  51单片机核心板、动态扫描数码管区、串行A/D转换区、可调电压区

实验接线：  51单片机核心板------串行A/D转换区
					P3.0----------------CLK
					P3.1----------------SDA
					P3.2----------------nCS
					
			51单片机核心板------动态扫描数码管区
					P0----------------J6
					P2----------------J5
			可调电压区------串行A/D转换区
				TESE-1----------------IN
				
现象描述：	调节可调电压区的旋钮，数码管显示对应的电压值

更新时间：2017.10.18
***************************************************************************/


#include<reg52.h>
#include <math.h>
#define	uchar unsigned char
#define	uint  unsigned int 

sbit CLK = P3^0;  //时钟端口
sbit SDA = P3^1;  //数据端口
sbit CS  = P3^2;  //片选端口


#define DIGI P0 //宏定义，将P0口定义为数码管
#define SELECT P2 //宏定义，将P2定义为数码管选择口

uchar code tab[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7f,0x6f};
uchar select[]={0x01,0x02,0x04,0x08}; //选择数码管数组，依次选择1，2，..，

//**********延时n个us函数**********************//
void  delay1(unsigned int delus)//1us
{  
  while(delus!=0)
	{ 
	 delus--;
	}
}

void display(float dis2) //函数
{

		uint dis;
		dis2*=5000;
		dis=(uint)dis2;
		SELECT=select[3]; //选择第i个数码管
		DIGI=tab[dis/1000];
		delay1(500);
		SELECT=select[2]; //选择第i个数码管
		DIGI=tab[dis/100%10];
		delay1(500);
		SELECT=select[1]; //选择第i个数码管
		DIGI=tab[dis/10%10];
		delay1(500);
		SELECT=select[0]; //选择第i个数码管
		DIGI=tab[dis%10];
//		delay1(500);

}
//******************************************************
//延时子程序
void delay(unsigned int x)
{
	unsigned int y=x;
	do{y--;}
   while(y>1);
}

//******************************************************
//读取转换数值
unsigned int read()
{
 	unsigned int i=0,value=0;
	delay(2);
	for(i=0;i<8;i++)
	{
		CLK=1;	         //产生上升沿
		value=value<<1;  //数据左移一位
		if(SDA==1)
         value=value+1;  //读取数值
		CLK=0;
	}
	return value;        //返回数据
}

//******************************************************
void main()
{
	uint data2=0;
	float data1=0;
	CLK=0;             //初始化时钟端口
	CS=1;        //片选	
	while(1)
	{
		CS=1;        //片选
		delay(100);    //等待转换
		CS=0;
		data2=read();//读取转换数据	
		data1=data2/255.0;
		display(data1);
	}
}




