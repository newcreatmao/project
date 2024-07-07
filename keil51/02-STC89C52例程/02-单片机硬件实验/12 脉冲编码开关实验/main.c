/*************************************************************/
/********************** 12 ������뿪��ʵ�� ******************/
/*************************************************************/
/************************* ���ߣ�XHCH ************************/
/*************************************************************/
/******************* �޸����ڣ�2012��2��2�� ******************/
/*************************************************************/
/***************************************************************************
ʵ�����ƣ� ������뿪��ʵ��

ʵ��ģ��:  51��Ƭ�����İ塢Һ����ʾ���������������

ʵ����ߣ�  51��Ƭ�����İ�------�����������
					P3.2---------B
					P3.3---------A
					P3.4---------D
					
			51��Ƭ�����İ�------Һ����ʾ����1602�ַ�Һ����
					P2.0---------RS
					P2.1---------RW
					P2.2---------E
			   P0.0~P0.7---------BD0~BD7	
						
����������	1.���������������LCD1602��ʾ��You Pressed it����
			2.˳ʱ��ת�������������1602��ʾ�ı������ӣ���֮����С��

����ʱ�䣺2017.10.17
***************************************************************************/
#include "reg52.h"       
#include "intrins.h"     	//_nop_();��ʱ������

sbit  LCM_RS = P2^0; 		//��������
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

sbit  Pulse_coder_A = P3^3;
sbit  Pulse_coder_B = P3^2;
sbit  Pulse_coder_D = P3^4;

#define LCM_Data P0
#define Busy 0x80 //���ڼ��LCM״̬���е�Busy��ʶ

unsigned char DisP[]="You Pressed it!";       //�趨��ʾ�ַ�
unsigned char Now_Num[]="Now the Uum:    ";   //���ڵ�ֵ

unsigned char i,temp;
unsigned char num=0x80;

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
/*******************LCM1602��غ���************************/
/**********************************************************/
//��״̬
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

/**********************************************************/
//5ms��ʱ
void Delay5Ms(void)
{
    unsigned int TempCyc = 5552;
    while(TempCyc--);
}

/**********************************************************/
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

/**********************************************************/
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

/**********************************************************/
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

/**********************************************************/
//LCD����ָ��λ�ó���
void LCM_pos(char position)
{						
	WriteCommandLCM(position|0x80);	//����ָ��=80+��ַ��(00H~27H,40H~67H)
}

/**********************************************************/
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

/**********************************************************/
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

/**********************************************************/
//�ж����ó�ʼ��
void Int_Init(void)
{
    TCON=0x01;//�趨�ⲿ�ж�0Ϊ���ش�����ʽ
    EX0=1;    //�����ⲿ�ж�0
    PX0=1;    //�����ⲿ�ж�0Ϊ�����ȼ�
    EA=1;     //�����ж�
}

/**********************************************************/
main()
{
    LCMInit();    //LCM��ʼ��
    Int_Init();   //ϵͳ��ʼ��
    while(1)
       {
           if(!Pulse_coder_D)
              {
              for(i=0;i<0x0F;i++)
                 {
                     DisplayOneChar(i,0,DisP[i]);
                 }
              }
           delay1ms(100);
       }
}

/**********************************************************/
//�ⲿ�ж�0�жϷ����ӳ���
void Out_interrupt0 (void) interrupt 0
{
   EA=0;     //�����ж�
   _nop_();_nop_();_nop_();_nop_();_nop_();
   _nop_();_nop_();_nop_();_nop_();_nop_();//΢����ʱ
   if(Pulse_coder_B==Pulse_coder_A)
      {
         if(num==0xFF)
         {
            num=0xFF;
         }
         else
         {
            num=num+1;
         }
         temp=num/16;
         if(temp>9)               //ת��ΪASCII��
            temp= temp+0x37;
         else
	         temp=temp+0x30;
         Now_Num[12]=temp;
         temp=num%16;
         if(temp>9)               //ת��ΪASCII��
            temp= temp+0x37;
         else
	         temp=temp+0x30;
         Now_Num[13]=temp;
      }
   else if(Pulse_coder_B==(~Pulse_coder_A))
      {
         if(num==0x00)
         {
            num=0x00;
         }
         else
         {
            num=num-1;
         }
            temp=num/16;
         if(temp>9)               //ת��ΪASCII��
            temp= temp+0x37;
         else
	         temp=temp+0x30;
         Now_Num[12]=temp;
         temp=num%16;
         if(temp>9)               //ת��ΪASCII��
            temp= temp+0x37;
         else
	         temp=temp+0x30;
         Now_Num[13]=temp;
      }
   for(i=0;i<0x10;i++)
       {
          DisplayOneChar(i,0,Now_Num[i]);
       }
   EA=1;     //�����ж�
}