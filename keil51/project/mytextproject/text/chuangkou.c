#include <REGX52.H>
void UartInit(void)		//4800bps@11.0592MHz��51��Ƭ���ǵ͹��ʵģ�Ҫ��8λ��ʱ������
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50;		//8λ����,�ɱ䲨����,�������
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xFA;		//���ö�ʱ��ʼֵ
	TH1 = 0xFA;		//���ö�ʱ����ֵ
	ET1 = 0;		//��ֹ��ʱ��%d�ж�
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
	EA=1;//ʹ���ж�
	ES=1;//ʹ���ж�
}
void sendbyte(unsigned char byte)
{
	SBUF=byte;
	while(TI==0);
	TI=0;
}