#include <REGX52.H>
#include <INTRINS.H>
#include"delay.h"
unsigned char mod=0;
void uart()
{
	PCON |= 0x80;		//�����ʱ���
	SCON = 0x40;		//8λ����,�ɱ䲨����,�������
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xF3;		//���ö�ʱ��ʼֵ
	TH1 = 0xF3;		//���ö�ʱ����ֵ
	ET1 = 0;		//��ֹ��ʱ��ET1�жϣ������жϽ��ջ��������
	TR1 = 1;		//��ʱ��1��ʼ��ʱ

}
void timer()
{
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	TL0 = 0x18;
	TH0 = 0xFC;
	TF0 = 0;
	TR0 = 1;
	
	ET0 = 1;
	EA = 1;
  PT0  = 0;	
}


void sendbyte(unsigned char byte)
{
	SBUF=byte;//SBUF���ݽ�����
	while(TI==0);//TI���ͱ�־λ��0Ϊ�ȴ��������ݣ�1Ϊ�������
	TI=0;
}

int main ()
{	
	P2=0xFE;
	timer();
uart();
	while(1)
	{
		if(P3_1==0)
		{
			delayms(20);
			while(P3_1==0);
			delayms(20);
			mod++;
			mod%=2;
		}
	}
}

void Timer0_Routine() interrupt 1
{	
	static unsigned int Tcount;
	TL0 = 0x18;
	TH0 = 0xFC;
	
	Tcount++;

	if(Tcount>=500)//500ms
	{	sendbyte(mod);
		Tcount=0;
	if(mod==0)
	{
		P2=_crol_(P2,1);
	}
	if(mod==1)
	{
	P2=_cror_(P2,1);
	}}
}

