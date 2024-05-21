/*************************************************************/
/************** 25 ONE-WIRE���������㷨����ʵ�� **************/
/*************************************************************/
/************************* ���ߣ�XHCH ************************/
/*************************************************************/
/******************* �޸����ڣ�2012��2��3�� ******************/
/*************************************************************/



//����һ�������кţ�����1602��ʾ��1602�����ҷֱ��ǵ͵���λ��
#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define Data P0
sbit DQ=P1^3;//ds18b20�뵥Ƭ�����ӿ�
sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;
unsigned char code str1[]={"              "};
unsigned char code str2[]={"              "};
uchar fCode[8];


/*************************lcd1602����**************************/
void delay1ms(unsigned int ms)//��ʱ1���루������ȷ�ģ�
{unsigned int i,j;
   for(i=0;i<ms;i++)
    for(j=0;j<100;j++);
}

void wr_com(unsigned char com)//дָ��//
{ delay1ms(1);
   RS=0;
   RW=0;
   EN=0;
   Data=com;
   delay1ms(1);
   EN=1;
   delay1ms(1);
   EN=0;
}

void wr_dat(unsigned char dat)//д����//
{ delay1ms(1);;
   RS=1;
   RW=0;
   EN=0;
   Data=dat;
   delay1ms(1);
   EN=1;
   delay1ms(1);
   EN=0;
}

void lcd_init()//��ʼ������//
{delay1ms(15);
  wr_com(0x38);delay1ms(5);
  wr_com(0x08);delay1ms(5);
  wr_com(0x01);delay1ms(5);
  wr_com(0x06);delay1ms(5);
  wr_com(0x0c);delay1ms(5);
}
void display(unsigned char *p)//��ʾ//
{
while(*p!='\0')
{
wr_dat(*p);
p++;
delay1ms(1);
}
}

void init_play()//��ʼ����ʾ
{ lcd_init();
    wr_com(0x80);
    display(str1);
    wr_com(0xc0);
    display(str2);
   }

/******************************ds1820 *********************/
void delay_18B20(unsigned int i)//��ʱ1΢��
{
   while(i--);
}

void ds1820rst()/*ds1820��λ*/
{ uchar x=0;
DQ = 1;          //DQ��λ
delay_18B20(4); //��ʱ
DQ = 0;          //DQ����
delay_18B20(100); //��ȷ��ʱ����480us
DQ = 1;          //����
delay_18B20(40); 
   } 

uchar ds1820rd()/*������*/
{ uchar i=0;
uchar dat = 0;
for (i=8;i>0;i--)
{   DQ = 0; //�������ź�
    dat>>=1;
    DQ = 1; //�������ź�
    if(DQ)
    dat|=0x80;
    delay_18B20(10);
}
   return(dat);
}
void ds1820wr(uchar wdata)/*д����*/
{uchar i=0;
    for (i=8; i>0; i--)
   { DQ = 0;
     DQ = wdata&0x01;
     delay_18B20(10);
     DQ = 1;
     wdata>>=1;
   }
}




void DispCode()
{
 unsigned char i,temp;

  ds1820rst();
  ds1820wr(0x33);
   for (i=0;i<8;i++)
 {
  fCode[i]=ds1820rd();
 }
 wr_com(0x80+0x40); 
 for (i=0;i<8;i++)
  {
    temp = fCode[i]>>4; //��ʾ����λ
   if (temp<10) 
    wr_dat(temp + 0x30);
  else
    wr_dat(temp + 0x37);
  temp = fCode[i]&0x0f;//��ʾ����λ
  if (temp<10) 
    wr_dat(temp+ 0x30);
  else
    wr_dat(temp + 0x37);
  }
}

/********************������***********************************/
void main()
{ 
	init_play();//��ʼ����ʾ
	DispCode();	  //ϵ�к���ʾ
	delay1ms(1000);

   while(1);
}

