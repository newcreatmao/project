/***************************************************************************
ʵ�����ƣ� 	�����������ʵ��

ʵ��ģ��:  	51��Ƭ�����İ塢��������������뿪����

ʵ����ߣ�  51��Ƭ�����İ� --------- ���������
					P0.0 ------------ A
					P0.1 ------------ B
					P0.2 ------------ C
					P0.3 ------------ D
					
			51��Ƭ�����İ� --------- ���뿪����
					P0.4 ------------  SW1

����������	�����������SW1������˳ʱ��ת������ʱ��ת��

����ʱ�䣺	2017.10.17
***************************************************************************/

#include<reg52.h> 
#define uint unsigned int 
#define uchar unsigned char 

// ���岽��������������
sbit ap = P0^0;
sbit cp = P0^1;
sbit bp = P0^2;
sbit dp = P0^3;
// ��������ת����
sbit tp = P0^4;

void mDelay(uint Delay)	//��ʱ
{
	uint i;
	for(;Delay > 0;Delay--)	 
		for(i = 0;i < 210;i++);
}

void ff_setp()
{
	ap = 1;
	bp = 0;
	cp = 0;
	dp = 1;
	mDelay(10);
	bp = 1;
	dp = 0;
	mDelay(10);
	cp = 1;
	ap = 0;
	mDelay(10);
	dp = 1;
	bp = 0;
	mDelay(10);	
}

void bw_setp()
{
	ap = 1;
	bp = 1;
	cp = 0;
	dp = 0;
	mDelay(10);
	bp = 0;
	dp = 1;
	mDelay(10);
	ap = 0;
	cp = 1;
	mDelay(10);
	dp = 0;
	bp = 1;
	mDelay(10);		
}


void main()
{
	ap = 1;
	bp = 1;
	cp = 1;
	dp = 1;

	while(1)
	{ 
		if(!tp)
			ff_setp();
		else
			bw_setp();
	  mDelay(300);		// ��ʱ���������ת��
	  	
	}

}







