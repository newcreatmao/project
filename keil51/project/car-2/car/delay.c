#include<intrins.h>
void delayms(unsigned int xms)//�������ʱx���뺯��
{
    while(xms)
    {
			  unsigned char i, j;

				i = 2;
				j = 239;
				do
				{
					while (--j);
				} while (--i);//�����1ms�Ĵ���;
        xms=xms-1;
    }
}

void Delay20us()		//@11.0592MHz
{
	unsigned char i;
	
	i = 6;
	while (--i);
}