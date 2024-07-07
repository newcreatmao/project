/***************************************************************************
实验名称： ONE-WINE总线测温实验

实验模块:  51单片机核心板、温度传感区、液晶显示区

实验接线：  51单片机核心板------温度传感区
					P1.3 --------- 1WIRE
										
			51单片机核心板------液晶显示区（1602字符液晶）
					P1.0 --------- RS
					P1.1 --------- RW
					P1.2 --------- E
			   P0.0~P0.7 --------- BD0~BD7		
						
现象描述：	读出环境的温度

更新时间：	2017.10.17
***************************************************************************/

//程序二：匹配序列号，并读温度。
#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int
#define Data P0
sbit DQ=P1^3;//ds18b20与单片机连接口
sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;	
uchar code str1[]={0x28,0x40,0xAD,0x82,0x03,0x00,0x00,0x8E};	//ROM1
uchar code str2[]={0x28,0x65,0xA5,0x82,0x03,0x00,0x00,0xED};	//ROM2 
uchar code table[8]={0x0c,0x12,0x12,0x0c,0x00,0x00,0x00,0x00};	// 摄氏温度符号
uchar data disdata[5];
uint tvalue;//温度值
uchar tflag;//温度正负标志

/*************************lcd1602程序**************************/
void delay1ms(uint ms)//延时1毫秒（不够精确的）
{  
	uint i,j;
	for(i=0;i<ms;i++)
	for(j=0;j<100;j++);
}

void wr_com(uchar com)//写指令//
{ 
	delay1ms(1);
	RS=0;
	RW=0;
	EN=0;
	Data=com;
	delay1ms(1);
	EN=1;
	delay1ms(1);
	EN=0;
}

void wr_dat(uchar dat)//写数据//
{ 
	delay1ms(1);;
	RS=1;
	RW=0;
	EN=0;
	Data=dat;
	delay1ms(1);
	EN=1;
	delay1ms(1);
	EN=0;
}
void wr_new()		  //写新字符
{
	uchar i;
	wr_com(0x40);
	for(i=0;i<8;i++)
	{
		wr_dat(table[i]);
	}
}
void lcd_init()//初始化设置//
{	delay1ms(15);
	wr_com(0x38);delay1ms(5);
	wr_com(0x08);delay1ms(5);
	wr_com(0x01);delay1ms(5);
 	wr_com(0x06);delay1ms(5);
	wr_com(0x0c);delay1ms(5);
	wr_new();
	wr_com(0x80);
    wr_dat('N');
	wr_com(0x81);
    wr_dat('o');
	wr_com(0x82);
    wr_dat('1');
	wr_com(0x83);
    wr_dat(':');
  	wr_com(0x8b);
    wr_dat(0x00);
	wr_com(0x8c);
    wr_dat('C');
	wr_com(0xcb);
    wr_dat(0x00);		//摄氏温度字符
	wr_com(0xcc);
    wr_dat('C');
	wr_com(0xc0);
    wr_dat('N');
	wr_com(0xc1);
    wr_dat('o');
	wr_com(0xc2);
    wr_dat('2');
	wr_com(0xc3);
    wr_dat(':');
}

/******************************ds1820程序***************************************/
void delay_18B20(uint i)//延时1微秒
{
   while(i--);
}



void ds1820rst()/*ds1820复位*/
{   uchar x=0;
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
  for (i=0;i<8;i++)
	{   
		DQ = 0; //给脉冲信号
		dat>>=1;
		DQ = 1; //给脉冲信号
		if(DQ)
		dat|=0x80;
		delay_18B20(10);
	}
   return(dat);
}
void ds1820wr(uchar dat)/*写数据*/
{ 	uchar i=0;
    for (i=0; i<8; i++)
	{ DQ = 0;
	  DQ = dat&0x01;
	  delay_18B20(10);
	  DQ = 1;
	  dat>>=1;
	}
}
void b20_Matchrom(uchar a)	 //匹配ROM
{
	char j;
	ds1820wr(0x55);	   //发送匹配ROM命令
	if(a==1)
	{
	for(j=0;j<8;j++)
		ds1820wr(str1[j]);		//发送18B20的序列号，先发送低字节 
	}
	if(a==2)
	{
	for(j=0;j<8;j++)
		ds1820wr(str2[j]);		//发送18B20的序列号，先发送低字节 
	}

} 
read_temp(uchar z)/*读取温度值并转换*/
{	uchar a,b;
	float tt;
	ds1820rst();    
	ds1820wr(0xcc);			//读序列号
	ds1820rst(); 
	if(z==1)
	{
		b20_Matchrom(1);		 //匹配ROM 1
	}
	if(z==2)
	{
		b20_Matchrom(2);		 //匹配ROM	 2
	}
	ds1820wr(0x44);//*启动温度转换*/
	delay1ms(5);
	ds1820rst();    
	ds1820wr(0xcc);				//读序列号
	ds1820rst(); 
	if(z==1)
	{
		b20_Matchrom(1);			    //匹配ROM 1
	}
	if(z==2)
	{
		b20_Matchrom(2);				//匹配ROM	 2
	}
	ds1820wr(0xbe);//*读取温度*/ 
	a=ds1820rd();
	b=ds1820rd();
	tvalue=b;
	tvalue<<=8;
	tvalue=tvalue|a;
    if(tvalue<0x0fff)
    tflag=0;
    else
   		{	
			tvalue=~tvalue+1;
			tflag=1;
 		}
	tt=tvalue*0.0625;
	tvalue=tt*10;
	return(tvalue);
}

/*****************显示函数******************************/
void ds1820disp(uchar z)//温度值显示
{    
	 uchar flagdat;
     disdata[0]=tvalue/1000+0x30;//百位数
     disdata[1]=tvalue%1000/100+0x30;//十位数
     disdata[2]=tvalue%100/10+0x30;//个位数
     disdata[3]=tvalue%10+0x30;//小数位
    
	if(tflag==0)
	flagdat=0x20;//正温度不显示符号
	else
	flagdat=0x2d;//负温度显示负号:-

	if(disdata[0]==0x30)
	{disdata[0]=0x20;//如果百位为0，不显示
	if(disdata[1]==0x30)
	{disdata[1]=0x20;//如果百位为0，十位为0也不显示
	}
   }
  if(z==1)
    {
		wr_com(0x84);
		wr_dat(flagdat);//显示符号位
		wr_com(0x85);
		wr_dat(disdata[0]);//显示百位
		wr_com(0x86);
		wr_dat(disdata[1]);//显示十位 
		wr_com(0x87);
		wr_dat(disdata[2]);//显示个位 
		wr_com(0x88);
		wr_dat(0x2e);//显示小数点 
		wr_com(0x89);
		wr_dat(disdata[3]);//显示小数位
   }
  if(z==2)
    {
		wr_com(0xc4);
		wr_dat(flagdat);//显示符号位
		wr_com(0xc5);
		wr_dat(disdata[0]);//显示百位
		wr_com(0xc6);
		wr_dat(disdata[1]);//显示十位 
		wr_com(0xc7);
		wr_dat(disdata[2]);//显示个位 
		wr_com(0xc8);
		wr_dat(0x2e);//显示小数点 
		wr_com(0xc9);
		wr_dat(disdata[3]);//显示小数位
   }
}
/********************主程序***********************************/
void main()
{ 
	lcd_init();//初始化显示
    while(1)
    {
 		read_temp(1);//读取温度
 		ds1820disp(1);//显示
		read_temp(2);//读取温度
		ds1820disp(2);//显示
  }
}
