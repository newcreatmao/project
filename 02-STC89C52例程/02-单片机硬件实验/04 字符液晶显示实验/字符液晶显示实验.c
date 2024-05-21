/***************************************************************************
ʵ�����ƣ� 1602�ַ���ʾʵ��

ʵ��ģ��:  51��Ƭ�����İ塢Һ����ʾ��

ʵ����ߣ� 51��Ƭ�����İ�------Һ����ʾ��
				 P3.0--------------RS
				 P3.1--------------RW
				 P3.2--------------E
			P0.0~P0.7--------------DB0~DB7
				
						
����������1602 ��ʾ�����ַ�

����ʱ�䣺2017.10.17
***************************************************************************/
#include<reg52.h>		//��ӿ��ļ�
#define uint unsigned int
#define uchar unsigned char

sbit E = P3^2;			//����ܽ�
sbit RW = P3^1;
sbit RS = P3^0;

void mDelay(uint Delay)	//��ʱ
{	uint i;
	for(;Delay > 0;Delay--)
		for(i = 0;i < 110;i++);
}


void LCD1602Write_data(uchar i)	//LCD1602д����
{
	//E=0;
	RS = 1;//����
	RW = 0;//д��
	P0 = i;
	E = 1;//����
	mDelay(11);
	E = 0;
             
    
}
void LCD1602Write_com(uchar i)	//LCD1602дָ��
{

	RS = 0; //ָ��
	RW = 0; //д��
	P0 = i;
	E = 1;  //����д��
    mDelay(11);
	E = 0;          
}
void LCD1602Init()		 //LCD1602��ʼ��
{
	RW = 0;
	RS = 0;
	LCD1602Write_com(0x01);
	LCD1602Write_com(0x38);
	LCD1602Write_com(0x0c);		//�޹��
	LCD1602Write_com(0x06);	
}

void main()				//������
{
	unsigned char Code1[] = "1602 LCD TEST OK";//Code1��Ҫ��ʾ���ַ�Һ���ĵ�һ��
	unsigned char Code2[] = "HELLO EVERYONE!!"; //Code2��Ҫ��ʾ���ַ�Һ���ĵڶ���
 	unsigned char m;
	RW = 0;
	LCD1602Init();
	while(1)
	{ 
		LCD1602Write_com(0x80+0x00);	//�ڵ�һ�е�һ����ʾCode1
		for(m = 0;m < 40;m++)			
	   {
			LCD1602Write_data(Code1[m]);

			mDelay(10);			//��ʱ
       }
	LCD1602Write_com(0x80+0x40);		//�ڵڶ��е�һ����ʾCode2
		for(m = 0;m < 40;m++)			
	   {
			
			LCD1602Write_data(Code2[m]);	
			mDelay(10);			//��ʱ
}		
    }
}