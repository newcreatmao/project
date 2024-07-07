/***************************************************************************
实验名称：  直流电机测速实验程序 

实验模块�	51单片机核心板、直流电机区、LCD12864显示区 、简易扩展IO区、矩阵键盘区

实验接线：	 51单片机核心板------LCD12864显示区
				   P2.0--------------CS1
				   P2.1--------------CS2
				   P2.2--------------CS
				   P2.3--------------RW
				   P2.4--------------E
			  P0.0~P0.7--------------DB0~DB7
				
			 51单片机核心板------简易扩展IO区		
				  P3.0--------------A0				   						 
				  P3.1--------------A1
					   
					T/R接+5V  nOE 接GND
			 51单片机核心板------直流电机区	   
				 P3.2--------------SPEED
			 简易扩展IO区 ------  直流电机区 
				  B0--------------MOTO1
				  B1 --------------MOTO2
			51单片机核心板------矩阵键盘区
				  P1 -------------- MK1
				  
现象描述按动矩阵键盘相应按键，直流电机执行相关功能。
		  

更新时间：2017.08.18
***************************************************************************/ 


#include <reg52.h> 
#include<12864.c>    
#define uchar unsigned char
#define uint unsigned int

#define CIRCLE 25  //速度可调节的档位设置

uchar count=1,last=10;
uchar temp,key;
uint time,speed;
bit  PWM,flag=0;
uchar kt=0;
sbit Moto1 = P3^0;
sbit Moto2 = P3^1;

void mDelay(uint Delay)	//延时
{
	uint i;
	for(;Delay > 0;Delay--)	 
		for(i = 0;i < 110;i++);
}
void Timer0(void) interrupt 1  //定时器0溢出中断服务子程序，用于产生PWM波
{
   count++;
   if(count>CIRCLE) 
     {
        count=1;
     } 
   if(count<=last)
      PWM=0;
   else 
      PWM=1;
   TH0=0xFC;
   TL0=0x66;
}

void INT_0 (void) interrupt 0  //外部中断0中断服务子程序，用于记录测速器模块产生的脉冲数目
{
   EX0=0;    //禁止外部中断0中断
   time++;
   EX0=1;    //允许外部中断0中断
}



void Timer1 (void) interrupt 3 //定时器1溢出中断服务子程序，用于获取速度值
{
   TH1=0x4C;      //重装定时初值
   TL1=0x00;      //50ms定时
   time=time*300;        //防止个位被去除
   speed=(time/3)*20;    //速度：r/s
   speed=speed/300;
   time=0;
}


void INT_Init() //系统初始化函数，初始化定时器T0、T1和外部中断0
{
   TMOD=0x10;     //选择T1工作于方式1
   TH1=0x4C;
   TL1=0x00;      //50ms定时
   ET1=1;         //允许T1中断
   TR1=1;         //启动T1中断

   ET0=1;         //允许T0中断
   TH0=0xFC;
   TL0=0x66;
   TR0=1;         //启动T0中断

   IT0=1;         //下降沿触发
   EX0=1;         //允许外部中断0中断

   EA=1;          //开所有中断

   	LCD12864_Init();
	LCD12864_Clear();
	Display();
}

/**********************************************************/
// 键扫描子程序
void  keyscan(void)
 { 
    P1=0xF0;                //行线为输入，列线为输出，并置列线输出全为0
	temp=P1;                //读P1口       
    temp=temp&0xF0;
    temp=~((temp>>4)|0xF0);
    if(temp==1)
        key=0;
    else if(temp==2)
        key=1;
    else if(temp==4)
        key=2;
    else if(temp==8)
        key=3;
    P1=0x0F;                 //列线为输入，行线为输出，并置行线输出全为0  
	 temp=P1;                 //读P1口 
    temp=temp&0x0F;
    temp=~(temp|0xF0);        
    if(temp==1)
        key=key+0;
    else if(temp==2)
        key=key+4;
    else if(temp==4)
        key=key+8;
    else if(temp==8)
        key=key+12;

	while(temp)
	{
		P1=0x0F;                 
		temp=P1;                
		temp=temp&0x0F;
		temp=~(temp|0xF0); 
	}

 }

/*************************************************************/
//判断键是否按下
void  keydown(void)
 {  

  	P1=0xF0;
    mDelay(5);
	if(P1!=0xF0)
	{
	  keyscan();
	  	switch(mm[key])
		{
			case 0:
				kt=1;
				break;	
			case 2:
				last--;
				if(last<1)
					last=25;
				break;	
			case 4:
				flag=0;
				break;	
			case 5:
				kt=0;
				break;	
			case 6:
				flag=1;
				break;	
			case 8:
				last++;
				if(last>=25)
					last=1;
				break;	
			default:	
				break;
			
		}
    }
 }
void main(void)   //主函数
{

	INT_Init();
	while(1)
	{
		keydown();
		display(key,speed);
		if(kt)
		{		
			if(flag)//正传
			{
				Moto1=PWM;
				Moto2=0;
			}
			if(!flag)//反传
			{
				Moto2=PWM;
				Moto1=0;
			}
		}
		else 
		{
			Moto2=0;
			Moto1=0;			
		}
	}
}