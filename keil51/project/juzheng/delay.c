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
