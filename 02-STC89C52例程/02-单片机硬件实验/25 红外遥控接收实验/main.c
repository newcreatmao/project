/***************************************************************************
ʵ�����ƣ� �������ʵ��

ʵ��ģ��:  51��Ƭ�����İ塢���⴫������Һ����ʾ����1602��

ʵ����ߣ�  51��Ƭ�����İ�------���⴫����
					P3.2 --------- RXD				
					
			51��Ƭ�����İ�------Һ����ʾ����1602�ַ�Һ����
					P2.0 --------- RS
					P2.1 --------- RW
					P2.2 --------- E
			   P0.0~P0.7 --------- BD0~BD7		
						
����������	���º���ң������1602Һ������ʾ���յ��ĺ��������ź�

����ʱ�䣺	2017.10.17
***************************************************************************/

#include <reg52.h>		  
#define uchar unsigned char
#define uint  unsigned int

sbit IRIN = P3^2;    //���������������

uchar IRCOM[7];

sbit  LCM_RS = P2^0; //��������
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80    //���ڼ��LCM״̬���е�Busy��ʶ

uchar code  cdis1[ ] = {" REMOTE CONTROL "};
uchar code  cdis2[ ] = {"  IR-CODE: --H  "};


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


//x*0.14MS��ʱ
void delay(unsigned char x)
{
   unsigned char i;
   while(x--)
     {
        for (i = 0; i<13; i++) {}
     }
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
    X &= 0xF;         		//����X���ܴ���15��Y���ܴ���1
    if (Y) X |= 0x40; 		//��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
    X |= 0x80;        		//���ָ����
    WriteCommandLCM(X, 0); 	//���ﲻ���æ�źţ����͵�ַ��
    WriteDataLCM(DData);
}


main()
{
    uchar m;
  
    IE = 0x81;                //�������ж��ж�,ʹ�� INT0 �ⲿ�ж�
    TCON = 0x01;              //������ʽΪ���帺���ش���
    
    IRIN=1;                   //I/O�ڳ�ʼ��
	
    Delay5Ms();               //��ʱ
    LCMInit();                //��ʼ��LCD             
        
     m = 0;
    while(cdis1[m] != '\0')
     {                         //��ʾ�ַ�
       DisplayOneChar(m,0,cdis1[m]);
       m++;
     }

     m = 0;
    while(cdis2[m] != '\0')
     {
       DisplayOneChar(m,1,cdis2[m]);      //��ʾ�ַ�
       m++;
     }

   while(1)	;

}


//ң�ؼ�ֵ��ȡ�ʹ�����

void IR_IN() interrupt 0 using 0
{
    unsigned char j,k,N=0;
    EX0 = 0;   
	 delay(15);
	 if (IRIN==1)           //ȷ��IR�źų���
       { 
          EX0 =1;
	       return;
	    } 
                           
     while (!IRIN)         //��IR��Ϊ�ߵ�ƽ������9ms��ǰ���͵�ƽ�źš�
       {
           delay(1);
       }

     for (j=0;j<4;j++)  //�ռ���������
       { 
           for (k=0;k<8;k++)		//ÿ��������8λ
               {
                   while (IRIN)		//�� IR ��Ϊ�͵�ƽ������4.5ms��ǰ���ߵ�ƽ�źš�
                       {
                           delay(1);
                       }
                   while (!IRIN)	//�� IR ��Ϊ�ߵ�ƽ
                       {
                           delay(1);
                       }
                   while (IRIN) 	//����IR�ߵ�ƽʱ��
                       {
                           delay(1);
                           N++;           
                           if (N>=30)
	                            { 
                                  EX0=1;
	                               return; //0.14ms���������Զ��뿪��
                               } 
                       }                  //�ߵ�ƽ�������                
                   IRCOM[j]=IRCOM[j] >> 1;//�������λ����0
                   if (N>=8) 
                       {
                           IRCOM[j] = IRCOM[j] | 0x80;//�������λ����1��
                       }  
                   N=0;
               }//end for k
       }//end for j
   
   if (IRCOM[2]!=~IRCOM[3])
       { 
           EX0=1;
           return; 
       }

   IRCOM[5]=IRCOM[2]&0x0F;     //ȡ����ĵ���λ
   IRCOM[6]=IRCOM[2]>>4;       //����4�Σ�����λ��Ϊ����λ

   if(IRCOM[5]>9)
       {
           IRCOM[5]=IRCOM[5]+0x37;
       }
   else
	    IRCOM[5]=IRCOM[5]+0x30;

   if(IRCOM[6]>9)
       {
           IRCOM[6]=IRCOM[6]+0x37;
       }
   else
	    IRCOM[6]=IRCOM[6]+0x30;

       DisplayOneChar(0x0b,1,IRCOM[6]);        //��һλ����ʾ
       DisplayOneChar(0x0c,1,IRCOM[5]);        //�ڶ�λ����ʾ

       EX0 = 1; 
} 
