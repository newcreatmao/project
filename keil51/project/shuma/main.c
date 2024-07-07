#include <REGX52.H>
unsigned char kk[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0xFF,0x6F};//定义所有的数字形状
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
void towtoten(unsigned char location,unsigned char *x)
{
	int i=0;
	for(i=0;i<3;i++)
	{
		*(x+i)=location%2;
		location/=2;
	}
}
void children(unsigned char location,number)//定义子函数
{
	unsigned char m[3];
	/*switch(location)
	{
		case 1:	P2_4=1;P2_3=1;P2_2=1;break;
		case 2:	P2_4=1;P2_3=1;P2_2=0;break;
		case 3:	P2_4=1;P2_3=0;P2_2=1;break;
		case 4:	P2_4=1;P2_3=0;P2_2=0;break;
		case 5:	P2_4=0;P2_3=1;P2_2=1;break;
		case 6:	P2_4=0;P2_3=1;P2_2=0;break;
		case 7:	P2_4=0;P2_3=0;P2_2=1;break;
		case 8:	P2_4=0;P2_3=0;P2_2=0;break;
	}*/
	towtoten(location,m);
	P2_4=m[2];P2_3=m[1];P2_2=m[0];
	P0=kk[number];
	delay(1);
	P0=0x00;//清零
}//点亮一个
void light()
{
	//P2_4=1;
	//P2_3=0;
	//P2_2=1;//二进制转十进制选中LED6
	//P0=0x7D;//将数据输入LED6，使其显示6
	while(1)
	{
		children(1,7);//7
		children(2,6);//6
		children(3,5);//5
		children(4,4);//4
		children(5,3);//3
		children(6,2);//2
		children(7,1);//1
		children(8,0);//8
	}
}//点亮数码管
void main()
{
	light();
}