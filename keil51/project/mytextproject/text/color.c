#include <REGX52.H>
#include"color.h"

sbit SCLK=P3^6;
sbit IO=P3^4;
sbit CE=P3^5;

unsigned char DS1302_Time[]={23,04,15,12,59,55,6};

void init()//BCD�룬0001 0011��ʾ13��һλ��ʾʮλ��һλ��ʾ��λ
{
	CE=0;
	SCLK=0;
}	//ʱ�ӳ�ʼ��
void write(unsigned char com,Data)
{
	unsigned char i;
	CE=1;
	for(i=0;i<8;i++)
	{
	IO=com&(0x01<<i);//ѡȡ��nλ
	SCLK=1;//����Ƶ��
	SCLK=0;//ѡȡ��nλ
	}
	for(i=0;i<8;i++)
	{
	IO=Data&(0x01<<i);//ȡ����nλ
	SCLK=1;//����Ƶ��
	SCLK=0;//д���nλ
	}
	CE=0;
}
unsigned char read(unsigned char com)
{
	unsigned char i,Data=0x00;
	com|=0x01;
	CE=1;
	for(i=0;i<8;i++)
	{
	IO=com&(0x01<<i);//ѡȡ��nλ
	SCLK=0;//����Ƶ��
	SCLK=1;//ѡȡ��nλ
	}
	for(i=0;i<8;i++)
	{
	SCLK=1;//����һλ�����庬ȥ��
	SCLK=0;
	if(IO)
	{
		Data|=(0x01<<i);
	}
  }
	CE=0;
	IO=0;//ѡȡ������
	return Data;
}

void settime(void)//BCD��ת��
{
	write(DS1302_WP,0x00);
	write(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
  write(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	write(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	write(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	write(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	write(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	write(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	write(DS1302_WP,0x80);
}

void readtime(void)
{
	unsigned char Temp;
	Temp=read(DS1302_YEAR);
	DS1302_Time[0]=Temp/16*10+Temp%16;
	Temp=read(DS1302_MONTH);
	DS1302_Time[1]=Temp/16*10+Temp%16;
	Temp=read(DS1302_DATE);
	DS1302_Time[2]=Temp/16*10+Temp%16;
	Temp=read(DS1302_HOUR);
	DS1302_Time[3]=Temp/16*10+Temp%16;
	Temp=read(DS1302_MINUTE);
	DS1302_Time[4]=Temp/16*10+Temp%16;
	Temp=read(DS1302_SECOND);
	DS1302_Time[5]=Temp/16*10+Temp%16;
	Temp=read(DS1302_DAY);
	DS1302_Time[6]=Temp/16*10+Temp%16;
}