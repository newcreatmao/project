#include <STC8.H>

sbit SW1= P3^3;

void Delayms(unsigned int ms)		//@11.0592MHz
{
	unsigned char data i, j;
	while(ms--){
		i = 15;
		j = 90;
		do
		{
			while (--j);
		} while (--i);
	}	
}


void main()
{
	P1M1 = 0x00;
	P1M0 = 0xFF;//推挽
	P3M1 = 0xF7;
	P3M0 = 0xF7;//弱上拉
  P1 = 0xFF;
	while(1)
	{
		char count=0;
		if(SW1==0)
		{
			Delayms(20);
			while(SW1==0);
			Delayms(20);//按键消抖
			
			for(;count<8;count++)
			{
				P1=~(0x01<<count);//流水灯
				Delayms(500);
			}
		}
	}
}
