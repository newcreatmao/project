#include <REGX52.H>
#include"HEAD.h"
#include"user.h"
#include"delay.h"

unsigned char pwmfl=180,pwmfg=180,pwmbl=180,pwmbg=180,basic1=180;
unsigned char pwm_t=0;
unsigned char compare=10,limit,keynum;

int main ()
{
	timer();		
	forward();
	while(1)
	{
	keynum=Keyreturn();
  if(keynum==1){basic1+=5;reward();}
	if(keynum==2){basic1-=5;reward();}	
	limit=red();
	if(left==0){tgf();while(left==0);reward();}
	if(right==0){tlf();while(right==0);reward();}
	if(clx){tgf();while(mlx);reward();}
	if(crx){tlf();while(mrx);reward();}
	if(mlx&&clx){tgf();while(mlx);reward();}
	if(mrx&&crx){tlf();while(mrx);reward();}
	}
}

void pwm() interrupt 1
{
	  static unsigned int T0;
		TL0 = 0xA4;		//设置定时初始值
	  TH0 = 0xFF;	
		T0++;
	  pwm_t++;
		if(limit>compare)
		{
			forward();
		}
		if(limit<compare)
		{
			stop();
		}
		if(T0>=200){T0=0;Key_Loop();}	//20ms调用一次按键驱动函数
		if(pwm_t==255)  {pwm_t=efl=efg=ebl=ebg=0;}
		if(pwm_t==pwmfl){efl=1;}
		if(pwm_t==pwmfg){efg=1;}
		if(pwm_t==pwmbl){ebl=1;}
		if(pwm_t==pwmbg){ebg=1;}
}