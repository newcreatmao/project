/***************************************************************************
ʵ�����ƣ� ����������ʵ��

ʵ��ģ��:  51��Ƭ�����İ塢������������ģ��

ʵ����ߣ� 51��Ƭ�����İ�------������������ģ��
				 P3.0--------------IN
				 P3.1--------------BEEP
				 P3.2--------------OUT
			
			P0.0~P0.7--------------A~DP
			P2.0~P2.3--------------COM1~COM3		
						
����������12864��ʾ�����ַ�

����ʱ�䣺2017.10.17
***************************************************************************/
//**************ͷ�ļ�************//
#include <reg52.h>
#include <intrins.h>
#include <math.h>
#define	uchar unsigned char
#define	uint  unsigned int 
sbit been=P3^1;
sbit P30=P3^0;//555�����շ�λ
//**********��������**************//
float distance;
float dis1; 
uchar high_time,low_time;
bit flag=0;//��־λ


#define DIGI P0 //�궨�壬��P0�ڶ���Ϊ�����
#define SELECT P2 //�궨�壬��P2����Ϊ�����ѡ���

uchar code tab[] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7f,0x6f};
uchar select[]={0x01,0x02,0x04,0x08}; //ѡ����������飬����ѡ��1��2��..��



//******��ʱn��ms����*****************//
void delay_nms(uint ms)   //delay ms function                              
{   uchar i; 
    while(ms--)
   {
    for(i = 0; i < 100; i++);
   }
}
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
		dis=(uint)dis2;
		SELECT=select[0]; //ѡ���i�������
		DIGI=tab[dis/1000];
		delay1(500);
		SELECT=select[1]; //ѡ���i�������
		DIGI=tab[dis/100%10];
		delay1(500);
		SELECT=select[2]; //ѡ���i�������
		DIGI=tab[dis/10%10];
		delay1(500);
		SELECT=select[3]; //ѡ���i�������
		DIGI=tab[dis%10];
//		delay1(500);

}

//***********��ʼ��*******************//             
void init()
{  
//******** ��ʱ��0****************//
   	TMOD=0x11;//��ʱ��0��ʽ1���ڼ�ʱ
	TH0=0; //��ʱ����ʼ��
	TL0=0;
//	ET0=1;
	TR0=0;//���ҹرն�ʱ��0	       
//*********���ж�****************//	
	EA=1; //�����ж�
//*********���ж�1***************//
    IT0=1;//�½�����Ч,�󴫸���
	      
}
//**********  ������㺯��********//
float Distance_count()
{
  float temp;
  temp=high_time*256+low_time;//ʱ��Ϊ΢�뼶
  temp=(temp/10000)/2;//��λת��	
  temp*=344; //������㣬S=V*T
  return temp;
}
//****** ��������������*******//   
void tran()
{
	TH0=0;
	TL0=0;//�嶨ʱ0
	P30 = 1;
	TR0=1;//����ʱ0	
	EX0=1;
	delay1(4*4);
	P30 = 0;
	delay_nms(5*4);
	if(flag==1) //�Ƿ����жϴ�����
	{
		distance=Distance_count();//�д�������þ�����㺯��
		dis1=distance*10;
		flag=0;
	}
	else 
		dis1=0;
	if(dis1<110&&dis1>10)
	{
		been=~been;
		delay_nms(50);
	}
	else	been=0;
}
//**************������****************//

void main()
{ 

	init();//������ʼ��
	while(1)
	{	
   		display(dis1);
		tran();
	}
} 
//*************�ⲿ�жϼ�����0*********//
 void TT() interrupt 0
{
	unsigned int tmp;
	TR0=0;//�ض�ʱ��0
	ET0=0;//���ⲿ�ж�
	flag=1;//�ⲿ�жϱ�־λ
	tmp=TH0*256+TL0; //�����ⲿ�ж� 
	if((tmp>0)&&(tmp<5174))	
     {
	  high_time=TH0;
	  low_time=TL0;	
	}
	else 
	{
	 high_time=0;
	 low_time=0;	
	} 

}
 
