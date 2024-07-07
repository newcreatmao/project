#include "config.h"
#include "timer_ISR.h"
#include "motor.h"
#include "app.h"

uchar PWM_T;//PWW����
/*=================================================
*�������ƣ�IntRegInit
*�������ܣ��жϼĴ�����ʼ��
*���ã�
*���룺
=================================================*/
void IntRegInit()
{
	ET0 = 1;//����ʱ��0�ж�
	ET1 = 1;             //����T1�ж�
	EA	= 1;//���ж�����	
}
/*��ʱ��0��ʼ��*/
void Timer0Init(void)		//100΢��@11.0592MHz
{
	TMOD |= 0x02;//��ʱ��0��8λ�Զ���װģ��
	TH0 = 0xA4;
	TL0 = 0xA4;//100US�ж�һ��
	TR0 = 1;//������ʱ��0
}

/*��ʱ��1��ʼ��*/
void Timer1Init(void)		
{
	TMOD |= 0x10;	//��ʱ��1����ģʽ1,16λ��ʱģʽ��T1�ò�ECH0���峤��
	TH1 = 0;		   
    TL1 = 0;
}
/* Timer0 interrupt routine */
void tm0_isr() interrupt 1 using 1
{
	PWM_T++;
	if(PWM_T == 255)		//Ƶ��F=1000000/T0���ʱ��*255
	{
		PWM_T = 0;
	}
	if(RightMotorSpeed >= PWM_T)
	{
		RightMotor_EN = 1;	//ʹ�������
	}
	if(LeftMotorSpeed >= PWM_T)
	{
	 	LeftMotor_EN  = 1;  //ʹ�������
	}		
	if(LeftMotorSpeed < PWM_T)
	{
	 	LeftMotor_EN  = 0;  //���������
	}		
	if(RightMotorSpeed < PWM_T)
	{
		RightMotor_EN = 0;	//���������
	}	
}
/* Timer0 interrupt routine */
void tm1_isr() interrupt 3 using 1
{
	Timer1Overflow = 1;	//������1�����־λ
	EchoPin = 0;		//���������ն�	
}
