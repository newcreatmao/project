#include <REG52.H>
#include "BASIC.H"
#include "HEAD.H"
#include "delay.h"
#include "user.h"//定义管脚


unsigned char pwm_left_val=200,pwm_right_val=200,pwm_t=0;//左占空比，右占空比，周期数
unsigned char count=0;

void timei() interrupt 1
{
	TL0 = 0xA4;		//设置定时初始值
	TH0 = 0xFF;		//设置定时重载值
	pwm_t++;
	if(pwm_t==255)
		pwm_t=EN1=EN2=0;
	if(pwm_t==pwm_left_val)
		EN1=1;
	if(pwm_t==pwm_right_val)
		EN2=1;
}

void change()
{
		if(key4 == 0)	 //S2按下LED变暗
		{
			delayms(5);
			if(key4 == 0)
			{
				Delay20us();
			  while(key4==0);
			  Delay20us();
				if(pwm_left_val < 255)
				{
					pwm_left_val+=5;
					pwm_right_val=pwm_left_val;
				}
			}
		}
		if(key5 == 0)	//S3按键LED变亮
		{
			delayms(5);
			if(key5 == 0)
			{
				Delay20us();
			  while(key5==0);
			  Delay20us();
				if(pwm_left_val > 0)
				{
					pwm_right_val-=5;
					pwm_left_val=pwm_right_val;
				}
			}
		}		
 }
void main()
{
	key_begin();//按下s2松开，启动
	timer0();
	while(1)
	{	
		display(pwm_right_val,1);
		if(count==0)
		{xunji();}
		if(count==1)
		{judge();}
		if(count==2)
		{change();}
		if(count==3)
		{magic_hand();}
		if(key2==0)
		{
			stop();
			delayms(1000);
			break;
		}
		if(key3==0)
		{
			Delay20us();
			while(key3==0);
			Delay20us();
			count=(count+1)%4;
		  stop();
 		  delayms(1000);
			continue;
		}	
		display(count,8);
	}
}