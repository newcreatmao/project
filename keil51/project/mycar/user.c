#include <REGX52.H>
#include"delay.h"
#include"HEAD.h"
unsigned char Key_KeyNumber;
extern unsigned char pwmfl,pwmfg,pwmbl,pwmbg,basic1;
unsigned char distance;


void timer()		//100微秒@11.0592MHz
{
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0xA4;		//设置定时初始值
	TH0 = 0xFF;		
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	ET0=1;			//1允许定时器中断
	EA=1;			//允许总中断
	PT0=0;			//中断优先级
}

void uart()
{
	PCON |= 0x80;		//波特率倍速
	SCON = 0x40;		//8位数据,可变波特率,允许接收
	TMOD &= 0x0F;		//设置定时器模式
	TMOD |= 0x20;		//设置定时器模式
	TL1 = 0xF3;		//设置定时初始值
	TH1 = 0xF3;		//设置定时重载值
	ET1 = 0;		//禁止定时器ET中断，开启中断接收会增大误差
	TR1 = 1;		//定时器1开始计时
}

void sendbyte(unsigned char byte)
{
	SBUF=byte;//SBUF数据接收器
	while(TI==0);//TI发送标志位，0为等待发送数据，1为发送完成
	TI=0;
}





/**
  * @brief  获取按键键码
  * @param  无
  * @retval 按下按键的键码，范围：0,1~4,0表示无按键按下
  */
unsigned char Keyreturn(void)
{
	unsigned char Temp=0;
	Temp=Key_KeyNumber;
	Key_KeyNumber=0;
	return Temp;
}

/**
  * @brief  获取当前按键的状态，无消抖及松手检测
  * @param  无
  * @retval 按下按键的键码，范围：0,1~4,0表示无按键按下
  */
unsigned char Key_GetState()
{
	unsigned char KeyNumber=0;
	
	if(key1==0){KeyNumber=1;}
	if(key2==0){KeyNumber=2;}
	if(key3==0){KeyNumber=3;}
	if(key4==0){KeyNumber=4;}
	
	return KeyNumber;
}

/**
  * @brief  按键驱动函数，在中断中调用
  * @param  无
  * @retval 无
  */
void Key_Loop(void)
{
	static unsigned char NowState,LastState;
	LastState=NowState;				//按键状态更新
	NowState=Key_GetState();		//获取当前按键状态
	//如果上个时间点按键按下，这个时间点未按下，则是松手瞬间，以此避免消抖和松手检测
	if(LastState==1 && NowState==0)
	{
		Key_KeyNumber=1;
	}
	if(LastState==2 && NowState==0)
	{
		Key_KeyNumber=2;
	}
	if(LastState==3 && NowState==0)
	{
		Key_KeyNumber=3;
	}
	if(LastState==4 && NowState==0)
	{
		Key_KeyNumber=4;
	}
}


unsigned char red()
{
	TMOD |= 0x11;//设置定时器模式
	TL1 = 0;//设置定时器初始值
	TH1 = 0;//设置定时器初始值
	
	TRIG = 1;
	delayus(20);//发射一段脉冲，至少20us
	TRIG = 0;
	
	while(!ECHO);//等待超声波模块返回脉冲
	TR1=1;//打开定时器
	while(ECHO);//等待超声波定时器返回脉冲结束
	TR1 = 0;//停止计数器，计时结束
	
	distance=((TH1*256+TL1)*0.034)/2+1;//计算距离,定时器1的计数器，12t为1us一个计数，故总时间为那么多
	
	return distance;
}

void forward()
{
	blf=1;
	blb=0;
	bgf=1;
	bgb=0;
	flf=1;
	flb=0;
	fgf=1;
	fgb=0;
}

void backward()
{
	blf=0;
	blb=1;
	bgf=0;
	bgb=1;
	flf=0;
	flb=1;
	fgf=0;
	fgb=1;
}

void stop()
{
	blf=0;
	blb=0;
	bgf=0;
	bgb=0;
	flf=0;
	flb=0;
	fgf=0;
	fgb=0;
}

void reward()
{pwmfl=pwmfg=pwmbl=pwmbg=basic1;}

void tlf()//左前转
{
	forward();
	pwmfl=255;
	pwmbl=255;
	pwmbg=100;
	pwmfg=pwmbg+20;

}

void tgf()
{
	forward();
	pwmfg=255;
	pwmbg=255;
	pwmbl=100;
	pwmfl=pwmbl+20;

}

void tlb()
{
	backward();
	pwmfl=255;
	pwmbl=255;
	pwmfg=100;
	pwmbg=pwmfg+20;

}

void tgb()
{
	backward();
	pwmfg=255;
	pwmbg=255;
	pwmbl=100;
	pwmfl=pwmbl+20;

}
void look_road()
{
	if(clx){tgf();}
	if(crx){tlf();}
	if(mlx&&clx){tgf();}
	if(mrx&&crx){tlf();}
	if(clx==0&&crx==0&&mlx==0&&mrx==0){reward();}
}