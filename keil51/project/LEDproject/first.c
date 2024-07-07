#include <REGX52.H>//有位声明
#include <INTRINS.H>//_nop_函数所在头文件
//全局变量的unsigned char 默认是0
void delay(unsigned int xms)//定义的延时x毫秒函数
{
    while(xms)
    {
			  unsigned char i, j;

				i = 2;
				j = 239;
				do
				{
					while (--j);
				} while (--i);//定义的1ms的代码;
        xms=xms-1;
    }
}
void first()//点亮一个LED
{
	P2=0xFE;  //1111 1110,给P2寄存器写入命令
	while(1)
	{
		
	};//令P2的指令不变
}
void tow()
{
	while(1)
	{
		P2=0xFE;
		delay(500);
		P2=0xFF;//执行的速度快，导致看不出亮灭
		//添加延时代码,可在stc软件的延时计数器里直接生成
		delay(500);
	}//让一个LED以一秒周期闪
}
void third()
{
	while(1)
	{
		
	}//流水灯,可用移位for来
}
void forth()
{
	while(1)
	{
			if(P3_1==0)//一定要==
					P2_0=0;//给予一个低电频
			else
				P2_0=1;//给予一个高电频
	}//独立按键控制LED,按下点亮，松手熄灭
}
void fifth()
{
	while(1)
	{
			if(P3_1==0)//一定要==
			{
				P2_0=0;
				delay(20);
				while(P3_1==0);//按下消抖
				delay(20);//松手消抖
				//给予一个低电频
				P2_0=~P2_0;
			}//给予一个高电频
	}//独立按键控制LED,按下点亮，松手熄灭,按键消抖
}
void six()
{
	unsigned char LEDNUM=0;//用字符型（二进制）可有效对应P2的寄存器数目
	while(1)
	{
		if(P3_1==0)
		{
			delay(20);
			while(P3_1==0);
			delay(20);
			
			//P2刚开始默认全是1
			LEDNUM++;
			P2=~LEDNUM;//不改变LEDNUM的值
		}
	}//独立按键实现LED二进制
}
void seven ()
{
	unsigned char LEDNUM1=0;//用字符型（二进制）可有效对应P2的寄存器数目
	P2=~0x01;//初始化
	while(1)
	{
		if(P3_1==0)
		{
			delay(20);
			while(P3_1==0);
			delay(20);
			
			LEDNUM1++;
			if(LEDNUM1>=8)
				LEDNUM1=0;
		  P2=~(0x01<<LEDNUM1);//前进
		}
		if(P3_0==0)
		{
			delay(20);
			while(P3_1==0);
			delay(20);
			
			if(LEDNUM1==0)
				LEDNUM1=7;
			else LEDNUM1--;
		  P2=~(0x01<<LEDNUM1);//倒退
		}
	}
}//独立按键控制LED移位
	
void main()//执行完后又重新执行
{
	while(1)
	{
		unsigned char k=0;
		for(k=0;k<8;k++)
		{
			P1=~(0x01<<k);
			delay(500);
		}
	}
}
