/***************************************************************************
ʵ�����ƣ� �ⲿ�ж�ʵ��

ʵ��ģ��:  51��Ƭ�����İ塢����ܡ����뿪�ء��ᴥ������

ʵ����ߣ� 51��Ƭ�����İ�------����ܡ����뿪�ء��ᴥ������

						P1---------J4	
						
						P3.2---------K1
						
��������������һ��K1��LED���ն����Ƽӵķ�ʽϨ��

����ʱ�䣺2017.10.17
***************************************************************************/


#include<reg52.h>	//��ӿ��ļ�
#define uint unsigned int

void delay(int t){
	while(t--){
	unsigned char data i, j;
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
	}
}

void light_flout(){
	int i;
	for(i=0;i<8;i++){
		P1=(0x01<<i);
		delay(50);
	}
	for(i=7;i>-1;i--){
		P1=(0x01<<i);
		delay(50);
	}
}

void main(void)
{	
	IE=0x85;
	PX1=1;
	IT0 = 1;		//�ⲿ�ж�0�����崥����ʽ���½��ش������
	IT1 = 1;
	while(1){
				light_flout();
	}
}

void INIT_0(void) interrupt 0
{
	int i=0;
	P1=0xFF;
	for(i=0;i<3;i++){
	P1=0x00;
	delay(50);
	P1=0xFF;
	delay(50);
	}
}

void INIT_1(void) interrupt 2
{
	int i=0;
	for(i=0;i<3;i++){
	P1=0x0F;
	delay(50);
	P1=0xF0;
	delay(50);
	}
}




