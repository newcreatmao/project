///***************************************************************************
//ʵ�����ƣ� ����ADת��ʵ��

//ʵ��ģ��:  51��Ƭ�����İ塢LEDʾ��������A/Dת����

//ʵ����ߣ�  51��Ƭ�����İ�------����A/Dת����
//					 P0   ---------  J36
//					 P2.0 --------- START
//					 P2.1 ---------	EOC  
//					 P2.2 --------- OE 
//					 P2.3 --------- ALE
//					 
//			51��Ƭ�����İ�------LEDʾ��
//					 P1  ---------  J4	
//						
//����������	ת�����ֱ���Զ�������ʽ��LED����ʾ���ɵ��ڵ�λ���ı������ģ����

//����ʱ�䣺  2017.10.17
//***************************************************************************/

//#include <reg52.H>

//sbit START = P2^0;
//sbit EOC = P2^1;
//sbit OE  = P2^2;
//sbit CLK = P2^3;
//unsigned char getdata;

///************************************************/
////��ʱ����ʼ��
//void init()
//{
//        TMOD= 0x03;// ��ʱ��0������ʽ3
//        TH0 = 0xff;// ��ʱ��0����ֵ
//        TL0 = 0x00;
//        TR0 = 1;
//        ET0 = 1;
//        EA  = 1;
//}

///***********************************************/
////�����ʱ����ADC0809��ʱ��
//void clk() interrupt 1
//{ 
//        CLK=(~CLK);
//}


///************************************************/
////ADת������
//unsigned char ADC()
//    {
//         char value;
//		 START=0; 
//		 START=1;      //��ʼת������
//		 START=0;
//		 while(EOC==0);//�ȴ�ת������
//		 OE=1;
//		 value=P0;
//		 OE=0;
//         return value;
//     }


///************************************************/
//void main()
//{
//    init();
//    START = 1;       // ST�˲���������
//    START = 0;
//    while(1)
//	{
//		P1=~ADC();//���ת���õ�������
//	}
//}


#include <REGX51.H>

sbit START = P2^0;
sbit EOC = P2^1;
sbit OE  = P2^2;
sbit CLK = P2^3;
unsigned int getdata;
int u,t=0,mod,k=0;
unsigned char locate[]={0,0,0};
sbit add_a = P1^0;
sbit add_b = P1^1;
sbit add_c = P1^2;

unsigned char digivalue[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7f,0x6f};
unsigned char digorder[]={0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFf,0xCf};
unsigned char locate[3];
/************************************************/


//��ʱ����ʼ��
void init()
{
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
  TMOD |= 0x03;// ��ʱ��0������ʽ3
  TH0 = 0xff;// ��ʱ��0����ֵ
  TL0 = 0x00;
  TR0 = 1;
  ET0 = 1;
	PT0 = 1;
}

void Timer1_Init(void)		//1����@12.000MHz
{
	TMOD &= 0x0F;			//���ö�ʱ��ģʽ
	TMOD |= 0x10;			//���ö�ʱ��ģʽ
	TL1 = 0x20;				//���ö�ʱ��ʼֵ
	TH1 = 0xD1;				//���ö�ʱ��ʼֵ
	TF1 = 1;				//���TF1��־
	TR1 = 1;				//��ʱ��1��ʼ��ʱ
	ET1 = 1;
}

/***********************************************/
//�����ʱ����ADC0809��ʱ��
void clk() interrupt 1
{ 
      CLK=(~CLK);
}


/************************************************/
//ADת������
void ADC(int i)
{
		char value;
	
		add_a=i%2;
		i=i/2;
		add_b=i%2;
		i=i/2;
		add_c=i%2;
		
		P1_3 = ~add_a;
	  P1_4 = ~add_b;
		P1_5 = ~add_c;
	
		 START=0;
		 START=1;      //��ʼת������
		 START=0;
		 while(EOC==0){ OE=1;};//�ȴ�ת������
		
		 getdata=P0;
	   value=getdata;
		 getdata=getdata*1.96;
	   if(getdata<=2){
			 mod=1;
		 }
		 else{
			 mod=0;
		 }
		 OE=0;
		 locate[0]=getdata%10;
		 locate[1]=getdata/10%10;
		 locate[2]=getdata/100%10;
}

void use() interrupt 3
{
	TL1 = 0x20;				//���ö�ʱ��ʼֵ
	TH1 = 0xD1;				//���ö�ʱ��ʼֵ
	t++;
	if(t>=10000){
		t=0;
		k++;
		k=k%8;
		ADC(k);
		if(mod==1){
			P1_6=0;
		}
		else if(mod==0){
			P1_6=1;
		}
	}
}

void delay() //�ӳٺ������������������ļ��ʱ��
{ 
	unsigned char ii=200; //�������������˸���������Ｔ��
	while(ii--);
}
/************************************************/
void main()
{
		int i=0;
    init();
	  Timer1_Init();
		EA  = 1;
    START = 1;       // ST�˲���������
    START = 0;
    while(1)
	{
			P2_5=0;P2_6=0;P2_7=1;
			P3=0x00;
			P3=digorder[locate[2]]; 	//��ʾi
		  delay();
			
			P2_5=0;P2_6=1;P2_7=0;
			P3=0x00;
			P3=digivalue[locate[1]]; 	//��ʾi
			delay();
		
			P2_5=1;P2_6=0;P2_7=0;
			P3=0x00;
			P3=digivalue[locate[0]]; 	//��ʾi
			delay();
	}
}


//#include <REGX51.H>

//sbit START = P2^0;
//sbit EOC = P2^1;
//sbit OE  = P2^2;
//sbit CLK = P2^3;
//unsigned int getdata;
//int u,t=0,mod;
//unsigned char locate[]={0,0,0};

//unsigned char digivalue[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7f,0x6f};
//unsigned char digorder[]={0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFf,0xCf};
//unsigned char locate[3];
///************************************************/


//��ʱ����ʼ��
//void init()
//{
//    TMOD &= 0xF0;            //���ö�ʱ��ģʽ
//  TMOD |= 0x03;// ��ʱ��0������ʽ3
//  TH0 = 0xff;// ��ʱ��0����ֵ
//  TL0 = 0x00;
//  TR0 = 1;
//  ET0 = 1;
//    PT0 = 1;
//}

//void Timer1_Init(void)        //1����@12.000MHz
//{
//    TMOD &= 0x0F;            //���ö�ʱ��ģʽ
//    TMOD |= 0x10;            //���ö�ʱ��ģʽ
//    TL1 = 0x20;                //���ö�ʱ��ʼֵ
//    TH1 = 0xD1;                //���ö�ʱ��ʼֵ
//    TF1 = 1;                //���TF1��־
//    TR1 = 1;                //��ʱ��1��ʼ��ʱ
//    ET1 = 1;
//}

///***********************************************/
//�����ʱ����ADC0809��ʱ��
//void clk() interrupt 1
//{ 
//      CLK=(~CLK);
//}


///************************************************/
//ADת������
//unsigned char ADC()
//{
//    char value;
//         START=0; 
//         START=1;      //��ʼת������
//         START=0;
//         while(EOC==0);//�ȴ�ת������
//         OE=1;
//         getdata=P0;
//       value=getdata;
//         if(getdata>=0x40){
//             mod=1;
//         }
//         else{
//             mod=0;
//         }
//         getdata=getdata*1.96;
//         OE=0;
//         locate[0]=getdata%10;
//         locate[1]=getdata/10%10;
//         locate[2]=getdata/100%10;
//     return value;
//}

//void use() interrupt 3
//{
//    char use;
//    TL1 = 0x20;                //���ö�ʱ��ʼֵ
//    TH1 = 0xD1;                //���ö�ʱ��ʼֵ
//    t++;
//    if(t>=10000){
//        t=0;
//        use=ADC();
//        if(mod==1){
//            P1=~use;
//        }
//        else if(mod==0){
//            P1=0xff;
//        }
//    }
//}

//void delay() //�ӳٺ������������������ļ��ʱ��
//{ 
//    unsigned char ii=200; //�������������˸���������Ｔ��
//    while(ii--);
//}
///************************************************/
//void main()
//{
//        int i=0;
//    init();
//      Timer1_Init();
//        EA  = 1;
//    START = 1;       // ST�˲���������
//    START = 0;
//    while(1)
//    {
//            P2_5=0;P2_6=0;P2_7=1;
//            P3=0x00;
//            P3=digorder[locate[2]];     //��ʾi
//          delay();
//            
//            P2_5=0;P2_6=1;P2_7=0;
//            P3=0x00;
//            P3=digivalue[locate[1]];     //��ʾi
//            delay();
//        
//            P2_5=1;P2_6=0;P2_7=0;
//            P3=0x00;
//            P3=digivalue[locate[0]];     //��ʾi
//            delay();
//    }
//}