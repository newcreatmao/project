/***************************************************************************
实验名称： 1602字符显示实验

实验模块:  51单片机核心板、液晶显示区

实验接线： 51单片机核心板------液晶显示区
				 P3.0--------------RS
				 P3.1--------------RW
				 P3.2--------------E
			P0.0~P0.7--------------DB0~DB7
				
						
现象描述：1602 显示测试字符

更新时间：2017.10.17
***************************************************************************/
#include<reg52.h>		//添加库文件
#define uint unsigned int
#define uchar unsigned char

sbit E = P3^2;			//定义管脚
sbit RW = P3^1;
sbit RS = P3^0;

void mDelay(uint Delay)	//延时
{	uint i;
	for(;Delay > 0;Delay--)
		for(i = 0;i < 110;i++);
}


void LCD1602Write_data(uchar i)	//LCD1602写数据
{
	//E=0;
	RS = 1;//数据
	RW = 0;//写入
	P0 = i;
	E = 1;//允许
	mDelay(11);
	E = 0;
             
    
}
void LCD1602Write_com(uchar i)	//LCD1602写指令
{

	RS = 0; //指令
	RW = 0; //写入
	P0 = i;
	E = 1;  //允许写入
    mDelay(11);
	E = 0;          
}
void LCD1602Init()		 //LCD1602初始化
{
	RW = 0;
	RS = 0;
	LCD1602Write_com(0x01);
	LCD1602Write_com(0x38);
	LCD1602Write_com(0x0c);		//无光标
	LCD1602Write_com(0x06);	
}

void main()				//主函数
{
	unsigned char Code1[] = "1602 LCD TEST OK";//Code1是要显示在字符液晶的第一行
	unsigned char Code2[] = "HELLO EVERYONE!!"; //Code2是要显示在字符液晶的第二行
 	unsigned char m;
	RW = 0;
	LCD1602Init();
	while(1)
	{ 
		LCD1602Write_com(0x80+0x00);	//在第一行第一个显示Code1
		for(m = 0;m < 40;m++)			
	   {
			LCD1602Write_data(Code1[m]);

			mDelay(10);			//延时
       }
	LCD1602Write_com(0x80+0x40);		//在第二行第一个显示Code2
		for(m = 0;m < 40;m++)			
	   {
			
			LCD1602Write_data(Code2[m]);	
			mDelay(10);			//延时
}		
    }
}