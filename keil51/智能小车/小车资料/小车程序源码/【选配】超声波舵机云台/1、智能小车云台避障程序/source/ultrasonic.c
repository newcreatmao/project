#include "config.h"
#include "timer_ISR.h"
#include "ultrasonic.h"
#include "Delay.h"

/*����������*/
void TrigUltrasonic()
{
	TrigPin = 0; //������ģ��Trig	���ƶ�
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	TrigPin = 1; //������ģ��Trig	���ƶ�
	Delay15us();
	TrigPin = 0; //������ģ��Trig	���ƶ�
}
/*====================================
������	��GetDistance
����	����
����ֵ	����ȡ���뵥λ����
����	�����������
ͨ�������źŵ��յ������źŵ�ʱ����Ծ���
��Ƭ������11.0592Mhz
ע��������Ϊ60ms����
====================================*/
unsigned int GetDistance()
{
	unsigned int Distance = 0;	//����������
	unsigned int  Time=0;		//���ڴ�Ŷ�ʱ��ʱ��ֵ
	TrigUltrasonic();	//����������
	while(!EchoPin);  	//�жϻ����ź��Ƿ�Ϊ�͵�ƽ
	Timer1On;			//������ʱ��1
	while(EchoPin);		//�ȴ��յ������ź�
	Timer1Off;			//�رն�ʱ��1
	Time=TH1*256+TL1;	//��ȡʱ��
	TH1=0;
	TL1=0;				//��ն�ʱ��
    Distance = (float)(Time*1.085)*0.17;//�������MM
	return(Distance);//���ؾ���				
}
