/***************************************************************************
ʵ�����ƣ� ����DAת��ʵ��

ʵ��ģ��:  51��Ƭ�����İ塢��D/Aת����

ʵ����ߣ�  51��Ƭ�����İ�------����D/Aת����
					P2.0--------- CLK
					P2.1--------- DATA
					P2.2--------- LOAD
					P2.3--------- LDAC
						
����������	ʹ��ʾ�����۲�J24�ڵ�DCDA������������Ҳ�

����ʱ�䣺	2017.10.17
***************************************************************************/

#include<reg52.h>     

sbit SCLK    = P2^0;
sbit Data_in = P2^1;
sbit LOAD    = P2^2;
sbit LDAC    = P2^3;

unsigned char  code tab[128]={
64,67,70,73,76,79,82,85,88,91,94,96,99,102,104,106,
109,111,113,115,117,118,120,121,123,124,125,126,126,
127,127,127,127,127,127,127,126,126,125,124,123,121,
120,118,117,115,113,111,109,106,104,102,99,96,94,91,
88,85,82,79,76,73,70,67,64,60,57,54,51,48,45,42,39,
36,33,31,28,25,23,21,18,16,14,12,10,9,7,6,4,3,2,1,
1,0,0,0,0,0,0,0,1,1,2,3,4,6,7,9,10,12,14,16,18,21,23,
25,28,31,33,36,39,42,45,48,51,54,57,60};       //�������ݱ��

void DAC(unsigned  int DA_DATA)      //DAת��
{

    unsigned  char i;
	unsigned  int a,temp;

    LOAD=1;
	for(i=0;i<8;i++)
	{
	   SCLK=1;
	   
	   a=DA_DATA&0x80;
	   if(a==0x80)
		   Data_in=1;
	   else
		   Data_in=0;
	   
	   SCLK=0;
	 
	   temp=DA_DATA<<1;
		 DA_DATA=temp;             
	 }
    LOAD=0;
    LOAD=1;
}
  


void Output_channel(char channel)         //���ͨ��ѡ��
{
    unsigned char i;
    switch(channel)
       {
          case 0:for(i=0;i<2;i++)
                    {
                       SCLK=1;
                       Data_in=0;
                       SCLK=0;
                     };
                 break;
          case 1:SCLK=1;
                 Data_in=0;
                 SCLK=0;
                 SCLK=1;
                 Data_in=1;
                 SCLK=0;
                 break;
          case 2:SCLK=1;
                 Data_in=1;
                 SCLK=0;
                 SCLK=1;
                 Data_in=0;
                 SCLK=0;
                 break;
          case 3:SCLK=1;
                 Data_in=1;
                 SCLK=0;
                 SCLK=1;
                 Data_in=1;
                 SCLK=0;
                 break;
          default:break;
     }
}



void Write_RNG(unsigned char RNG_value)   //���������ѹ��Χ�����TLC5620�����ֲᣩ
{
    SCLK=1;
    Data_in=RNG_value;
    SCLK=0;
}

void main()
{
   unsigned  int j=0;
	while(1)
	{
      LDAC=0;
      LOAD=1;
      Output_channel(0);    //ѡ��ͨ��A
      Write_RNG(1);         //���������ѹ��Χ������ο���ѹ��������Χ��
      if(++j==128)
          j=0;
      DAC(tab[j]);
	}
}

