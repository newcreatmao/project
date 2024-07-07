#include <REGX52.H>
#include"delay.h"
#include"shuma.h"
#include"chuangkou.h"
#include"color.h"
#include"link.h"
void six()
{
	unsigned char show_mode = 0;//在静态显示下，选择显示年月日/时分秒/电压
	unsigned char input_mode = 0;
	unsigned int Data;
	float VccData = 0;
	int i = 0;
	init();
	settime();
	show_mode++;
	while(1)
	{
		readtime();
		Data = XPT2046_ReadAD(XPT2046_XP);
			if(show_mode == 0)
			{
				ymd();//年 月 日
			}
			else if(show_mode == 1)
			{
				hms();// 时 分 秒
			}
			else if(show_mode ==2)
			{
				ad(VccData);//电压
				VccData = Data/255.0 * 3.3;
				VccData *= 100;
			}
			show_mode %= 3;
		//按键消抖
			if(P3_1 == 0)
		{
			delayms(20);
			while(P3_1==0);
			delayms(20);
			show_mode += 1;
		}
	}
}

int  main()//执行完后又重新执行
{
	while(1)
	{
		char k=0;
		for(k=0;k<8;k++)
		{
			P0=~(0x01<<k);
			delayms(500);
		}
		for(k=6;k>0;k--)
		{
			P0=~(0x01<<k);
			delayms(500);
		}
	}
}
