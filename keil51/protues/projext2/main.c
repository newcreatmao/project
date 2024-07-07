#include<reg52.h>

sbit key=P3^2;

unsigned char tab[]={0x03,~0x60,0x25,0x0D,0x99,0x49,0xC1,0x1F,0x01,0x09};//最低0是点，给1不亮

int key_scan(){
	if(key==0){
		return 1;
	}
	return 0;
}

void main()
{
	int count=0;
	while(1)
	{
		if(key_scan()==1)
		{
		count=count+1;
		count%=9;
		}
		P1=tab[count];
	}
}




