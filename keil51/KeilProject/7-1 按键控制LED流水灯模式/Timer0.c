#include <REGX52.H>

/**
  * @brief  定时器0初始化，1毫秒@12.000MHz
  * @param  无
  * @retval 无
  */
void Timer0Init(void)//在定时器计算机可找该代码
{
	TMOD &= 0xF0;		//设置定时器模式，把TMOD的低四位清零，高四位保持不变
	TMOD |= 0x01;		//设置定时器模式，把TMOD的最低位置1，高四位不变
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	ET0=1;//打开中断开关
	EA=1;//打开总中断
	PT0=0;//中断优先级
}

/*定时器中断函数模板
void Timer0_Routine() interrupt 1 //interrupt 跳转指向
{
	static unsigned int T0Count;
	TL0 = 0x18;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=1000)
	{
		T0Count=0;
		
	}
}
*/
