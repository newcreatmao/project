#include <REGX52.H>
#include"lll.h"
#include"delay.h"
unsigned char sec=0;
unsigned char count=0;
unsigned char	Keyreturn ()
{
	unsigned char KeyNumber=0;
	
	if(P2_1==0){delayms(20);while(P2_1==0);delayms(20);KeyNumber=1;}
	if(P2_0==0){delayms(20);while(P2_0==0);delayms(20);KeyNumber=2;}	
	if(P2_2==0){delayms(20);while(P2_2==0);delayms(20);KeyNumber=3;}		
	if(P2_3==0){delayms(20);while(P2_3==0);delayms(20);KeyNumber=4;}
	return KeyNumber;
}
	
int main ()
{
	uart();
	sendbyte(Keyreturn());
	delayms(3000);
}

