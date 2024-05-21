/***************************************************************************
实验名称： 并行AD转换实验

实验模块:  51单片机核心板、LED示区、并行A/D转换区

实验接线：  51单片机核心板------并行A/D转换区
					 P0   ---------  J36
					 P2.0 --------- START
					 P2.1 ---------	EOC  
					 P2.2 --------- OE 
					 P2.3 --------- ALE
					 
			51单片机核心板------LED示区
					 P1  ---------  J4	
						
现象描述：	转换结果直接以二进制形式在LED上显示。可调节电位器改变输入的模拟量

更新时间：  2017.10.17
***************************************************************************/

#include <reg52.H>

sbit START = P2^0;
sbit EOC = P2^1;
sbit OE  = P2^2;
sbit CLK = P2^3;
unsigned char getdata;

/************************************************/
//定时器初始化
void init()
{
        TMOD= 0x03;// 定时器0工作方式3
        TH0 = 0xff;// 定时器0赋初值
        TL0 = 0x00;
        TR0 = 1;
        ET0 = 1;
        EA  = 1;
}

/***********************************************/
//软件延时产生ADC0809的时钟
void clk() interrupt 1
{ 
        CLK=(~CLK);
}


/************************************************/
//AD转换函数
unsigned char ADC()
    {
         char value;
		 START=0; 
		 START=1;      //开始转换命令
		 START=0;
		 while(EOC==0);//等待转换结束
		 OE=1;
		 value=P0;
		 OE=0;
         return value;
     }


/************************************************/
void main()
{
    init();
    START = 1;       // ST端产生正脉冲
    START = 0;
    while(1)
	{
		P1=~ADC();//输出转换得到的数据
	}
}

