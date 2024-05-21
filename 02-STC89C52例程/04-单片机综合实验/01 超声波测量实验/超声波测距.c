
//**************头文件************//
#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include <math.h>
//#include "1602.c" //1602显示函数
#include "12864.c" //12864显示函数
#define	uchar unsigned char
#define	uint  unsigned int 
sbit been=P3^1;
//sbit P37=P3^0;//555控制收发位
//**********变量定义**************//
float distance;
float dis1; 
uchar high_time,low_time;
bit flag=0;//标志位
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
//***********初始化*******************//             
void init()
{  
//******** 定时器0****************//
   	TMOD=0x01;//定时器0方式1用于计时
	TH0=0; //定时器初始化
	TL0=0;
	TR0=0;//暂且关闭定时器0	       
//*********总中断****************//	
	EA=1; //开总中断
//*********外中断1***************//
    IT0=1;//下降沿有效,左传感器
//    LCD_init();
	LCD12864_Init();
	LCD12864_Clear();
	Display();
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
	P37 = 1;
	TR0=1;//开定时0	
	EX0=1;
	delay1(4*4);
	P37 = 0;
	delay_nms(5*4);
	if(flag==1) //是否有中断触发？
	{
		distance=Distance_count();//有触发则调用距离计算函数
		dis1=distance;
		flag=0;
	}
	else 
		dis1=0;
}
//**************主函数****************//

void main()
{ 

	init();//函数初始化
	while(1)
	{	
		tran();
		dis1 *= 10;


		if(dis1<110&&dis1>10)
		{
			been=~been;
			delay_nms(50);
		}
		else	been=1;
/*
//****************1602显示函数*************************			  
		sprintf(dis,"Measure distance"); 			//*
		DispStrPosi(dis,0,0);						//*
		sprintf(dis,"Range=%0.1f mm  ",dis1);		//*
		DispStrPosi(dis,0,1);						//*
		delay_nms(100);								//*
													//*
//*****************************************************
*/


//****************12864显示函数************************			  
		display(dis1*10);							//*
		delay_nms(10);								//*
//*****************************************************



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


 
  
