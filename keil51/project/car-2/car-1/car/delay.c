#include<intrins.h>
void delayms(unsigned int xms)//定义的延时x毫秒函数
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

void Delay20us()		//@11.0592MHz
{
	unsigned char i;
	
	i = 6;
	while (--i);
}