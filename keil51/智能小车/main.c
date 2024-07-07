#include <REGX52.H>
#include "basic.h"
#include"delay.h"
#include"LCD1602.h"

sbit EN1A = P1^5;
sbit EN1B = P0^4;//L298Nʹ������

unsigned char count;//������
unsigned char speech=20;//�ٶ�
void prepare ()
{
	ET0 = 1;//��ʱ��0�ж�������
	EA = 1;//��ʱ���ܿ���
	PT0 =0;//��ʱ��0�ж����ȼ�
}
void init()//100΢��@11��0592MHZ
{
	TMOD &= 0xF0;//���ö�ʱ��ģʽ
	TMOD |= 0x01;//���ö�ʱ��ģʽ
	TL0 = 0xA4;//���ö�ʱ����ʼֵ
	TH0 = 0xFF;//���ö�ʱ����ʼֵ
	TF0 = 0;//����TF0��־
	TR0 = 1;//��ʱ��0��ʼ��ʱ
	prepare();
}//��ʱ���жϳ�����
void go ()
{
	car_lf_go();
	car_rg_go();
}
void main ()
{
	myinit();
	init();
	mystring(1,1,"myspeech");
	while(1)
	{
	if(P3_1==0)
	{
			delayms(20);
			while(P3_1==0);
			delayms(20);
			speech++;
	}
	if(P3_2==0)
	{
			delayms(20);
			while(P3_1==0);
			delayms(20);
			speech--;
	}
	go();
	}
	mychar(2,2,speech);
	//һ�߸�һ�ߵͣ��ߵ͵�ƽ���γɵ������Ϳ���ת��
	//��ת��ת��ǰ��ֵ������
	//�жϳ���λ�ÿ�һ��������01���ж�
}

void mywant () interrupt 1 //�жϺ�����1Ϊ��ʱ��0�ж�ģʽ
{
	TL0 = 0xA4;
	TH0 = 0xFF;//��ʱ���ع��ʼֵ
	count++;
	if(count >=100)
	{
		count=0;
	}//ʱ���������100Ϊ����
	if(count<speech)
	{
		EN1A = 1;
		EN1B = 1;//ʹ�����ţ�1���ܣ�0����
	}
	else
	{
		EN1A = 0;
		EN1B = 0;
	}
}
