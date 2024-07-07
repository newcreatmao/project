#include <reg52.h>
#include <intrins.h>

#define ON  0
#define OFF 1

sbit KEY1 = P3^3;
sbit KEY2 = P3^4;
sbit KEY3 = P3^6;
sbit KEY4 = P3^7;

sbit BUZZER = P0^7;

void delay_ms(unsigned int nms)
{
	 unsigned int i,j;

	 for(i=nms;i>0;i--)
	 	for(j=113;j>0;j--);
}

void main()
{	
	unsigned int i;
	P1 = 0xff;

	while(1)
	{
		if(KEY1 == ON){
			delay_ms(10);
			if(KEY1 == ON)
			{
				BUZZER = ON;
			}
			while(KEY1 == ON);
		}
		if(KEY2 == ON){
			delay_ms(10);
			if(KEY2 == ON)
			{
				BUZZER = OFF;
			}
			while(KEY2 == ON);
		}
		if(KEY3 == ON){
			delay_ms(10);
			if(KEY3 == ON)
			{
				P1 = 0xfe;
				for(i=8;i>0;i--)
				{
					delay_ms(150);
					P1 = _crol_(P1,1);
				}
			}
			while(KEY3 == ON);
		}
		if(KEY4 == ON){
			delay_ms(10);
			if(KEY4 == ON)
			{
				P1 = 0x7f;
				for(i=8;i>0;i--)
				{
					delay_ms(150);
					P1 = _crol_(P1,-1);
				}
			}
			while(KEY4 == ON);
		}
	}
}
