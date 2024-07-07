////////////////////////////////////////////////////////////////////////////
//[ע:AT89S52ʹ��11.0592M����]
////////////////////////////////////////////////////////////////////////////
#include <reg52.h>

sbit  LCM_RS = P2^0; //��������
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80 //���ڼ��LCM״̬���е�Busy��ʶ

void WriteDataLCM(unsigned char WDLCM);
void WriteCommandLCM(unsigned char WCLCM,BuysC);
unsigned char ReadDataLCM(void);
unsigned char ReadStatusLCM(void);
void LCMInit(void);
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData);
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData);
void Delay5Ms(void);

////////////////////////////////////////////////////////////////////////////
//д����
////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////
//дָ��
////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////
//������
////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////
//��״̬
////////////////////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////////////////
//LCD����ָ��λ�ó���
////////////////////////////////////////////////////////////////////////////
void LCM_pos(char position)
{						
	WriteCommandLCM(position|0x80);	//����ָ��=80+��ַ��(00H~27H,40H~67H)
}

void LCMInit(void) //LCM��ʼ��
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
WriteCommandLCM(0x06,1); // ��ʾ����ƶ�����
WriteCommandLCM(0x0C,1); // ��ʾ�����������
}

////////////////////////////////////////////////////////////////////////////
//��ָ��λ����ʾһ���ַ�
////////////////////////////////////////////////////////////////////////////
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
Y &= 0x1;
X &= 0xF; //����X���ܴ���15��Y���ܴ���1
if (Y) X |= 0x40; //��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
X |= 0x80; //���ָ����
WriteCommandLCM(X, 0); //���ﲻ���æ�źţ����͵�ַ��
WriteDataLCM(DData);
}

////////////////////////////////////////////////////////////////////////////
//��ָ��λ����ʾһ���ַ�
////////////////////////////////////////////////////////////////////////////
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData)
{
unsigned char ListLength;

ListLength = 0;
Y &= 0x1;
X &= 0xF; //����X���ܴ���15��Y���ܴ���1
while (DData[ListLength]>0x20) //�������ִ�β���˳�
{
if (X <= 0xF) //X����ӦС��0xF
{
DisplayOneChar(X, Y, DData[ListLength]); //��ʾ�����ַ�
ListLength++;
X++;
}
}
}

////////////////////////////////////////////////////////////////////////////
//5ms��ʱ
////////////////////////////////////////////////////////////////////////////
void Delay5Ms(void)
{
unsigned int TempCyc = 5552;
while(TempCyc--);
}


