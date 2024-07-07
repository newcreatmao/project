#include <REGX52.H>
#include "basic.h"
#include <intrins.h>
#include "delay.h"

sbit Dl = P2^7;
sbit Dr = P2^6;//1为黑（即光反射回来），0为白

void car_go()
{
	car_lf_go();
	car_rg_go();
}

void xunji()
{	
	if(Dl==1&&Dr==1)
	{car_go();}
	if(Dl==1&&Dr==0)//中间左侧检测到黑线，偏左，向右调
	{
		car_lf_go();
		if(Dl==0&&Dr==0)//回正小车后
	  {car_go();}//保持直线
	}
	if(Dl==0&&Dr==1)
	{
		car_rg_go();
		if(Dl==0&&Dr==0)//回正小车后
	  {car_go();}//保持直线
	}
	/*直角转弯
	if(Dl1==0&&Dl2==0&&Dr1==1&&Dr2==1)
	{
	car_go();
	delayms(50);
	if(Dl1==0&&Dl2==0&&Dr1==0&&Dr2==0)//全白
	{
	car_lf_stop();
	car_rg_stop();
	delayms(50);//保护电机
	car_rg_go();
	}
	}//直角左拐
*/
/*锐角拐弯
*/
}