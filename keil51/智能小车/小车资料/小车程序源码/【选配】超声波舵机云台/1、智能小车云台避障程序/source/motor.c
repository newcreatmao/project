#include "config.h"
#include "motor.h"

uchar LeftMotorSpeed;
uchar RightMotorSpeed;
/*=================================================
*�������ƣ�SmartCarForward
*�������ܣ�����С��ǰ��
*���ã�
*���룺LeftSpeedVal�������ٶȣ����뷶Χ100-255
	   RightSpeedVal���ҵ���ٶȣ����뷶Χ100-255
	   255�ٶ���죬100����
=================================================*/
void SmartCarForward(uchar LeftSpeedVal,uchar RightSpeedVal)
{
	LeftMotorSpeed = LeftSpeedVal;	//����������ٶ�
	RightMotorSpeed= RightSpeedVal;	//�����Ҳ����ٵ�	
	LeftMotorGo;					//������ת
	RightMotorGo;					//�ҵ����ת
}
/*=================================================
*�������ƣ�SmartCarBack
*�������ܣ�����С������
*���ã�
*���룺LeftSpeedVal�������ٶȣ����뷶Χ100-255
	   RightSpeedVal���ҵ���ٶȣ����뷶Χ100-255
	   255�ٶ���죬100����
=================================================*/
//void SmartCarBack(uchar LeftSpeedVal,uchar RightSpeedVal)
//{
//	LeftMotorSpeed = LeftSpeedVal;	//����������ٶ�
//	RightMotorSpeed= RightSpeedVal;	//�����Ҳ����ٵ�	
//	LeftMotorBack;					//������ת
//	RightMotorBack;					//�ҵ����ת
//}
/*=================================================
*�������ƣ�SmartCarLeft
*�������ܣ�����С����ת
*���ã�
*���룺LeftSpeedVal�������ٶȣ����뷶Χ100-255
	   RightSpeedVal���ҵ���ٶȣ����뷶Χ100-255
	   255�ٶ���죬100����
=================================================*/
void SmartCarLeft(uchar LeftSpeedVal,uchar RightSpeedVal)
{
	LeftMotorSpeed = LeftSpeedVal;	//����������ٶ�
	RightMotorSpeed= RightSpeedVal;	//�����Ҳ����ٵ�	
	LeftMotorStop;					//����ͣת
	RightMotorGo;					//�ҵ����ת
}
/*С�����ͷ�������������ȷ�Χ�ڵ�ͷ*/
void SmartCarLeftTurn(uchar LeftSpeedVal,uchar RightSpeedVal)
{
	LeftMotorSpeed = LeftSpeedVal;	//����������ٶ�
	RightMotorSpeed= RightSpeedVal;	//�����Ҳ����ٵ�	
	LeftMotorBack;					//������ת
	RightMotorGo;					//�ҵ����ת
}
/*=================================================
*�������ƣ�SmartCarRight
*�������ܣ�����С����ת
*���ã�
*���룺LeftSpeedVal�������ٶȣ����뷶Χ100-255
	   RightSpeedVal���ҵ���ٶȣ����뷶Χ100-255
	   255�ٶ���죬100����
=================================================*/
void SmartCarRight(uchar LeftSpeedVal,uchar RightSpeedVal)
{
	LeftMotorSpeed = LeftSpeedVal;	//����������ٶ�
	RightMotorSpeed= RightSpeedVal;	//�����Ҳ����ٵ�	
	LeftMotorGo;					//������ת
	RightMotorStop;					//�ҵ��ͣת
}
/*С���ҵ�ͷ�������������ȷ�Χ�ڵ�ͷ*/
void SmartCarRightTurn(uchar LeftSpeedVal,uchar RightSpeedVal)
{
	LeftMotorSpeed = LeftSpeedVal;	//����������ٶ�
	RightMotorSpeed= RightSpeedVal;	//�����Ҳ����ٵ�	
	LeftMotorGo;					//������ת
	RightMotorBack;					//�ҵ����ת
}
/*=================================================
*�������ƣ�SmartCarStops
*�������ܣ�����С��ͣ��
*���ã�
*���룺
=================================================*/
void SmartCarStops(void)
{	
	LeftMotorStop;					//����ͣת
	RightMotorStop;					//�ҵ��ͣת
}
