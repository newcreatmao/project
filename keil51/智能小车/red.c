#include <REGX52.H>
#include "basic.h"
#include "delay.h"

sbit TRIG = P2^1;//���峬������෢�Ͷ�
sbit ECHO = P2^2;//���峬���������ն�

unsigned int sum;//�����������
unsigned int limit;//С�����ϰ�����������ƾ���

void red_control()
{
	TMOD = 0x11;//���ö�ʱ��ģʽ
	TL1 = 0;//���ö�ʱ����ʼֵ
	TH1 = 0;//���ö�ʱ����ʼֵ
	
	TRIG = 1;
	delayus(20);//����һ�����壬����20us
	TRIG = 0;
	
	while(!ECHO);//�ȴ�������ģ�鷵������
	TR1=1;//�򿪶�ʱ��
	while(ECHO);//�ȴ���������ʱ�������������
	TR1 = 0;//ֹͣ����������ʱ����
	
	sum=((TH1*256+TL1)*0.034)/2+1;//�������
	
	if(limit>sum)
	{
		car_lf_stop();
		car_rg_stop();
		delayms(1000);
	}
}
