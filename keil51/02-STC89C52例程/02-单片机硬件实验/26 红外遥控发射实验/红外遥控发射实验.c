/***************************************************************************
实验名称： 红外发送实验

实验模块:  	51单片机核心板、红外传输区、矩阵键盘区

实验接线：  51单片机核心板------红外传输区
					P3.5 --------- TXD				
			51单片机核心板------矩阵键盘区			
					P1	 ---------  MK1
现象描述：	1.使用另外一台试验箱的红外接收程序接收
			2.按下矩阵键盘的按键，另一台实验显示接收到按键的码值

更新时间：	2017.10.17
***************************************************************************/

#include <reg51.h>
#include "intrins.h"     //_nop_();延时函数用

#define uchar unsigned char
#define uint  unsigned int

sbit  remoteout=P3^5;        //遥控输出口

uchar IRCOM[4];

/**********************************************************/
//x*0.14MS延时
void delay(unsigned char x)
{
   unsigned char i;
   while(x--)
     {
        for (i = 0; i<13; i++) {}
     }
}

/**********************************************************/
// 1ms延时子程序
void delay1ms(int ms)
{
 unsigned char y;
  while(ms--)
 {
  for(y = 0; y<250; y++)
  {
   _nop_();
   _nop_();
   _nop_();
   _nop_();
  }
 }
}

/**********************************************************/
// 定时器初始化子程序
void clearmen()
{
   remoteout=0;           //关遥控输出
   IE=0x00;
   IP=0x01;
   TMOD=0x20;             //定时器1工作于方式2，即8位自动重装模式
   TH1=0xF4;              //38KHZ初值
   TL1=0xF4;
   EA=1;                  //开总中断
}

/**********************************************************/
//38KHZ发生器子程序
void Time1_int(void) interrupt 3 
{
   remoteout=~remoteout;
}

/**********************************************************/
// 数据发送子程序
void Transmition(unsigned char key_value)
{
    unsigned char i,j,temp;
    IRCOM[2]=key_value;
    IRCOM[3]=~key_value;
    ET1=1;TR1=1;
    delay1ms(3);    //9ms前导低电平
    ET1=0;TR1=0;
    delay1ms(1);
    delay(8);       //两个延时产生4ms结果码
    for(i=0;i<4;i++)
    {
       for(j=0;j<8;j++)
          {
             temp=(IRCOM[i]>>j)&0x01;
             if(temp==0)//发射0
                {
                   ET1=1;TR1=1;
                   delay(4);//延时0.56ms
                   ET1=0;TR1=0;
                   delay(4);//延时0.56ms
                 }
             if(temp==1)//发射1
                 {
                   ET1=1;TR1=1;
                   delay(4);//延时0.56ms
                   ET1=0;TR1=0;
                   delay(14);//延时1.48ms
                 }
          }
    }
    ET1=1;TR1=1;//结束
    delay(4);   //延时0.56ms
    ET1=0;TR1=0;//关闭红外发射
}

/**********************************************************/
// 键扫描子程序
unsigned char keyscan(void)
{
    unsigned char temp,key;
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
    return(key);
}

/*************************************************************/
//判断键是否按下
void  keydown(void)
{  
  	P1=0xF0;
   delay1ms(5);
	if(P1!=0xF0)
	{
	  keyscan();
    }
}
/**********************************************************/

/**********************************************************/
main()
{
   IRCOM[0]=0x00;IRCOM[1]=0xFF;IRCOM[2]=0x48;IRCOM[3]=0xB7;
   clearmen();
   while(1)
     {
        keydown();
        if(keyscan()!=0xFF) Transmition(keyscan());
     }
}