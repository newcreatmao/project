#include "config.h"
#include "timer_ISR.h"
#include "LCD1602.h"
#include "ultrasonic.h"
#include "Delay.h"
#include "motor.h"
#include "Servo.h"
#include "app.h"
#include "main.h"

bit Timer1Overflow;	//������1�����־λ
uchar code ASCII[13] = "0123456789";
uchar disbuff[4]={0,0,0,0};//���ڷֱ��ž����ֵ�ף����ף�����
uint LeftDistance = 0, RightDistance = 0, FrontDistance = 0; //��̨�����뻺��
uint DistBuf[5] = {0};//distance data buffer

/*====================================
������	��DispDistance(unsigned long Val)
����	������
����ֵ	����
����	��LCD1602��ʾ����
��ʾ���뵥λ������
====================================*/
void DispDistance(unsigned int Val)
{
	if((Val >= 5000) || (Timer1Overflow == 1))//����������Χ
	{
		Timer1Overflow = 0; //�����ʱ�������־λ
		LCD1602_Dis_Str(0, 1, "!!! Out of range"); //LCD1602��ʾ�ַ���	
	}
	else
	{
		/*��ʾ���뵥λ����*/
		disbuff[0]=Val/1000; //������ֵǧλ
		disbuff[1]=Val%1000/100;//������ֵ��λ
		disbuff[2]=Val%100/10;//������ֵʮλ
		disbuff[3]=Val%10; //������ֵ��λ
		LCD1602_Dis_Str(0, 1, "Distance:0000 MM"); //��ʾ��Distance:000.0cm
	    LCD1602_Dis_OneChar(9, 1,  ASCII[disbuff[0]]); //��ʾǧλ
	    LCD1602_Dis_OneChar(10, 1, ASCII[disbuff[1]]);	
	    LCD1602_Dis_OneChar(11, 1, ASCII[disbuff[2]]);	
	    LCD1602_Dis_OneChar(12, 1, ASCII[disbuff[3]]); 				
	}		
}
//ð������
void bubble(unsigned int *a,unsigned char n) /*�������������������׵�ַ�������С*/
{
	unsigned int i,j,temp;	
	for(i = 0;i < n-1; i++)	
	{	
		for(j = i + 1; j < n; j++) /*ע��ѭ����������*/
		{
			if(a[i] > a[j])
			{
				temp = a[i];		
				a[i] = a[j];		
				a[j] = temp;			
			}
		}
	}

}
/*====================================
������	��RefreshDistance
����	����
����ֵ	������ð�������ľ���
����	������5�β�࣬ȥ�����ֵ����Сֵ��ȡ�м�3��ƽ��ֵ
���뵥λ������
====================================*/
unsigned int RefreshDistance()
{
	uchar num;
	uint Dist;
	for(num=0; num<5; num++)
	{
		DistBuf[num] = GetDistance();
		Delay1ms(60);//������ڲ�����60����	
	}
	bubble(DistBuf, 5);//
	Dist = (DistBuf[1]+DistBuf[2]+DistBuf[3])/3; //ȥ��������Сȡ�м�ƽ��ֵ
	return(Dist);
}
/*�������*/
void IR_Avoid()
{
	if(UAvoidSensorLeft == 0)
	{
		SmartCarRight(LeftSpeed, RightSpeed);//��ת	
	}else if(UAvoidSensorRight == 0)
	{
		SmartCarLeft(LeftSpeed, RightSpeed);//��ת		
	}else
	{
		SmartCarForward(LeftSpeed, RightSpeed);//ǰ��	
	}
}
/*====================================
������	��PTZ_Avoid
����	����
����ֵ	��С����ͷǰ������
����	������С�������̨����
���뵥λ������
====================================*/
void PTZ_Avoid()
{
	uint Dis;//�����ݴ����
	Dis = GetDistance();//��ȡ������������,��λ������
	if(Dis < 300)
	{
		LCD1602_Dis_OneChar(0, 0, 'D');
		DispDistance(Dis);//LCD1602��ʾ������������	
		SmartCarStops();	//ͣ��
		Delay1ms(100);

		/*�����ת���*/
		ServoLeft();
		LeftDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'L');
		DispDistance(LeftDistance);//LCD1602��ʾ������������
		Delay1ms(100);

		/*�����ת���*/
		ServoRight();
		RightDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'R');
		DispDistance(RightDistance);//LCD1602��ʾ������������
		Delay1ms(100);

		/*�����ǰ�����*/
		ServoFront();
		FrontDistance = RefreshDistance();
		LCD1602_Dis_OneChar(0, 0, 'F');
		DispDistance(FrontDistance);//LCD1602��ʾ������������
		Delay1ms(100);
		if((FrontDistance<100) && (LeftDistance<100) && (RightDistance<100))
		{
			do{
				SmartCarLeftTurn(255, 255);//ԭ����ת
				Delay1ms(50);
				/*�����ǰ�����*/
				ServoFront();
				Dis = RefreshDistance();
				LCD1602_Dis_OneChar(0, 0, 'D');
				DispDistance(Dis);//LCD1602��ʾ������������
				Delay1ms(100);		
			}while(Dis < 200);
		}else if(LeftDistance > RightDistance)
		{
			LCD1602_Dis_OneChar(0, 0, 'L');
			DispDistance(LeftDistance);//LCD1602��ʾ������������
			Delay1ms(100);
			SmartCarLeftTurn(255, 255);//ԭ����ת
			Delay1ms(80);		
		}else if(RightDistance > LeftDistance)
		{
			LCD1602_Dis_OneChar(0, 0, 'R');
			DispDistance(RightDistance);//LCD1602��ʾ������������
			Delay1ms(100);
			SmartCarRightTurn(255, 255);//ԭ����ת
			Delay1ms(80);	
		}else if((FrontDistance>LeftDistance) && (FrontDistance>RightDistance))
		{
			LCD1602_Dis_OneChar(0, 0, 'F');
			DispDistance(FrontDistance);//LCD1602��ʾ������������
			Delay1ms(100);
			SmartCarForward(LeftSpeed, RightSpeed);//ǰ��
		}		
	}
	else
	{
		for(Dis=0; Dis<1800; Dis++)//������ڲ�����60ms �������Dis������ѭ��
		{
			IR_Avoid();//�������
		}
	}			
}

