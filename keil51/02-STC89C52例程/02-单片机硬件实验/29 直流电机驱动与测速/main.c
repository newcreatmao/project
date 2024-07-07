/***************************************************************************
ʵ�����ƣ� 	ֱ��������������ʵ��

ʵ��ģ��:  	51��Ƭ�����İ塢��I/O��չ�����ᴥ��������ֱ���������Һ����ʾ��

ʵ����ߣ�  51��Ƭ�����İ� --------- ��I/O��չ��
					P2.6 ------------ A0
					P2.7 ------------ A1
					
			51��Ƭ�����İ� --------- �ᴥ������
					P1.0 ------------ K1
					P1.1 ------------ K2
					
			51��Ƭ�����İ� --------- ֱ�������
					P3.2 ------------ SPEED
					
			51��Ƭ�����İ�------Һ����ʾ����1602�ַ�Һ����
					P2.0 ------------ RS
					P2.1 ------------ RW
					P2.2 ------------ E
			   P0.0~P0.7 ------------ BD0~BD7
			   
			��I/O��չ�� --------- ֱ�������
					  B0 ------------ MOTO1
					  B1 ------------ MOTO2
					  
			ע����I/O��չ���� T/R��+5V��OE��GND
			
����������	������ťK1�ı�����ת�٣��������K2�ı���ת������

����ʱ�䣺	2017.10.17
***************************************************************************/

#include <reg52.h>    
#define uchar unsigned char
#define uint unsigned int

#define CIRCLE 15  //�ٶȿɵ��ڵĵ�λ����

unsigned char count=1,last=1;
char old=0 ,new=0;

sbit  LCM_RS = P2^0; //��������
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80 //���ڼ��LCM״̬���е�Busy��ʶ

uint time,speed;
uchar Dis[]="  Speed:000r/s  ";//������ʾ��ʽ

bit  PWM,flag=0;
sbit Moto1 = P2^6;
sbit Moto2 = P2^7;
sbit key   = P1^0;
sbit dir   = P1^1;


//LCM1602��غ���,��״̬
unsigned char ReadStatusLCM(void)
{
    LCM_Data = 0xFF; 
    LCM_RS = 0;
    LCM_RW = 1;
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1;
    while (LCM_Data & Busy); //���æ�ź�
    return(LCM_Data);
    LCM_E = 0;
}


//5ms��ʱ
void Delay5Ms(void)
{
    unsigned int TempCyc = 5552;
    while(TempCyc--);
}

//д����
void WriteDataLCM(unsigned char WDLCM)
{
    ReadStatusLCM(); //���æ
    LCM_Data = WDLCM;
    LCM_RS = 1;
    LCM_RW = 0;
    LCM_E = 0; //�������ٶ�̫�߿���������С����ʱ
    LCM_E = 0; //��ʱ
    LCM_E = 1;
    LCM_E = 0;
}

//дָ��
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysCΪ0ʱ����æ���
{
    if (BuysC) ReadStatusLCM(); //������Ҫ���æ
    LCM_Data = WCLCM;
    LCM_RS = 0;
    LCM_RW = 0; 
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1; 
    LCM_E = 0;
}

//������
unsigned char ReadDataLCM(void)
{
    LCM_RS = 1; 
    LCM_RW = 1;
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1;
    return(LCM_Data);
    LCM_E = 0;
}

//LCD����ָ��λ�ó���
void LCM_pos(char position)
{						
	WriteCommandLCM(position|0x80);	//����ָ��=80+��ַ��(00H~27H,40H~67H)
}

//LCM��ʼ��
void LCMInit(void) 
{
    LCM_Data = 0;
    WriteCommandLCM(0x38,0); //������ʾģʽ���ã������æ�ź�
    Delay5Ms(); 
    WriteCommandLCM(0x38,0);
    Delay5Ms(); 
    WriteCommandLCM(0x38,0);
    Delay5Ms(); 

    WriteCommandLCM(0x38,1); //��ʾģʽ����,��ʼҪ��ÿ�μ��æ�ź�
    WriteCommandLCM(0x08,1); //�ر���ʾ
    WriteCommandLCM(0x01,1); //��ʾ����
    WriteCommandLCM(0x06,1); //��ʾ����ƶ�����
    WriteCommandLCM(0x0C,1); //��ʾ�����������
}

//��ָ��λ����ʾһ���ַ�
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
    Y &= 0x1;
    X &= 0xF;         //����X���ܴ���15��Y���ܴ���1
    if (Y) X |= 0x40; //��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
    X |= 0x80;        //���ָ����
    WriteCommandLCM(X, 0); //���ﲻ���æ�źţ����͵�ַ��
    WriteDataLCM(DData);
}




void delay(unsigned int tx) //������ƺ��ٶȲ�����غ���,��ʱ�ӳ���
{
	unsigned int x=tx;
	do
		x--;
	while(x>1);
}


void pwmkey(void) //������ƺ���
{
    if(key==0)
      {
			delay(200);  //������
			if(key==0)
			  {
              last++;
           }
         if(last>CIRCLE)
           last=1;
         while(!key);//�ȴ������ͷ�
       }
}



void Dir_key(void) //���Ƶ��ת��������
{
    if(dir==0)
      {
			delay(200);  //������
			if(dir==0)
			  {
              flag=~flag;
           }
         while(!key);//�ȴ������ͷ�
       }
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
   Dis[8]=speed/100+0x30; //�ٶȰ�λֵ��ʾ
   if(Dis[8]==0x30) Dis[8]=0x20;//�����λΪ0������ʾΪ�ո�
   speed=speed%100;
   Dis[9]=speed/10+0x30;  //�ٶ�ʮλֵ��ʾ
   Dis[10]=speed%10+0x30; //�ٶȸ�λֵ��ʾ
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
}


void main(void)   //������
{
   uchar i;
   INT_Init();
   LCMInit();
   while(1)
     {
        pwmkey();
        Dir_key();
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
        for(i=0;i<0x10;i++)
           {
              DisplayOneChar(i,0,Dis[i]);
           }
     }
}