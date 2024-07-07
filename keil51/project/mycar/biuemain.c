//#include <REGX52.H>
//#include"HEAD.h"
//#include"user.h"
//unsigned char pwmfl=180,pwmfg=180,pwmbl=180,pwmbg=180,basic1=180;
//unsigned char pwm_t=0;
//unsigned char redata;//接收的的数据变量
//void receive(unsigned char num)
//{
//	switch(num)
//	{
//		case '1':
//			forward();
//			break;
//		case '2':
//			backward();
//			break;
//		case '3':
//			tlf();
//			break;
//		case '4':
//			tgb();
//			break;
//		case '5':
//			tlb();
//			break;
//		case '6':
//			tgf();
//			break;
//		case '7':
//			basic1+=5;
//			reward();
//			break;
//		case '8':
//			basic1-=5;
//			reward();
//			break;
//		case '9':
//			look_road();
//			break;
//	}
//}
//void Uart_Init()//9600bps@11.0592
//{
//	PCON=0x00;//关倍频
//	SCON=0x50;//8位数据，可变波特率
//	TMOD &= 0x0F;	//设置定时器模式
//	TMOD |= 0x20;
//	TL1=0xFD;//设置定时初始值
//	TH1=0xFD;
//	//禁止定时器1中断
//  ET1=0;
//	//定时器1开始计时
//	TR1=1;
//	EA=1;//总中断
//	ES=1;//打开串口中断
//}

//void main()
//{
//	timer();
//	Uart_Init();
//	while(1);
//}
//	
//void Uart_Routine() interrupt 4
//{
//	stop();
//	RI=0;//清除中断标志位
//	redata=SBUF;//
//	receive(redata);
//}	
//void pwm() interrupt 1
//{
//		TL0 = 0xA4;		//设置定时初始值
//	  TH0 = 0xFF;	
//	  pwm_t++;
//		if(pwm_t==255)  {pwm_t=efl=efg=ebl=ebg=0;}
//		if(pwm_t==pwmfl){efl=1;}
//		if(pwm_t==pwmfg){efg=1;}
//		if(pwm_t==pwmbl){ebl=1;}
//		if(pwm_t==pwmbg){ebg=1;}
//}