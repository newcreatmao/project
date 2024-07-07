/***************************************************************************
实验名称： 超声波测量实验

实验模块:  51单片机核心板、超声波传感器模块

实验接线： 51单片机核心板------超声波传感器模块
				 P3.0--------------IN
				 P3.1--------------BEEP
				 P3.2--------------OUT
			
			P0.0~P0.7--------------A~DP
			P2.0~P2.3--------------COM1~COM3		
						
现象描述：12864显示测试字符

更新时间：2017.10.17
***************************************************************************/
//**************头文件************//
#include <reg52.h>
#include <intrins.h>
#include <math.h>
#define	uchar unsigned char
#define	uint  unsigned int 
sbit been=P3^1;
sbit P30=P3^0;//555控制收发位
//**********变量定义**************//
float distance;
float dis1; 
uchar high_time,low_time;
bit flag=0;//标志位


#define DIGI P0 //宏定义，将P0口定义为数码管
#define SELECT P2 //宏定义，将P2定义为数码管选择口

uchar code tab[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7f,0x6f};
uchar select[]={0x01,0x02,0x04,0x08}; //选择数码管数组，依次选择1，2，..，



//******延时n个ms函数*****************//
void delay_nms(uint ms)   //delay ms function                              
{   uchar i; 
    while(ms--)
   {
    for(i = 0; i < 100; i++);
   }
}
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
		dis=(uint)dis2;
		SELECT=select[0]; //选择第i个数码管
		DIGI=tab[dis/1000];
		delay1(500);
		SELECT=select[1]; //选择第i个数码管
		DIGI=tab[dis/100%10];
		delay1(500);
		SELECT=select[2]; //选择第i个数码管
		DIGI=tab[dis/10%10];
		delay1(500);
		SELECT=select[3]; //选择第i个数码管
		DIGI=tab[dis%10];
//		delay1(500);

}

//***********初始化*******************//             
void init()
{  
//******** 定时器0****************//
   	TMOD=0x11;//定时器0方式1用于计时
	TH0=0; //定时器初始化
	TL0=0;
//	ET0=1;
	TR0=0;//暂且关闭定时器0	       
//*********总中断****************//	
	EA=1; //开总中断
//*********外中断1***************//
    IT0=1;//下降沿有效,左传感器
	      
}
//**********  距离计算函数********//
float Distance_count()
{
  float temp;
  temp=high_time*256+low_time;//时间为微秒级
  temp=(temp/10000)/2;//单位转换	
  temp*=344; //距离计算，S=V*T
  return temp;
}
//****** 左发生超声波函数*******//   
void tran()
{
	TH0=0;
	TL0=0;//清定时0
	P30 = 1;
	TR0=1;//开定时0	
	EX0=1;
	delay1(4*4);
	P30 = 0;
	delay_nms(5*4);
	if(flag==1) //是否有中断触发？
	{
		distance=Distance_count();//有触发则调用距离计算函数
		dis1=distance*10;
		flag=0;
	}
	else 
		dis1=0;
	if(dis1<110&&dis1>10)
	{
		been=~been;
		delay_nms(50);
	}
	else	been=0;
}
//**************主函数****************//

void main()
{ 

	init();//函数初始化
	while(1)
	{	
   		display(dis1);
		tran();
	}
} 
//*************外部中断计数器0*********//
 void TT() interrupt 0
{
	unsigned int tmp;
	TR0=0;//关定时器0
	ET0=0;//关外部中断
	flag=1;//外部中断标志位
	tmp=TH0*256+TL0; //处理外部中断 
	if((tmp>0)&&(tmp<5174))	
     {
	  high_time=TH0;
	  low_time=TL0;	
	}
	else 
	{
	 high_time=0;
	 low_time=0;	
	} 

}
 
