#include <REGX52.H>

void EX0_Init(void)
{
			//设置触发方式 外部中断0
	IT0=1;  //设置下降沿触发TCON 硬件可自动清零触发信号
 	EX0=1; //IE
	EA=1;
}