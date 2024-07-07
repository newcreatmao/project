
void Delay(unsigned char xms)		//@12.000MHz
{
	unsigned char i, j;
	while(xms--)
	{

		i = 12;
		j = 169;
		do
		{
			while (--j);
		} while (--i);
	}
}