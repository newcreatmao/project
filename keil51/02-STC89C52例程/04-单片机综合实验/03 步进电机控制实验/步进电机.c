/***************************************************************************
实验名称： 	步进电机实验

实验模块:  51单片机核心板、步进电机区、矩阵键盘区、12864显示区

实验接线：  51单片机核心板------步进电机区
					P3.0----------------A
					P3.1----------------B
					P3.2----------------C
					P3.2----------------D
					
			51单片机核心板------矩阵键盘区
					P1----------------MK1
					
			51单片机核心板----------12864显示区
					 P2.0--------------CS1
					 P2.1--------------CS2
					 P2.2--------------CS
					 P2.3--------------RW
					 P2.4--------------E
				P0.0~P0.7--------------DB0~DB7	

				
现象描述：	按动矩阵键盘的按键，控制步进电机

更新时间：2017.10.23
***************************************************************************/


#include<reg52.h>
#include<12864.c> 
#define uint unsigned int 
#define uchar unsigned char 
uchar  key=0;
uchar  temp;

sbit ap = P3^0;
sbit bp = P3^1;
sbit cp = P3^2;
sbit dp = P3^3;


void mDelay(uint Delay)	//延时
{
	uint i;
	for(;Delay > 0;Delay--)	 
		for(i = 0;i < 110;i++);
}
void ff_setp()
{
	ap = 1;
	bp = 0;
	cp = 0;
	dp = 1;
	mDelay(10);
	bp = 1;
	dp = 0;
	mDelay(10);
	cp = 1;
	ap = 0;
	mDelay(10);
	dp = 1;
	bp = 0;
	mDelay(10);	
}

void bw_setp()
{
	ap = 1;
	bp = 1;
	cp = 0;
	dp = 0;
	mDelay(10);
	bp = 0;
	dp = 1;
	mDelay(10);
	ap = 0;
	cp = 1;
	mDelay(10);
	dp = 0;
	bp = 1;
	mDelay(10);		
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
    }
 }
void init()
{

	LCD12864_Init();
	LCD12864_Clear();
	Display();
	ap = 1;
	bp = 1;
	cp = 1;
	dp = 1;

}
void main()
{
	uchar t=10;
	uchar kt=0,zf=0;
	init();
	while(1)
	{
		keydown();
		display(key);
		switch(mm[key])
		{
			case 0:
				kt=1;
				break;	
			case 2:
				t-=5;
				break;	
			case 4:
				zf=0;
				break;	
			case 5:
				kt=0;
				break;	
			case 6:
				zf=1;
				break;	
			case 8:
				t+=50;
				break;	
			default:	
				break;
	
		}
		if(kt)
		{
			if(zf)
				ff_setp();				
			else
				bw_setp();
			mDelay(t);
		}
	}

}







