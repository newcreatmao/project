/***********************************************************************************************************/
//���ߣ�ģ��TRIG�� P2.1  ECH0 ��P2.0	 VCC��VCC��5V����GND��GND
//����ܣ�������
//�������ʾ������루���ף�
//ע�����������
/***********************************************************************************************************/	    
#include <AT89x51.H>		//���������ļ�
#include <intrins.h>
#define  RX  P2_0
#define  TX  P2_1
sbit DU  = P2^6;   //����ܶ�ѡ
sbit WE  = P2^7;   //�����λѡ
unsigned int  time=0;
unsigned int  timer=0;
unsigned char posit=0;
unsigned long S=0;
bit      flag =0;
unsigned char const discode[] ={ 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F,0x6F,0x40,0x00/*-*/};
unsigned char const positon[4]={ 0xfe,0xfd,0xfb,0xf7};
unsigned char disbuff[4]	   ={ 0,0,0,0,};
/********************************************************/
    void Display(void)				 //ɨ�������
	{
	DU = 0;	
	 if(posit==0)
	 {P0=(discode[disbuff[posit]]);}
	 else
	 {P0=discode[disbuff[posit]];}
	 DU = 1;
	 DU = 0;
	 WE = 0;
	  P0=positon[posit];
	  WE=1;
	  WE=0;
	  if(++posit>=4)
	  posit=0;
	}
/********************************************************/
    void Conut(void)
	{
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	
	 S=(float)(time*1.085)*0.17;     //�������MM
	 if((S>=7000)||flag==1) //����������Χ��ʾ��-��
	 {	 
	  flag=0;
	  disbuff[0]=10;	   //��-��
	  disbuff[1]=10;	   //��-��
	  disbuff[2]=10;	   //��-��
	  disbuff[3]=10;	   //��-��
	 }
	 else
	 {
	  disbuff[0]=S/1000;
	  disbuff[1]=S%1000/100;
	  disbuff[2]=S%100/10;
	  disbuff[3]=S%10;
	 }
	}
/********************************************************/
     void zd0() interrupt 1 		 //T0�ж��������������,������෶Χ
  {
    flag=1;							 //�ж������־
  }
/********************************************************/
   void  zd3()  interrupt 3 		 //T1�ж�����ɨ������ܺͼ�800MS����ģ��
  {
	 TH1=0xf8;
	 TL1=0x30;
	 Display();
	 timer++;
	 if(timer>=400)
	 {
	  timer=0;
	  TX=1;			                //800MS  ����һ��ģ��
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  TX=0;
	 } 
  }
/*********************************************************/

	void  main(  void  )

  {  
    TMOD=0x11;		   //��T0,T1Ϊ��ʽ1��ʱģʽ��GATE=1��
	TH0=0;
	TL0=0;          
	TH1=0xf8;		   //2MS��ʱ
	TL1=0x30;
	ET0=1;             //����T0�ж�
	ET1=1;			   //����T1�ж�
	TR1=1;			   //������ʱ��1
	EA=1;			   //�������ж�

	while(1)
	{
	 while(!RX);		//��RX��ECHO�źŻ��죩Ϊ��ʱ�ȴ�
	 TR0=1;			    //��������
	 while(RX);			//��RXΪ1�������ȴ�
	 TR0=0;				//�رռ���
     Conut();			//����
	}

  }
                