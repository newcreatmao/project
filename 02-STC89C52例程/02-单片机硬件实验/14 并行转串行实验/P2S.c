/***************************************************************************
ʵ�����ƣ� ����ת����ʵ��

ʵ��ģ��:  51��Ƭ�����İ塢����ת�����������뿪������LED��ʾ��

ʵ����ߣ�  51��Ƭ�����İ�------����ת������
					P1.0---------SLK
					P1.1---------SDA
					P1.2---------SFT_LD
					
			51��Ƭ�����İ�------LED��ʾ��
					P0  ---------J4
					
			����ת������------���뿪����
					J8	--------- J1
						
����������	��������SW1~SW8����LED��D1~D8������

����ʱ��	�2017.10.17
***************************************************************************/

#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int
                                                   
sbit CLK = P1^0;
sbit SDA = P1^1;
sbit SF  = P1^2;


void mDelay(uint Delay)	//��ʱ
{	uint i;
	for(;Delay > 0;Delay--)
		for(i = 0;i < 110;i++);
}

uchar receive() 	   //��ȡ�ֽڵĳ���
{     
	uchar byte = 0,c;  
	for(c = 0; c < 8; c++) 		
	{ 
		byte = byte<<1; 		//��������һλ
		CLK = 1;
		CLK = 0;
		if(SDA) 				//��ȡ���λ����
			byte = byte|0x01; 		
		CLK = 1;

	       
	} 
	return(byte);
} 


void main() //������
{
	uchar a = 0;
	while(1)
	{
		SF = 1;			   		//��������
		SF = 0;
		SF = 1;
		a = receive();
		P0 = a;
 
	}
}

