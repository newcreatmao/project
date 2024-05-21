/***************************************************************************
ʵ�����ƣ� ���ⷢ��ʵ��

ʵ��ģ��:  	51��Ƭ�����İ塢���⴫���������������

ʵ����ߣ�  51��Ƭ�����İ�------���⴫����
					P3.5 --------- TXD				
			51��Ƭ�����İ�------���������			
					P1	 ---------  MK1
����������	1.ʹ������һ̨������ĺ�����ճ������
			2.���¾�����̵İ�������һ̨ʵ����ʾ���յ���������ֵ

����ʱ�䣺	2017.10.17
***************************************************************************/

#include <reg51.h>
#include "intrins.h"     //_nop_();��ʱ������

#define uchar unsigned char
#define uint  unsigned int

sbit  remoteout=P3^5;        //ң�������

uchar IRCOM[4];

/**********************************************************/
//x*0.14MS��ʱ
void delay(unsigned char x)
{
   unsigned char i;
   while(x--)
     {
        for (i = 0; i<13; i++) {}
     }
}

/**********************************************************/
// 1ms��ʱ�ӳ���
void delay1ms(int ms)
{
 unsigned char y;
  while(ms--)
 {
  for(y = 0; y<250; y++)
  {
   _nop_();
   _nop_();
   _nop_();
   _nop_();
  }
 }
}

/**********************************************************/
// ��ʱ����ʼ���ӳ���
void clearmen()
{
   remoteout=0;           //��ң�����
   IE=0x00;
   IP=0x01;
   TMOD=0x20;             //��ʱ��1�����ڷ�ʽ2����8λ�Զ���װģʽ
   TH1=0xF4;              //38KHZ��ֵ
   TL1=0xF4;
   EA=1;                  //�����ж�
}

/**********************************************************/
//38KHZ�������ӳ���
void Time1_int(void) interrupt 3 
{
   remoteout=~remoteout;
}

/**********************************************************/
// ���ݷ����ӳ���
void Transmition(unsigned char key_value)
{
    unsigned char i,j,temp;
    IRCOM[2]=key_value;
    IRCOM[3]=~key_value;
    ET1=1;TR1=1;
    delay1ms(3);    //9msǰ���͵�ƽ
    ET1=0;TR1=0;
    delay1ms(1);
    delay(8);       //������ʱ����4ms�����
    for(i=0;i<4;i++)
    {
       for(j=0;j<8;j++)
          {
             temp=(IRCOM[i]>>j)&0x01;
             if(temp==0)//����0
                {
                   ET1=1;TR1=1;
                   delay(4);//��ʱ0.56ms
                   ET1=0;TR1=0;
                   delay(4);//��ʱ0.56ms
                 }
             if(temp==1)//����1
                 {
                   ET1=1;TR1=1;
                   delay(4);//��ʱ0.56ms
                   ET1=0;TR1=0;
                   delay(14);//��ʱ1.48ms
                 }
          }
    }
    ET1=1;TR1=1;//����
    delay(4);   //��ʱ0.56ms
    ET1=0;TR1=0;//�رպ��ⷢ��
}

/**********************************************************/
// ��ɨ���ӳ���
unsigned char keyscan(void)
{
    unsigned char temp,key;
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
    return(key);
}

/*************************************************************/
//�жϼ��Ƿ���
void  keydown(void)
{  
  	P1=0xF0;
   delay1ms(5);
	if(P1!=0xF0)
	{
	  keyscan();
    }
}
/**********************************************************/

/**********************************************************/
main()
{
   IRCOM[0]=0x00;IRCOM[1]=0xFF;IRCOM[2]=0x48;IRCOM[3]=0xB7;
   clearmen();
   while(1)
     {
        keydown();
        if(keyscan()!=0xFF) Transmition(keyscan());
     }
}