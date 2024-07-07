/***************************************************************************
ʵ�����ƣ� PS2���̶�ȡʵ��

ʵ��ģ��:  51��Ƭ�����İ塢Һ����ʾ���������̽ӿ�

ʵ����ߣ� 51��Ƭ�����İ�------�����̽ӿ�
				P3.2--------------SDA
				P3.3--------------SLK
				
			51��Ƭ�����İ�------Һ����ʾ��
				 P3.0--------------RS
				 P3.1--------------RW
				 P3.2--------------E
			P0.0~P0.7--------------DB0~DB7
						
�������������¼��̵İ�����1602������ʾ���µİ����ļ�ֵ

����ʱ�䣺2017.10.17
***************************************************************************/

#include <Reg52.h>	
#include <stdio.h>

sbit  LCM_RS = P2^0; //��������
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80    //���ڼ��LCM״̬���е�Busy��ʶ

sbit Key_Data =P3^2; //����Keyboard����
sbit Key_CLK=  P3^3;

unsigned char code Welcome[] = {"PC_KEYboard_test"};
unsigned char code Tips[] = {"Press__any__key."};
unsigned char code Cls[] = {" "};
static unsigned char IntNum = 0; //�жϴ�������
static unsigned char KeyV;       //��ֵ
static unsigned char DisNum = 0; //��ʾ��ָ��
static unsigned char Key_UP=0, Shift = 0;//Key_UP�Ǽ��ɿ���ʶ��Shift��Shift�����±�ʶ
static unsigned char BF = 0;     //��ʶ�Ƿ����ַ����յ�

unsigned char code UnShifted[59][2] = {
0x1C, 'a',
0x32, 'b',
0x21, 'c',
0x23, 'd',
0x24, 'e',
0x2B, 'f',
0x34, 'g',
0x33, 'h',
0x43, 'i',
0x3B, 'j',
0x42, 'k',
0x4B, 'l',
0x3A, 'm',
0x31, 'n',
0x44, 'o',
0x4D, 'p',
0x15, 'q',
0x2D, 'r',
0x1B, 's',
0x2C, 't',
0x3C, 'u',
0x2A, 'v',
0x1D, 'w',
0x22, 'x',
0x35, 'y',
0x1A, 'z',
0x45, '0',
0x16, '1',
0x1E, '2',
0x26, '3',
0x25, '4',
0x2E, '5',
0x36, '6',
0x3D, '7',
0x3E, '8',
0x46, '9',
0x0E, '`',
0x4E, '-',
0x55, '=',
0x5D, '\\',
0x29, ' ',
0x54, '[',
0x5B, ']',
0x4C, ';',
0x52, '\'',
0x41, ',',
0x49, '.',
0x4A, '/',
0x71, '.',
0x70, '0',
0x69, '1',
0x72, '2',
0x7A, '3',
0x6B, '4',
0x73, '5',
0x74, '6',
0x6C, '7',
0x75, '8',
0x7D, '9',
};

unsigned char code Shifted[59][2] = {
0x1C, 'A',
0x32, 'B',
0x21, 'C',
0x23, 'D',
0x24, 'E',
0x2B, 'F',
0x34, 'G',
0x33, 'H',
0x43, 'I',
0x3B, 'J',
0x42, 'K',
0x4B, 'L',
0x3A, 'M',
0x31, 'N',
0x44, 'O',
0x4D, 'P',
0x15, 'Q',
0x2D, 'R',
0x1B, 'S',
0x2C, 'T',
0x3C, 'U',
0x2A, 'V',
0x1D, 'W',
0x22, 'X',
0x35, 'Y',
0x1A, 'Z',
0x45, '0',
0x16, '1',
0x1E, '2',
0x26, '3',
0x25, '4',
0x2E, '5',
0x36, '6',
0x3D, '7',
0x3E, '8',
0x46, '9',
0x0E, '~',
0x4E, '_',
0x55, '+',
0x5D, '|',
0x29, ' ',
0x54, '{',
0x5B, '}',
0x4C, ':',
0x52, '"',
0x41, '<',
0x49, '>',
0x4A, '?',
0x71, '.',
0x70, '0',
0x69, '1',
0x72, '2',
0x7A, '3',
0x6B, '4',
0x73, '5',
0x74, '6',
0x6C, '7',
0x75, '8',
0x7D, '9',
};

/**********************************************************/
/*******************LCM1602��غ���************************/
/**********************************************************/
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

/**********************************************************/
//��ָ��λ����ʾһ���ַ�
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

/**********************************************************/

void Keyboard_out(void) interrupt 2
{
    if ((IntNum > 0) && (IntNum < 9))
        { 
            KeyV = KeyV >> 1; //����������ǵ�>>�ߣ������һ����������һλ
            if (Key_Data) KeyV = KeyV | 0x80; //������������Ϊ1ʱΪ1�����λ
        }
    IntNum++;
    while (!Key_CLK); //�ȴ�PS/2CLK����

    if (IntNum > 10)
        {
            IntNum = 0; //���ж�11�κ��ʾһ֡�������꣬�����׼����һ�ν���
            BF = 1; //��ʶ���ַ���������
            EA = 0; //���жϵ���ʾ����ٿ��ж� (ע�������ﲻ��BF�͹��ж�ֱ�ӵ�Decode()����Decode�������õ����к���Ҫ����Ϊ���뺯��)
        }
}

void Decode(unsigned char ScanCode) //ע��:��SHIFT+GΪ12H 34H F0H 34H F0H 12H��Ҳ����˵shift��ͨ��+G��ͨ��+shift�Ķ���+G�Ķ���
{
    unsigned char TempCyc; 

    if (!Key_UP) //�������ɿ�ʱ
        {
            switch (ScanCode)
                {
                    case 0xF0 : // ���յ�0xF0��Key_UP��1��ʾ���뿪ʼ
                            Key_UP = 1;
                            break;

                    case 0x12 : // �� SHIFT
                            Shift = 1;
                            break;

                    case 0x59 : // �� SHIFT
                            Shift = 1;
                            break;

                    default: 
                    if (DisNum > 15)
                        {
                            DisplayListChar(0, 1, Cls);//��LCD�ڶ���
                            DisNum = 0; 
                        }
                    if(!Shift) //���SHIFTû����
                        {
                            for (TempCyc = 0;(UnShifted[TempCyc][0]!=ScanCode)&&(TempCyc<59); TempCyc++); //�����ʾ
                            if (UnShifted[TempCyc][0] == ScanCode) DisplayOneChar(DisNum, 1, UnShifted[TempCyc][1]);
                            DisNum++;
                        } 
                    else //����SHIFT
                        {
                            for(TempCyc = 0; (Shifted[TempCyc][0]!=ScanCode)&&(TempCyc<59); TempCyc++); //�����ʾ
                            if (Shifted[TempCyc][0] == ScanCode) DisplayOneChar(DisNum, 1, Shifted[TempCyc][1]);
                            DisNum++;
                        }

                    break;
                }
        }
        else
            { 
                Key_UP = 0;
                switch (ScanCode) //�����ɿ�ʱ���������룬��G 34H F0H 34H ��ô�ڶ���34H���ᱻ����
                    {
                        case 0x12 : // �� SHIFT
                            Shift = 0;
                            break;

                        case 0x59 : // �� SHIFT
                            Shift = 0;
                            break;
                    }
            }
        BF = 0; //��ʶ�ַ���������
}

void main(void)
{
    unsigned char TempCyc;

    LCMInit(); //LCM��ʼ�� 
    DisplayListChar(0, 0, Welcome);
    DisplayListChar(0, 1, Tips);
    ReadDataLCM();//�����þ�������
    for (TempCyc=0; TempCyc<10; TempCyc++)
    Delay5Ms(); //��ʱ
    DisplayListChar(0, 1, Cls); 

    IT1 = 0; //���ⲿ�ж�1Ϊ�͵�ƽ����
    EA = 1;
    EX1 = 1; //���ж�

    while(1)
        {
            if (BF)
            Decode(KeyV);
            else
            EA = 1; //���ж�
        }
} 
