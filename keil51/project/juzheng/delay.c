void delay(unsigned int xms)//�������ʱx���뺯��
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
