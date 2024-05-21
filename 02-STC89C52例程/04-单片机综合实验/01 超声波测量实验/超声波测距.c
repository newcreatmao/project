
//**************ͷ�ļ�************//
#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include <math.h>
//#include "1602.c" //1602��ʾ����
#include "12864.c" //12864��ʾ����
#define	uchar unsigned char
#define	uint  unsigned int 
sbit been=P3^1;
//sbit P37=P3^0;//555�����շ�λ
//**********��������**************//
float distance;
float dis1; 
uchar high_time,low_time;
bit flag=0;//��־λ
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
//***********��ʼ��*******************//             
void init()
{  
//******** ��ʱ��0****************//
   	TMOD=0x01;//��ʱ��0��ʽ1���ڼ�ʱ
	TH0=0; //��ʱ����ʼ��
	TL0=0;
	TR0=0;//���ҹرն�ʱ��0	       
//*********���ж�****************//	
	EA=1; //�����ж�
//*********���ж�1***************//
    IT0=1;//�½�����Ч,�󴫸���
//    LCD_init();
	LCD12864_Init();
	LCD12864_Clear();
	Display();
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
	P37 = 1;
	TR0=1;//����ʱ0	
	EX0=1;
	delay1(4*4);
	P37 = 0;
	delay_nms(5*4);
	if(flag==1) //�Ƿ����жϴ�����
	{
		distance=Distance_count();//�д�������þ�����㺯��
		dis1=distance;
		flag=0;
	}
	else 
		dis1=0;
}
//**************������****************//

void main()
{ 

	init();//������ʼ��
	while(1)
	{	
		tran();
		dis1 *= 10;


		if(dis1<110&&dis1>10)
		{
			been=~been;
			delay_nms(50);
		}
		else	been=1;
/*
//****************1602��ʾ����*************************			  
		sprintf(dis,"Measure distance"); 			//*
		DispStrPosi(dis,0,0);						//*
		sprintf(dis,"Range=%0.1f mm  ",dis1);		//*
		DispStrPosi(dis,0,1);						//*
		delay_nms(100);								//*
													//*
//*****************************************************
*/


//****************12864��ʾ����************************			  
		display(dis1*10);							//*
		delay_nms(10);								//*
//*****************************************************



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


 
  
