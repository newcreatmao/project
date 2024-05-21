/***************************************************************************
实验名称： PS2鼠标读取实验

实验模块:  51单片机核心板、液晶显示区、鼠标键盘区、蜂鸣器区

实验接线： 51单片机核心板------鼠标键盘区(J29)
				P3.3--------------CLK
				P3.4--------------SDA
				
			51单片机核心板------液晶显示区
				 P2.0--------------RS
				 P2.1--------------RW
				 P2.2--------------E
			P0.0~P0.7--------------DB0~DB7
			
			51单片机核心板------蜂鸣器区
				P3.7--------------PUL
				
						
现象描述：按动鼠标，1602下排显示是对应是鼠标按键按下。并伴随着蜂鸣器的鸣响。

更新时间：2017.10.17
***************************************************************************/

#include<REG52.H>  
#include "intrins.h"     //_nop_();延时函数用

sbit mouse_SDA=P3^4;//数据线P3_4 
sbit mouse_CLK=P3^3;//时钟线P3_3 

sbit LCD1602_RS=P2^0;
sbit LCD1602_RW=P2^1;  
sbit LCD1602_EN=P2^2;
#define LCM1602_DATA P0

#define CLEARSCREEN LCM1602_write_cmd(0x01) 
 
#define uchar unsigned char 
#define uint unsigned int 

sbit beep=P3^7;
                             
unsigned char bdata mouse_byte; //接收字节 
sbit mouse_byte_bit0=mouse_byte^0;//mouse_byte第0位 
sbit mouse_byte_bit1=mouse_byte^1;//mouse_byte第1位 
sbit mouse_byte_bit2=mouse_byte^2;//mouse_byte第2位 
sbit mouse_byte_bit3=mouse_byte^3;//mouse_byte第3位 
sbit mouse_byte_bit4=mouse_byte^4;//mouse_byte第4位 
sbit mouse_byte_bit5=mouse_byte^5;//mouse_byte第5位 
sbit mouse_byte_bit6=mouse_byte^6;//mouse_byte第6位 
sbit mouse_byte_bit7=mouse_byte^7;//mouse_byte第7位 
 
unsigned char bdata mouse_fuction;//功能信息字节  
                       
unsigned char mouse_buffer[11];   //接收位数据缓冲区 
unsigned char mouse_buffer_bit=0; //mouse_buffer[mouse_buffer_bit] 
unsigned char mouse_data[3];      //接收鼠标数据缓冲区,分别存放:功能信息字节,x位移量,y位移量 
unsigned char mouse_data_bit=0;   //mouse_data[mouse_data_bit] 
 
unsigned int move_x=10000;//存放横坐标 
unsigned int move_y=10000;//存放纵坐标 

//********************************************************************** 
void LCM1602_Init(void);									//液晶初始化 
void LCM1602_write_cmd(unsigned char command);		//写命令 
void LCM1602_write_data(unsigned char temp);			//写数据 
void LCM1602_set_xy(unsigned char x, unsigned char y);//设置坐标 
void LCM1602_write_char(unsigned x,unsigned char y,unsigned char dat);//写一个字符到第x行y列 
void LCM1602_write_string(unsigned char x,unsigned char y,unsigned char *s);//写字符串到第x行y列 
void LCM1602_Read_BF(void);                       //读忙信号 
void num(unsigned char x,unsigned char y,unsigned int n);//在第x行,第y列显示整型数字n 
//********************************************************************** 
////////////////////////////////////////////////////////////////////////////
//LCD初始化子程序
////////////////////////////////////////////////////////////////////////////
void LCM1602_Init(void) 
{  
	LCM1602_write_cmd(0x28); 
	LCM1602_write_cmd(0x28); 
	LCM1602_write_cmd(0x28);//设置4位数据传输模式 
	LCM1602_write_cmd(0x0C); 
	LCM1602_write_cmd(0x80); 
   CLEARSCREEN; 
} 
 
////////////////////////////////////////////////////////////////////////////
//读LCD状态
//////////////////////////////////////////////////////////////////////////// 
void LCM1602_Read_BF(void) 
{ 
	LCD1602_RW=1;		//RW 1 
	LCD1602_RS=0;		//RS 0 
	LCD1602_EN=1;		//EN 1	Read BF 
 	LCM1602_DATA=LCM1602_DATA&0x0F|0xf0; 
	while(LCM1602_DATA&0x80); 
	LCD1602_EN=0;		 
}

////////////////////////////////////////////////////////////////////////////
//LCD写使能，EN端产生一个高电平脉冲，写LCD 
////////////////////////////////////////////////////////////////////////////
void LCD_en_write(void)        //
  { 
    LCD1602_EN=1; 
	 LCD1602_EN=1;
    LCD1602_EN=0;	 
  } 
 
////////////////////////////////////////////////////////////////////////////
//写指令
////////////////////////////////////////////////////////////////////////////
void LCM1602_write_cmd(unsigned char command) 
{ 
	LCM1602_Read_BF(); 
	LCD1602_RS=0;   	//RS 0  
	LCD1602_RW=0;		//RW 0  
	 
	LCM1602_DATA&=0x0F; 
	LCM1602_DATA=command&0xf0 | LCM1602_DATA&0x0f; 
	LCD_en_write(); 
	command=command<<4;  
	LCM1602_DATA&=0x0F; 
	LCM1602_DATA=command&0xf0 | LCM1602_DATA&0x0f; 
	LCD_en_write(); 
} 

////////////////////////////////////////////////////////////////////////////
//写数据
////////////////////////////////////////////////////////////////////////////
void LCM1602_write_data(unsigned char dat) 
{ 
	LCM1602_Read_BF(); 
	LCD1602_RS=1;	 //RS 1  
	LCD1602_RW=0;	 //RW 0  
	LCM1602_DATA &=0x0F; 
	LCM1602_DATA=dat&0xf0 | LCM1602_DATA&0x0f; 
	LCD_en_write(); 
	dat=dat<<4; 
	LCM1602_DATA &=0x0F; 
	LCM1602_DATA=dat&0xf0 | LCM1602_DATA&0x0f; 
	LCD_en_write(); 
} 

////////////////////////////////////////////////////////////////////////////
//设定显示位置
////////////////////////////////////////////////////////////////////////////
void LCM1602_set_xy(unsigned char x,unsigned char y) 
{ 
	unsigned char address; 
	y&=0x0f; 
	if(!x)	 
		address=0x80+y; 
	else 			 
		address=0xc0+y; 
	LCM1602_write_cmd(address);  
} 

////////////////////////////////////////////////////////////////////////////
//按指定位置显示一个字符
////////////////////////////////////////////////////////////////////////////
void LCM1602_write_char(unsigned x,unsigned char y,unsigned char dat) 
{ 
	LCM1602_set_xy(x,y);  
	LCM1602_write_data(dat); 
} 

////////////////////////////////////////////////////////////////////////////
//按指定位置显示一串字符
////////////////////////////////////////////////////////////////////////////
void LCM1602_write_string(unsigned char x,unsigned char y,const unsigned char *s) 
{ 
	LCM1602_set_xy(x,y);  
	while(*s)   
	{ 
		LCM1602_write_data(*s);    
		s++; 
	} 
} 

////////////////////////////////////////////////////////////////////////////
//位移数据处理和现实函数
//////////////////////////////////////////////////////////////////////////// 
void num(unsigned char x,unsigned char y,unsigned int n) 
{ 
	unsigned char i,length,a[6]={0,0,0,0,0,0}; 
	unsigned int nx=n; 
	if(n==0){LCM1602_write_char(x,y,'0');return;} 
	for(i=0;i<6;i++) 
	{ 
		if(nx>=1)length++; 
		nx/=10; 
	} 
	nx=n; 
	for(;length>0;length--) 
	{ 
		a[length-1]=nx%10+48; 
		nx/=10; 
	} 
	LCM1602_write_string(x,y,a); 
}

////////////////////////////////////////////////////////////////////////////
//起始值delayus(1)=27us,间隔9.9us 
////////////////////////////////////////////////////////////////////////////
void delay10us(unsigned int t) 
{ 
	while(t--); 
}

////////////////////////////////////////////////////////////////////////////
// 1ms延时子程序
////////////////////////////////////////////////////////////////////////////
void delayms(int ms)
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

////////////////////////////////////////////////////////////////////////////
//鼠标初始化子函数
////////////////////////////////////////////////////////////////////////////
void Init_mouse(void) 
{ 
     TCON=0x00; 
     EA=1; 
     EX1=1;   //允许外部中断1 
     ET0=0x01;//允许全局中断，允许定时器/计数器0溢出中断 
     PX1=1;   //设置中断优先级 
} 
 
////////////////////////////////////////////////////////////////////////////
//发送数据给鼠标
////////////////////////////////////////////////////////////////////////////
void mouse_send_data(unsigned char dat) 
{ 
	unsigned char i; 
	EX1=0;                    //关闭外部中断1
	ACC=dat;                  //将要发送的数据放入A寄存器
	mouse_CLK=0;              //拉低时钟线
	delay10us(200);           //延时100us以上
	mouse_SDA=0;              //拉低数据线
	delay10us(40); 
	mouse_CLK=1;              //释放时钟线
	for(i=0;i<=7;i++)         //低位在前，一次发送8个数据位
	{ 
		while(mouse_CLK==1);   //等待设备拉低时钟线
		mouse_SDA=(dat>>i)&0x01;//发送数据位
		while(mouse_CLK==0);   //等待设备释放时钟线
	} 
	while(mouse_CLK==1); 
	mouse_SDA=~P;             //发送校验位，奇校验
	while(mouse_CLK==0); 
	while(mouse_CLK==1); 
	mouse_SDA=1;              //发送停止位
	while(mouse_CLK==0);							   
	while(mouse_CLK==1);		  //应答位
	while(mouse_CLK==0);	 
	EX1=1;                    //打开外部中断1
} 
 
////////////////////////////////////////////////////////////////////////////
//奇校检子程序
////////////////////////////////////////////////////////////////////////////
unsigned char Checkout(void)			 
{ 
	ACC=mouse_byte; 
	if(~P==mouse_buffer[9]) 
		return 1; 
	else 
		return 0; 
}  

////////////////////////////////////////////////////////////////////////////
//数据分析及处理子程序
////////////////////////////////////////////////////////////////////////////
void data_analyse(void) 
{ 
	//将收到的11位信号中截取8位数据放进mouse_byte 
	mouse_byte_bit0=mouse_buffer[1]; 
	mouse_byte_bit1=mouse_buffer[2]; 
	mouse_byte_bit2=mouse_buffer[3]; 
	mouse_byte_bit3=mouse_buffer[4]; 
	mouse_byte_bit4=mouse_buffer[5]; 
	mouse_byte_bit5=mouse_buffer[6]; 
	mouse_byte_bit6=mouse_buffer[7]; 
	mouse_byte_bit7=mouse_buffer[8];	 
	if(Checkout())//如果校验正确 
	{ 
		if(mouse_data_bit<3)          
			mouse_data[mouse_data_bit++]=mouse_byte;  
		if(mouse_data_bit==3) 
		{ 
			mouse_data_bit=0; 
			if(mouse_data[0]&0x10)//如果"X sign bit"为1,表示鼠标向左移 
			{ 
				move_x-=(256-mouse_data[1]);//x坐标减 
			} 
			else 
			{ 
				move_x+=mouse_data[1];//x坐标加
			} 
			if(mouse_data[0]&0x20) 
			{ 
				move_y-=(256-mouse_data[2]);//y坐标减
			} 
			else 
			{ 
				move_y+=mouse_data[2];//y坐标加 
			} 
		} 
	} 
} 

////////////////////////////////////////////////////////////////////////////
//外部中断1，由鼠标的时钟线触发
////////////////////////////////////////////////////////////////////////////
void ReceiveData(void)  interrupt 2
{ 
	if(mouse_buffer_bit<=10) 
	{	                               	  
		while(mouse_CLK==0);//等待设备拉高时钟线 
		mouse_buffer[mouse_buffer_bit++]=mouse_SDA;//接收数据 
	}	 
	if(mouse_buffer_bit==10) 
	{ 
		data_analyse();//数据分析及处理 
		mouse_buffer_bit=0; 
	}			 	 					 
}

void main()   
{      
    Init_mouse();
    LCM1602_Init();
    mouse_send_data(0xf4);//向鼠标发送0xF4命令让其开始工作     
    EX1=0;//关掉外部中断以避开鼠标发回的应答
    delayms(100);
    EX1=1;//重开外部中断
    while(1)   
    {          
        CLEARSCREEN;//清屏    
        LCM1602_write_string(0,0,"x:");   
        num(0,2,move_x);//x坐标值    
        LCM1602_write_string(0,8,"y:");   
        num(0,10,move_y);//y坐标值    
        if(mouse_data[0]&0x01)//如果点下左键    
        {
            beep=0;
            LCM1602_write_string(1,0,"Left Key is Down");   
        }   
        else if(mouse_data[0]&0x02)//如果点下右键    
        {   
            beep=0;
            LCM1602_write_string(1,0,"Right  Key  Down");   
        }   
        else if(mouse_data[0]&0x04)//如果点下中键    
        {   
            beep=0;
            LCM1602_write_string(1,0,"Middle Key Down!");   
        }   
        else   
        {   
            beep=1;
            LCM1602_write_string(1,0,"No Key  is Down!");   
        }
        delayms(50);   
    }   
}  