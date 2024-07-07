/***************************************************************************
ʵ�����ƣ� ONE-WINE���߲���ʵ��

ʵ��ģ��:  51��Ƭ�����İ塢�¶ȴ�������Һ����ʾ��

ʵ����ߣ�  51��Ƭ�����İ�------�¶ȴ�����
					P1.3 --------- 1WIRE
										
			51��Ƭ�����İ�------Һ����ʾ����1602�ַ�Һ����
					P1.0 --------- RS
					P1.1 --------- RW
					P1.2 --------- E
			   P0.0~P0.7 --------- BD0~BD7		
						
����������	�����������¶�

����ʱ�䣺	2017.10.17
***************************************************************************/

//�������ƥ�����кţ������¶ȡ�
#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int
#define Data P0
sbit DQ=P1^3;//ds18b20�뵥Ƭ�����ӿ�
sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;	
uchar code str1[]={0x28,0x40,0xAD,0x82,0x03,0x00,0x00,0x8E};	//ROM1
uchar code str2[]={0x28,0x65,0xA5,0x82,0x03,0x00,0x00,0xED};	//ROM2 
uchar code table[8]={0x0c,0x12,0x12,0x0c,0x00,0x00,0x00,0x00};	// �����¶ȷ���
uchar data disdata[5];
uint tvalue;//�¶�ֵ
uchar tflag;//�¶�������־

/*************************lcd1602����**************************/
void delay1ms(uint ms)//��ʱ1���루������ȷ�ģ�
{  
	uint i,j;
	for(i=0;i<ms;i++)
	for(j=0;j<100;j++);
}

void wr_com(uchar com)//дָ��//
{ 
	delay1ms(1);
	RS=0;
	RW=0;
	EN=0;
	Data=com;
	delay1ms(1);
	EN=1;
	delay1ms(1);
	EN=0;
}

void wr_dat(uchar dat)//д����//
{ 
	delay1ms(1);;
	RS=1;
	RW=0;
	EN=0;
	Data=dat;
	delay1ms(1);
	EN=1;
	delay1ms(1);
	EN=0;
}
void wr_new()		  //д���ַ�
{
	uchar i;
	wr_com(0x40);
	for(i=0;i<8;i++)
	{
		wr_dat(table[i]);
	}
}
void lcd_init()//��ʼ������//
{	delay1ms(15);
	wr_com(0x38);delay1ms(5);
	wr_com(0x08);delay1ms(5);
	wr_com(0x01);delay1ms(5);
 	wr_com(0x06);delay1ms(5);
	wr_com(0x0c);delay1ms(5);
	wr_new();
	wr_com(0x80);
    wr_dat('N');
	wr_com(0x81);
    wr_dat('o');
	wr_com(0x82);
    wr_dat('1');
	wr_com(0x83);
    wr_dat(':');
  	wr_com(0x8b);
    wr_dat(0x00);
	wr_com(0x8c);
    wr_dat('C');
	wr_com(0xcb);
    wr_dat(0x00);		//�����¶��ַ�
	wr_com(0xcc);
    wr_dat('C');
	wr_com(0xc0);
    wr_dat('N');
	wr_com(0xc1);
    wr_dat('o');
	wr_com(0xc2);
    wr_dat('2');
	wr_com(0xc3);
    wr_dat(':');
}

/******************************ds1820����***************************************/
void delay_18B20(uint i)//��ʱ1΢��
{
   while(i--);
}



void ds1820rst()/*ds1820��λ*/
{   uchar x=0;
	DQ = 1;          //DQ��λ
	delay_18B20(4); //��ʱ
	DQ = 0;          //DQ����
	delay_18B20(100); //��ȷ��ʱ����480us
	DQ = 1;          //����
	delay_18B20(40); 
} 

uchar ds1820rd()/*������*/
{ uchar i=0;
  uchar dat = 0;
  for (i=0;i<8;i++)
	{   
		DQ = 0; //�������ź�
		dat>>=1;
		DQ = 1; //�������ź�
		if(DQ)
		dat|=0x80;
		delay_18B20(10);
	}
   return(dat);
}
void ds1820wr(uchar dat)/*д����*/
{ 	uchar i=0;
    for (i=0; i<8; i++)
	{ DQ = 0;
	  DQ = dat&0x01;
	  delay_18B20(10);
	  DQ = 1;
	  dat>>=1;
	}
}
void b20_Matchrom(uchar a)	 //ƥ��ROM
{
	char j;
	ds1820wr(0x55);	   //����ƥ��ROM����
	if(a==1)
	{
	for(j=0;j<8;j++)
		ds1820wr(str1[j]);		//����18B20�����кţ��ȷ��͵��ֽ� 
	}
	if(a==2)
	{
	for(j=0;j<8;j++)
		ds1820wr(str2[j]);		//����18B20�����кţ��ȷ��͵��ֽ� 
	}

} 
read_temp(uchar z)/*��ȡ�¶�ֵ��ת��*/
{	uchar a,b;
	float tt;
	ds1820rst();    
	ds1820wr(0xcc);			//�����к�
	ds1820rst(); 
	if(z==1)
	{
		b20_Matchrom(1);		 //ƥ��ROM 1
	}
	if(z==2)
	{
		b20_Matchrom(2);		 //ƥ��ROM	 2
	}
	ds1820wr(0x44);//*�����¶�ת��*/
	delay1ms(5);
	ds1820rst();    
	ds1820wr(0xcc);				//�����к�
	ds1820rst(); 
	if(z==1)
	{
		b20_Matchrom(1);			    //ƥ��ROM 1
	}
	if(z==2)
	{
		b20_Matchrom(2);				//ƥ��ROM	 2
	}
	ds1820wr(0xbe);//*��ȡ�¶�*/ 
	a=ds1820rd();
	b=ds1820rd();
	tvalue=b;
	tvalue<<=8;
	tvalue=tvalue|a;
    if(tvalue<0x0fff)
    tflag=0;
    else
   		{	
			tvalue=~tvalue+1;
			tflag=1;
 		}
	tt=tvalue*0.0625;
	tvalue=tt*10;
	return(tvalue);
}

/*****************��ʾ����******************************/
void ds1820disp(uchar z)//�¶�ֵ��ʾ
{    
	 uchar flagdat;
     disdata[0]=tvalue/1000+0x30;//��λ��
     disdata[1]=tvalue%1000/100+0x30;//ʮλ��
     disdata[2]=tvalue%100/10+0x30;//��λ��
     disdata[3]=tvalue%10+0x30;//С��λ
    
	if(tflag==0)
	flagdat=0x20;//���¶Ȳ���ʾ����
	else
	flagdat=0x2d;//���¶���ʾ����:-

	if(disdata[0]==0x30)
	{disdata[0]=0x20;//�����λΪ0������ʾ
	if(disdata[1]==0x30)
	{disdata[1]=0x20;//�����λΪ0��ʮλΪ0Ҳ����ʾ
	}
   }
  if(z==1)
    {
		wr_com(0x84);
		wr_dat(flagdat);//��ʾ����λ
		wr_com(0x85);
		wr_dat(disdata[0]);//��ʾ��λ
		wr_com(0x86);
		wr_dat(disdata[1]);//��ʾʮλ 
		wr_com(0x87);
		wr_dat(disdata[2]);//��ʾ��λ 
		wr_com(0x88);
		wr_dat(0x2e);//��ʾС���� 
		wr_com(0x89);
		wr_dat(disdata[3]);//��ʾС��λ
   }
  if(z==2)
    {
		wr_com(0xc4);
		wr_dat(flagdat);//��ʾ����λ
		wr_com(0xc5);
		wr_dat(disdata[0]);//��ʾ��λ
		wr_com(0xc6);
		wr_dat(disdata[1]);//��ʾʮλ 
		wr_com(0xc7);
		wr_dat(disdata[2]);//��ʾ��λ 
		wr_com(0xc8);
		wr_dat(0x2e);//��ʾС���� 
		wr_com(0xc9);
		wr_dat(disdata[3]);//��ʾС��λ
   }
}
/********************������***********************************/
void main()
{ 
	lcd_init();//��ʼ����ʾ
    while(1)
    {
 		read_temp(1);//��ȡ�¶�
 		ds1820disp(1);//��ʾ
		read_temp(2);//��ȡ�¶�
		ds1820disp(2);//��ʾ
  }
}
