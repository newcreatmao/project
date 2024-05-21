/***************************************************************************
ʵ�����ƣ�  ֱ���������ʵ����� 

ʵ��ģ��	51��Ƭ�����İ塢ֱ���������LCD12864��ʾ�� ��������չIO�������������

ʵ����ߣ�	 51��Ƭ�����İ�------LCD12864��ʾ��
				   P2.0--------------CS1
				   P2.1--------------CS2
				   P2.2--------------CS
				   P2.3--------------RW
				   P2.4--------------E
			  P0.0~P0.7--------------DB0~DB7
				
			 51��Ƭ�����İ�------������չIO��		
				  P3.0--------------A0				   						 
				  P3.1--------------A1
					   
					T/R��+5V  nOE ��GND
			 51��Ƭ�����İ�------ֱ�������	   
				 P3.2--------------SPEED
			 ������չIO�� ------  ֱ������� 
				  B0--------------MOTO1
				  B1 --------------MOTO2
			51��Ƭ�����İ�------���������
				  P1 -------------- MK1
				  
���������L�������������Ӧ������ֱ�����ִ����ع��ܡ�
		  

����ʱ�䣺2017.08.18
***************************************************************************/ 


#include <reg52.h> 
#include<12864.c>    
#define uchar unsigned char
#define uint unsigned int

#define CIRCLE 25  //�ٶȿɵ��ڵĵ�λ����

uchar count=1,last=10;
uchar temp,key;
uint time,speed;
bit  PWM,flag=0;
uchar kt=0;
sbit Moto1 = P3^0;
sbit Moto2 = P3^1;

void mDelay(uint Delay)	//��ʱ
{
	uint i;
	for(;Delay > 0;Delay--)	 
		for(i = 0;i < 110;i++);
}
void Timer0(void) interrupt 1  //��ʱ��0����жϷ����ӳ������ڲ���PWM��
{
   count++;
   if(count>CIRCLE) 
     {
        count=1;
     } 
   if(count<=last)
      PWM=0;
   else 
      PWM=1;
   TH0=0xFC;
   TL0=0x66;
}

void INT_0 (void) interrupt 0  //�ⲿ�ж�0�жϷ����ӳ������ڼ�¼������ģ�������������Ŀ
{
   EX0=0;    //��ֹ�ⲿ�ж�0�ж�
   time++;
   EX0=1;    //�����ⲿ�ж�0�ж�
}



void Timer1 (void) interrupt 3 //��ʱ��1����жϷ����ӳ������ڻ�ȡ�ٶ�ֵ
{
   TH1=0x4C;      //��װ��ʱ��ֵ
   TL1=0x00;      //50ms��ʱ
   time=time*300;        //��ֹ��λ��ȥ��
   speed=(time/3)*20;    //�ٶȣ�r/s
   speed=speed/300;
   time=0;
}


void INT_Init() //ϵͳ��ʼ����������ʼ����ʱ��T0��T1���ⲿ�ж�0
{
   TMOD=0x10;     //ѡ��T1�����ڷ�ʽ1
   TH1=0x4C;
   TL1=0x00;      //50ms��ʱ
   ET1=1;         //����T1�ж�
   TR1=1;         //����T1�ж�

   ET0=1;         //����T0�ж�
   TH0=0xFC;
   TL0=0x66;
   TR0=1;         //����T0�ж�

   IT0=1;         //�½��ش���
   EX0=1;         //�����ⲿ�ж�0�ж�

   EA=1;          //�������ж�

   	LCD12864_Init();
	LCD12864_Clear();
	Display();
}

/**********************************************************/
// ��ɨ���ӳ���
void  keyscan(void)
 { 
    P1=0xF0;                //����Ϊ���룬����Ϊ����������������ȫΪ0
	temp=P1;                //��P1��       
    temp=temp&0xF0;
    temp=~((temp>>4)|0xF0);
    if(temp==1)
        key=0;
    else if(temp==2)
        key=1;
    else if(temp==4)
        key=2;
    else if(temp==8)
        key=3;
    P1=0x0F;                 //����Ϊ���룬����Ϊ����������������ȫΪ0  
	 temp=P1;                 //��P1�� 
    temp=temp&0x0F;
    temp=~(temp|0xF0);        
    if(temp==1)
        key=key+0;
    else if(temp==2)
        key=key+4;
    else if(temp==4)
        key=key+8;
    else if(temp==8)
        key=key+12;

	while(temp)
	{
		P1=0x0F;                 
		temp=P1;                
		temp=temp&0x0F;
		temp=~(temp|0xF0); 
	}

 }

/*************************************************************/
//�жϼ��Ƿ���
void  keydown(void)
 {  

  	P1=0xF0;
    mDelay(5);
	if(P1!=0xF0)
	{
	  keyscan();
	  	switch(mm[key])
		{
			case 0:
				kt=1;
				break;	
			case 2:
				last--;
				if(last<1)
					last=25;
				break;	
			case 4:
				flag=0;
				break;	
			case 5:
				kt=0;
				break;	
			case 6:
				flag=1;
				break;	
			case 8:
				last++;
				if(last>=25)
					last=1;
				break;	
			default:	
				break;
			
		}
    }
 }
void main(void)   //������
{

	INT_Init();
	while(1)
	{
		keydown();
		display(key,speed);
		if(kt)
		{		
			if(flag)//����
			{
				Moto1=PWM;
				Moto2=0;
			}
			if(!flag)//����
			{
				Moto2=PWM;
				Moto1=0;
			}
		}
		else 
		{
			Moto2=0;
			Moto1=0;			
		}
	}
}