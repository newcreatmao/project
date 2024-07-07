#include "REG52.h"
#include "BASIC.h"
#include "HEAD.h"
#include "delay.h"
int sum;//�����������
unsigned int limit=15;//С�����ϰ�����������ƾ���
unsigned char lochoice[9]={0x00,0xFE,0xFD,0xFB,0xF7,0xEF,0xDF,0xBF,0x7F};//������
unsigned char displaynum[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};//0-9

int opration(int num)
{
		
	int n=0;
	if(num==0)
	{return 1;}
	while(num)
	{
		num=num/10;
		n++;
	}

	return n;
}

void display(int Data,int location)
{
	int n=0;
	int pp=0;
	for(n=location+opration(Data)-1;n>=location;n--)
{
	P0=0xFF;
	WS=1;//��λ��
	P0=lochoice[n];
	WS=0;//�ر�λ��
	
	pp=0;
	pp=Data%10;
	Data/=10;
	MS=1;//�򿪶ο�
	P0=displaynum[pp];
	MS=0;//�رնο�
	delayms(2);
}
}
void xunji()
{
	if(left_led==1 && right_led==1)
		forward();
	if(left_led==0 && right_led==1)
		right();
	if(left_led==1 && right_led==0)
		left();
	if(left_led==0 && right_led==0)
		back_right();
}

void red()
{
	TMOD = 0x11;//���ö�ʱ��ģʽ
	TL1 = 0;//���ö�ʱ����ʼֵ
	TH1 = 0;//���ö�ʱ����ʼֵ
	
	TRIG = 1;
	Delay20us();//����һ�����壬����20us
	TRIG = 0;
	
	while(!ECHO);//�ȴ�������ģ�鷵������
	TR1=1;//�򿪶�ʱ��
	while(ECHO);//�ȴ���������ʱ�������������
	TR1 = 0;//ֹͣ����������ʱ����
	
	sum=((TH1*256+TL1)*0.034)/2+1;//�������
	if(limit<sum)
	{forward();}
	if(limit>sum)
	{
		backward();
}
		display(sum,5);
}

void key2_long()	//�����ɿ�����
{	
	for(;;)
	{
		if(key2==0)
		{
			delayms(5);
			if(key2==0)
			{	
				delayms(10);
				beep=0;
				delayms(200);
				beep=1;
				break;
			}
		}
	}
}
