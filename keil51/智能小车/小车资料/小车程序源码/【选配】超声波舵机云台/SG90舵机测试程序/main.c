/*
* ����дʱ�䡿�� 2019��6��9��
* ����    �ߡ��� �������
* ����    ������ 1.0
* ����    վ���� http://www.qxmbot.com/ 
* ���Ա����̡��� http://qxmcu.taobao.com/ (ֱ����)
* ��ʵ��ƽ̨���� QX-MCS51 ��Ƭ�������� & QX-A51����С��
* ���ⲿ���񡿣� 11.0592mhz	
* ������оƬ���� STC89C52
* �����뻷������ Keil ��Visio4
* �������ܡ��� ���ʵ�� ���������ת
* ��ʹ��˵������
*/
#include <reg52.h> //51ͷ�ļ�
#include <intrins.h>   //����nop��ϵͳ����
sbit Servo = P2^7;//����ӿ�
/*��������*/
sbit key_s2 = P3^0;
sbit key_s3 = P3^1;
sbit beep = P2^3;//������
void delay(unsigned int z)//���뼶��ʱ
{
	unsigned int x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}
/*���������ʱ����С����ǰ��*/
void Delay1550us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 3;
	j = 196;
	do
	{
		while (--j);
	} while (--i);
}

void Delay18450us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 34;
	j = 16;
	do
	{
		while (--j);
	} while (--i);
}
/*���������ʱ��С���ҷ�*/
void Delay600us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 15;
	do
	{
		while (--j);
	} while (--i);
}
void Delay19400us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 35;
	j = 197;
	do
	{
		while (--j);
	} while (--i);
}
/*���������ʱ����С����*/
void Delay17500us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 32;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}
void Delay2500us()		//@11.0592MHz
{
	unsigned char i, j;

	i = 5;
	j = 120;
	do
	{
		while (--j);
	} while (--i);
}

//��ʼ��
void Init()
{
	Servo = 0;
	Servo = 1;
	Delay1550us();
	Servo = 0;
	Delay18450us();
	Servo = 1;
	delay(1000);
}
void keyscan()
{
	for(;;)	//��ѭ��
	{
		if(key_s2 == 0)// ʵʱ���S2�����Ƿ񱻰���
		{
			delay(5); //�������
			if(key_s2 == 0)//�ټ��S2�Ƿ񱻰���
			{
				while(!key_s2);//���ּ��
				beep = 0;	//ʹ����Դ������
				delay(200);//200������ʱ
				beep = 1;	//�ر���Դ������
				break;		//�˳�FOR��ѭ��
			}
		}
	}	
}

void main()
{
	char i;
	Init();
	keyscan();
	while(1)
	{		
		/*���0��*/
		for(i=0;i<10;i++)
		{	
			Servo = 1;
			Delay1550us();
			Servo = 0;
			Delay18450us();
		}
		delay(1000);
		/*���-90��*/
		for(i=0;i<10;i++)
		{	
			Servo = 1;
			Delay2500us();
			Servo = 0;
			Delay17500us();
		}
		delay(1000);
		/*���90��*/
		for(i=0;i<10;i++)
		{	
			Servo = 1;
			Delay600us();
			Servo = 0;
			Delay19400us();
		}
		delay(1000);		
	}
}