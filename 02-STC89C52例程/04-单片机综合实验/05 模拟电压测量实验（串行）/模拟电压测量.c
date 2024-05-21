/***************************************************************************
ʵ�����ƣ� ģ���ѹ����ʵ�飨���У�

ʵ��ģ��:  51��Ƭ�����İ塢��̬ɨ���������������A/Dת�������ɵ���ѹ��

ʵ����ߣ�  51��Ƭ�����İ�------����A/Dת����
					P3.0----------------CLK
					P3.1----------------SDA
					P3.2----------------nCS
					
			51��Ƭ�����İ�------��̬ɨ���������
					P0----------------J6
					P2----------------J5
			�ɵ���ѹ��------����A/Dת����
				TESE-1----------------IN
				
����������	���ڿɵ���ѹ������ť���������ʾ��Ӧ�ĵ�ѹֵ

����ʱ�䣺2017.10.18
***************************************************************************/


#include<reg52.h>
#include <math.h>
#define	uchar unsigned char
#define	uint  unsigned int 

sbit CLK = P3^0;  //ʱ�Ӷ˿�
sbit SDA = P3^1;  //���ݶ˿�
sbit CS  = P3^2;  //Ƭѡ�˿�


#define DIGI P0 //�궨�壬��P0�ڶ���Ϊ�����
#define SELECT P2 //�궨�壬��P2����Ϊ�����ѡ���

uchar code tab[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7f,0x6f};
uchar select[]={0x01,0x02,0x04,0x08}; //ѡ����������飬����ѡ��1��2��..��

//**********��ʱn��us����**********************//
void  delay1(unsigned int delus)//1us
{  
  while(delus!=0)
	{ 
	 delus--;
	}
}

void display(float dis2) //����
{

		uint dis;
		dis2*=5000;
		dis=(uint)dis2;
		SELECT=select[3]; //ѡ���i�������
		DIGI=tab[dis/1000];
		delay1(500);
		SELECT=select[2]; //ѡ���i�������
		DIGI=tab[dis/100%10];
		delay1(500);
		SELECT=select[1]; //ѡ���i�������
		DIGI=tab[dis/10%10];
		delay1(500);
		SELECT=select[0]; //ѡ���i�������
		DIGI=tab[dis%10];
//		delay1(500);

}
//******************************************************
//��ʱ�ӳ���
void delay(unsigned int x)
{
	unsigned int y=x;
	do{y--;}
   while(y>1);
}

//******************************************************
//��ȡת����ֵ
unsigned int read()
{
 	unsigned int i=0,value=0;
	delay(2);
	for(i=0;i<8;i++)
	{
		CLK=1;	         //����������
		value=value<<1;  //��������һλ
		if(SDA==1)
         value=value+1;  //��ȡ��ֵ
		CLK=0;
	}
	return value;        //��������
}

//******************************************************
void main()
{
	uint data2=0;
	float data1=0;
	CLK=0;             //��ʼ��ʱ�Ӷ˿�
	CS=1;        //Ƭѡ	
	while(1)
	{
		CS=1;        //Ƭѡ
		delay(100);    //�ȴ�ת��
		CS=0;
		data2=read();//��ȡת������	
		data1=data2/255.0;
		display(data1);
	}
}




