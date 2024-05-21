/*************************************************************/
/************** 25 ONE-WIRE总线搜素算法测温实验 **************/
/*************************************************************/
/************************* 作者：XHCH ************************/
/*************************************************************/
/******************* 修改日期：2012年2月3日 ******************/
/*************************************************************/



//程序一：读序列号，并用1602显示，1602从左到右分别是低到高位。
#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define Data P0
sbit DQ=P1^3;//ds18b20与单片机连接口
sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;
unsigned char code str1[]={"              "};
unsigned char code str2[]={"              "};
uchar fCode[8];


/*************************lcd1602程序**************************/
void delay1ms(unsigned int ms)//延时1毫秒（不够精确的）
{unsigned int i,j;
   for(i=0;i<ms;i++)
    for(j=0;j<100;j++);
}

void wr_com(unsigned char com)//写指令//
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

void wr_dat(unsigned char dat)//写数据//
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

void lcd_init()//初始化设置//
{delay1ms(15);
  wr_com(0x38);delay1ms(5);
  wr_com(0x08);delay1ms(5);
  wr_com(0x01);delay1ms(5);
  wr_com(0x06);delay1ms(5);
  wr_com(0x0c);delay1ms(5);
}
void display(unsigned char *p)//显示//
{
while(*p!='\0')
{
wr_dat(*p);
p++;
delay1ms(1);
}
}

void init_play()//初始化显示
{ lcd_init();
    wr_com(0x80);
    display(str1);
    wr_com(0xc0);
    display(str2);
   }

/******************************ds1820 *********************/
void delay_18B20(unsigned int i)//延时1微秒
{
   while(i--);
}

void ds1820rst()/*ds1820复位*/
{ uchar x=0;
DQ = 1;          //DQ复位
delay_18B20(4); //延时
DQ = 0;          //DQ拉低
delay_18B20(100); //精确延时大于480us
DQ = 1;          //拉高
delay_18B20(40); 
   } 

uchar ds1820rd()/*读数据*/
{ uchar i=0;
uchar dat = 0;
for (i=8;i>0;i--)
{   DQ = 0; //给脉冲信号
    dat>>=1;
    DQ = 1; //给脉冲信号
    if(DQ)
    dat|=0x80;
    delay_18B20(10);
}
   return(dat);
}
void ds1820wr(uchar wdata)/*写数据*/
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
    temp = fCode[i]>>4; //显示高四位
   if (temp<10) 
    wr_dat(temp + 0x30);
  else
    wr_dat(temp + 0x37);
  temp = fCode[i]&0x0f;//显示低四位
  if (temp<10) 
    wr_dat(temp+ 0x30);
  else
    wr_dat(temp + 0x37);
  }
}

/********************主程序***********************************/
void main()
{ 
	init_play();//初始化显示
	DispCode();	  //系列号显示
	delay1ms(1000);

   while(1);
}

