#include <REGX52.H>//��λ����
#include <INTRINS.H>//_nop_��������ͷ�ļ�
//ȫ�ֱ�����unsigned char Ĭ����0
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
void first()//����һ��LED
{
	P2=0xFE;  //1111 1110,��P2�Ĵ���д������
	while(1)
	{
		
	};//��P2��ָ���
}
void tow()
{
	while(1)
	{
		P2=0xFE;
		delay(500);
		P2=0xFF;//ִ�е��ٶȿ죬���¿���������
		//�����ʱ����,����stc�������ʱ��������ֱ������
		delay(500);
	}//��һ��LED��һ��������
}
void third()
{
	while(1)
	{
		
	}//��ˮ��,������λfor��
}
void forth()
{
	while(1)
	{
			if(P3_1==0)//һ��Ҫ==
					P2_0=0;//����һ���͵�Ƶ
			else
				P2_0=1;//����һ���ߵ�Ƶ
	}//������������LED,���µ���������Ϩ��
}
void fifth()
{
	while(1)
	{
			if(P3_1==0)//һ��Ҫ==
			{
				P2_0=0;
				delay(20);
				while(P3_1==0);//��������
				delay(20);//��������
				//����һ���͵�Ƶ
				P2_0=~P2_0;
			}//����һ���ߵ�Ƶ
	}//������������LED,���µ���������Ϩ��,��������
}
void six()
{
	unsigned char LEDNUM=0;//���ַ��ͣ������ƣ�����Ч��ӦP2�ļĴ�����Ŀ
	while(1)
	{
		if(P3_1==0)
		{
			delay(20);
			while(P3_1==0);
			delay(20);
			
			//P2�տ�ʼĬ��ȫ��1
			LEDNUM++;
			P2=~LEDNUM;//���ı�LEDNUM��ֵ
		}
	}//��������ʵ��LED������
}
void seven ()
{
	unsigned char LEDNUM1=0;//���ַ��ͣ������ƣ�����Ч��ӦP2�ļĴ�����Ŀ
	P2=~0x01;//��ʼ��
	while(1)
	{
		if(P3_1==0)
		{
			delay(20);
			while(P3_1==0);
			delay(20);
			
			LEDNUM1++;
			if(LEDNUM1>=8)
				LEDNUM1=0;
		  P2=~(0x01<<LEDNUM1);//ǰ��
		}
		if(P3_0==0)
		{
			delay(20);
			while(P3_1==0);
			delay(20);
			
			if(LEDNUM1==0)
				LEDNUM1=7;
			else LEDNUM1--;
		  P2=~(0x01<<LEDNUM1);//����
		}
	}
}//������������LED��λ
	
void main()//ִ�����������ִ��
{
	while(1)
	{
		unsigned char k=0;
		for(k=0;k<8;k++)
		{
			P1=~(0x01<<k);
			delay(500);
		}
	}
}
