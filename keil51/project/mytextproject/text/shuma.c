#include <REGX52.H>
#include"shuma.h"
#include"delay.h"
void towtoten(unsigned char location,unsigned char *x)
{
	int i=0;
	for(i=0;i<4;i++)
	{
		*(x+i)=location%2;
		location/=2;
	}
}
void children(unsigned char loc,num)
{
	static char table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
	switch(loc)		
	{
		case 1:P2_4=0;P2_3=0;P2_2=0;break;
		case 2:P2_4=0;P2_3=0;P2_2=1;break;
		case 3:P2_4=0;P2_3=1;P2_2=0;break;
		case 4:P2_4=0;P2_3=1;P2_2=1;break;
		case 5:P2_4=1;P2_3=0;P2_2=0;break;
		case 6:P2_4=1;P2_3=0;P2_2=1;break;
		case 7:P2_4=1;P2_3=1;P2_2=0;break;
		case 8:P2_4=1;P2_3=1;P2_2=1;break;
	}
	if(loc == 3 || loc == 5)
		P0=table[num]|0x80;	
	else
		P0 = table[num];
	delayms(1);				
	P0=0x00;

	//显示加点时间
}
void light_four(unsigned char a[])
{
		children(4,a[3]);
		children(5,a[2]);
	  children(6,a[1]);
		children(7,a[0]);
}//点亮数码管

void ymd()
{
	children(8,2);
	children(7,0);
	children(6,DS1302_Time[0]/10);
	children(5,DS1302_Time[0]%10);
	children(4,DS1302_Time[1]/10);
	children(3,DS1302_Time[1]%10);
	children(2,DS1302_Time[2]/10);
	children(1,DS1302_Time[2]%10);
}
void hms()
{
	children(6,DS1302_Time[3]/10);
  children(5,DS1302_Time[3]%10);
	children(4,DS1302_Time[4]/10);
	children(3,DS1302_Time[4]%10);
	children(2,DS1302_Time[5]/10);
	children(1,DS1302_Time[5]%10);

}
void ad(unsigned int Data)
{
	children(3,Data/100);
	children(2,Data/10%10);
	children(1,Data%10);
}