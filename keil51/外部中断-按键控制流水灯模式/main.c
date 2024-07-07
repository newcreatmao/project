#include <REGX52.H>
#include "Delay.h"
#include "EX0.h"

unsigned char i,Mode=0;


void LED_1()
{
	
	for(;i<8;i++)
	{
		if(i==7)
			i=0;
		if(Mode){	//ģʽ1
			P2=~(0x01<<i);
			Delay(30);
		}
		else 
		{
			i=7-i;
			break;
		}
		//ģʽ0���˳�LED_1
	}
}


void LED_0()
{
	for(;i<8;i++)
	{	
		if(i==7)
			i=0;
		if(Mode==0){
			P2=~(0x80>>i);
			Delay(30);
		}
		else 
		{
			i=7-i;
			break;
		}
	//ģʽ1���˳�LED_0
	}
}

void main()
{

	EX0_Init();
	
	while(1)
	{
		if(Mode==0)LED_0();	//������
		if(Mode==1)LED_1();	//������
	}
}

void EX0_ISR() interrupt 0
{
	if(P3_2==0){		//��������
		Delay(10);		//���������ܵ����ظ������ж�
		while(P3_2==0);
		Delay(10);
		
//		if(Mode)Mode =0;	//ģʽת��
//		else Mode=1;
		Mode=(Mode+1)%2;	//ģʽ(0��1)�л�

//����ģʽ:
//		Mode=(Mode+1)%2;	//ģʽ(0��1��2)
//		Mode=(Mode+1)%2+1;	//ģʽ(1��2��3)
	}

}
//Mode = ~Mode;		�������ModeΪ un char��)  ~0 = 1111 1111  ~1=1111 1110









