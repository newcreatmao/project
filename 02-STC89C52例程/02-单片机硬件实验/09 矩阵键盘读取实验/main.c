/*************************************************************/
/********************* 24 ������̶�ȡʵ�� *******************/
/*************************************************************/
/************************* ���ߣ�XHCH ************************/
/*************************************************************/
/******************* �޸����ڣ�2012��2��3�� ******************/
/*************************************************************/
/***************************************************************************
ʵ�����ƣ� ������̶�ȡʵ��

ʵ��ģ��:  51��Ƭ�����İ塢�����������Һ����ʾ����1602��

ʵ����ߣ�  51��Ƭ�����İ�------���������
				P1.0~P1.3 --------- ROW1~ROW4
				P1.4~P1.7 --------- LINE1~LINE4				
					
			51��Ƭ�����İ�------Һ����ʾ����1602�ַ�Һ����
					P2.0 --------- RS
					P2.1 --------- RW
					P2.2 --------- E
			   P0.0~P0.7 --------- BD0~BD7		
						
����������	1602Һ����������ʾ������λ�룬������ʾ��������ʾ���ַ�

����ʱ�䣺	2017.10.17
***************************************************************************/

#include <reg52.h>               

unsigned char  dis_buf;       //��ʾ����
unsigned char  temp;
unsigned char  key=0;         //��˳����

sbit  LCM_RS = P2^0; 		  //��������
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80 //���ڼ��LCM״̬���е�Busy��ʶ

unsigned char code  cdis1[ ] = {"KEY NUMBER:   H "};
unsigned char code  cdis2[ ] = {"  KEY-CODE:   H "};
unsigned char Code[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};

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
    X &= 0xF;         		//����X���ܴ���15��Y���ܴ���1
    if (Y) X |= 0x40; 		//��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
    X |= 0x80;        		//���ָ����
    WriteCommandLCM(X, 0);  //���ﲻ���æ�źţ����͵�ַ��
    WriteDataLCM(DData);
}

/**********************************************************/
// ��ɨ���ӳ���
void  keyscan(void)
 { 
    P1=0xF0;                //����Ϊ���룬����Ϊ����������������ȫΪ0
	 temp=P1;               //��P1��       
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
	 temp=P1;                //��P1�� 
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
    	
     dis_buf = key;	             //��ֵ����ʾ����
     dis_buf = dis_buf&0x0f;

	 if(dis_buf>9)               //ת��ΪASCII��
      dis_buf = dis_buf+0x37;
    else
	   dis_buf = dis_buf+0x30;
 }

/*************************************************************/
//�жϼ��Ƿ���
void  keydown(void)
 {  
  	P1=0xF0;
   Delay5Ms();
	if(P1!=0xF0)
	{
	  keyscan();
    }
 }

/*************************************************************/
// ������
main()
 {
    unsigned char m;
    P0=0xFF;                    //��P0��
    P2=0xFF;                    //��P2��  
    Delay5Ms();                 //��ʱ
    LCMInit();                  //��ʼ��LCD             
        
     m = 0;
    while(cdis1[m] != '\0')
     {                         //��ʾ�ַ�
       DisplayOneChar(m,0,cdis1[m]);
       m++;
     }

     m = 0;
    while(cdis2[m] != '\0')
     {
       DisplayOneChar(m,1,cdis2[m]);  //��ʾ�ַ�
       m++;
     }       
	  dis_buf = 0x2d;          		  //��ʾ�ַ�"-"

    while(1)
    { 
       keydown();
       DisplayOneChar(0x0c,0,dis_buf);    //��ʾ����ֵ
       DisplayOneChar(0x0c,1,Code[key]);  //��ʾ��������
    }
  }   

/************************************************************/  