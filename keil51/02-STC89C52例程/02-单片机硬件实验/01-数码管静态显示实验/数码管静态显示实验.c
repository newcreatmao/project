/***************************************************************************
ʵ�����ƣ� ��̬�������ʾʵ��

ʵ��ģ��:  51��Ƭ�����İ塢��̬�������

ʵ����ߣ� 51��Ƭ�����İ�------��̬�������
						P1.0---------CLK
						
						P1.1---------SDA
						
����������ѭ����ʾ��0~f��

����ʱ�䣺2017.10.17
***************************************************************************/


#include<reg52.h> 
#define uint unsigned int 
#define uchar unsigned char 
sbit DAT = P1^1;		//����ܽ�P1.1
sbit CLK = P1^0;		//����ܽ�P1.0
uchar code tab[] = {0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,
					0xff,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};//0-F�����������ʾ��16������

 
void sendbyte(uchar byte) 	   	//�����ֽڵĳ���
{     
	uchar num,c;  
	num = tab[byte];		   	//ȡ����
	for(c = 0; c < 8; c++) 		//����8λ����
	{ 
		CLK = 0; 
		DAT = num&0x01; 		//�������λ����
		CLK = 1; 
		num>>=1; 				//��������һλ
	       
	} 
} 
void mDelay(uint Delay)	//��ʱ
{	uint i;
	for(;Delay > 0;Delay--)
		for(i = 0;i < 110;i++);
}


main() 
{  
	unsigned char h; 
	while(1){ 
		for(h = 0; h < 16; h++){   	//���ΰ�tab��16���������ȥ
			mDelay(50);				//������ʱ������ʱ50���� 
			sendbyte(h); 	  		//���÷����ֽڵĳ���
			mDelay(500);			//������ʱ������ʱ500���� 
		} 
		h = 0; 
	} 
     
} 

