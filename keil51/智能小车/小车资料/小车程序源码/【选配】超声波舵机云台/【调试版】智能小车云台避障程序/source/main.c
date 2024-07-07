/*
* ����дʱ�䡿�� 2019��7��23��
* ����    �ߡ��� �������:01
* ����    ������ 1.6
* ����    վ���� http://www.qxmcu.com/ 
* ���Ա����̡��� http://qxmcu.taobao.com/ 
* ��ʵ��ƽ̨���� QX-MCS51 ��Ƭ�������� & QX-A51����С��
* ���ⲿ���񡿣� 11.0592mhz	
* ������оƬ���� STC89C52
* �����뻷������ Keil ��Visio4
* �������ܡ��� ���԰汾��̨���ϣ���������̨�������ϣ�1602Һ����ʾ����
* ��ʹ��˵������ 1���������1602Һ����ʾ��
				 2���뽫�������ذ��P32-P35��4P�Ű��߰ε�
				 3���ٰ�С��������P34�ӵ����ذ��P10�ϣ�P35�ӵ����ذ��P11��

				 Һ����һ����ʾ��̨��෽�򣬷ֱ�ΪD��Fǰ����L����,R����
				 �ڶ�������ʾ�ľ��룬��λ����
				 ����ͨ�������ʾ��Ϣ����������С�������߼��������ϲ�ͬʵ�黷��
				 �¶���Ҫ���Բ��ܴﵽ����Ч����
				 ִ���߼�app.c�ļ�����PTZ_Avoid();����
* ��ע������� ��̨����ײ
*/

#define  _MAIN_C
#include "config.h"
#include "motor.h"
#include "Delay.h"
#include "timer_ISR.h"
#include "LCD1602.h"
#include "ultrasonic.h"
#include "app.h"
#include "Servo.h"
#include "main.h"

uchar LeftSpeed, RightSpeed;//�����������ٶ�
void main()
{
	LeftSpeed	= 100;//���������ٶ�
	RightSpeed	= 130;//���������ٶ�
	IntRegInit();//�жϼĴ�����ʼ��
	Timer0Init();//PWM���ٳ�ʼ��
	Timer1Init();//��ʼ����ʱ��
	Init_LCD1602(); //LCD1602��ʼ��
	ServoFront(); //��ʼ���������	
	while(1)
	{
		PTZ_Avoid();//�����̨����
	}
} 