#include <REGX52.H>
#include "basic.h"
#include <intrins.h>
#include "delay.h"

sbit Dl = P2^7;
sbit Dr = P2^6;//1Ϊ�ڣ����ⷴ���������0Ϊ��

void car_go()
{
	car_lf_go();
	car_rg_go();
}

void xunji()
{	
	if(Dl==1&&Dr==1)
	{car_go();}
	if(Dl==1&&Dr==0)//�м�����⵽���ߣ�ƫ�����ҵ�
	{
		car_lf_go();
		if(Dl==0&&Dr==0)//����С����
	  {car_go();}//����ֱ��
	}
	if(Dl==0&&Dr==1)
	{
		car_rg_go();
		if(Dl==0&&Dr==0)//����С����
	  {car_go();}//����ֱ��
	}
	/*ֱ��ת��
	if(Dl1==0&&Dl2==0&&Dr1==1&&Dr2==1)
	{
	car_go();
	delayms(50);
	if(Dl1==0&&Dl2==0&&Dr1==0&&Dr2==0)//ȫ��
	{
	car_lf_stop();
	car_rg_stop();
	delayms(50);//�������
	car_rg_go();
	}
	}//ֱ�����
*/
/*��ǹ���
*/
}