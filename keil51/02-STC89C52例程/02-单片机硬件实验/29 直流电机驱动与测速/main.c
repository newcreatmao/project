/***************************************************************************
实验名称： 	直流电机驱动与测速实验

实验模块:  	51单片机核心板、简单I/O扩展区、轻触开关区、直流电机区、液晶显示区

实验接线：  51单片机核心板 --------- 简单I/O扩展区
					P2.6 ------------ A0
					P2.7 ------------ A1
					
			51单片机核心板 --------- 轻触开关区
					P1.0 ------------ K1
					P1.1 ------------ K2
					
			51单片机核心板 --------- 直流电机区
					P3.2 ------------ SPEED
					
			51单片机核心板------液晶显示区（1602字符液晶）
					P2.0 ------------ RS
					P2.1 ------------ RW
					P2.2 ------------ E
			   P0.0~P0.7 ------------ BD0~BD7
			   
			简单I/O扩展区 --------- 直流电机区
					  B0 ------------ MOTO1
					  B1 ------------ MOTO2
					  
			注：简单I/O扩展区的 T/R接+5V，OE接GND
			
现象描述：	按动按钮K1改变电机的转速，按动电机K2改变电机转动方向

更新时间：	2017.10.17
***************************************************************************/

#include <reg52.h>    
#define uchar unsigned char
#define uint unsigned int

#define CIRCLE 15  //速度可调节的档位设置

unsigned char count=1,last=1;
char old=0 ,new=0;

sbit  LCM_RS = P2^0; //定义引脚
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80 //用于检测LCM状态字中的Busy标识

uint time,speed;
uchar Dis[]="  Speed:000r/s  ";//定义显示格式

bit  PWM,flag=0;
sbit Moto1 = P2^6;
sbit Moto2 = P2^7;
sbit key   = P1^0;
sbit dir   = P1^1;


//LCM1602相关函数,读状态
unsigned char ReadStatusLCM(void)
{
    LCM_Data = 0xFF; 
    LCM_RS = 0;
    LCM_RW = 1;
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1;
    while (LCM_Data & Busy); //检测忙信号
    return(LCM_Data);
    LCM_E = 0;
}


//5ms延时
void Delay5Ms(void)
{
    unsigned int TempCyc = 5552;
    while(TempCyc--);
}

//写数据
void WriteDataLCM(unsigned char WDLCM)
{
    ReadStatusLCM(); //检测忙
    LCM_Data = WDLCM;
    LCM_RS = 1;
    LCM_RW = 0;
    LCM_E = 0; //若晶振速度太高可以在这后加小的延时
    LCM_E = 0; //延时
    LCM_E = 1;
    LCM_E = 0;
}

//写指令
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysC为0时忽略忙检测
{
    if (BuysC) ReadStatusLCM(); //根据需要检测忙
    LCM_Data = WCLCM;
    LCM_RS = 0;
    LCM_RW = 0; 
    LCM_E = 0;
    LCM_E = 0;
    LCM_E = 1; 
    LCM_E = 0;
}

//读数据
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

//LCD数据指针位置程序
void LCM_pos(char position)
{						
	WriteCommandLCM(position|0x80);	//数据指针=80+地址码(00H~27H,40H~67H)
}

//LCM初始化
void LCMInit(void) 
{
    LCM_Data = 0;
    WriteCommandLCM(0x38,0); //三次显示模式设置，不检测忙信号
    Delay5Ms(); 
    WriteCommandLCM(0x38,0);
    Delay5Ms(); 
    WriteCommandLCM(0x38,0);
    Delay5Ms(); 

    WriteCommandLCM(0x38,1); //显示模式设置,开始要求每次检测忙信号
    WriteCommandLCM(0x08,1); //关闭显示
    WriteCommandLCM(0x01,1); //显示清屏
    WriteCommandLCM(0x06,1); //显示光标移动设置
    WriteCommandLCM(0x0C,1); //显示开及光标设置
}

//按指定位置显示一个字符
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
    Y &= 0x1;
    X &= 0xF;         //限制X不能大于15，Y不能大于1
    if (Y) X |= 0x40; //当要显示第二行时地址码+0x40;
    X |= 0x80;        //算出指令码
    WriteCommandLCM(X, 0); //这里不检测忙信号，发送地址码
    WriteDataLCM(DData);
}




void delay(unsigned int tx) //电机控制和速度测量相关函数,延时子程序
{
	unsigned int x=tx;
	do
		x--;
	while(x>1);
}


void pwmkey(void) //脉宽调制函数
{
    if(key==0)
      {
			delay(200);  //消抖动
			if(key==0)
			  {
              last++;
           }
         if(last>CIRCLE)
           last=1;
         while(!key);//等待按键释放
       }
}



void Dir_key(void) //控制电机转动方向函数
{
    if(dir==0)
      {
			delay(200);  //消抖动
			if(dir==0)
			  {
              flag=~flag;
           }
         while(!key);//等待按键释放
       }
}

void Timer0(void) interrupt 1  //定时器0溢出中断服务子程序，用于产生PWM波
{
   count++;
   if(count>CIRCLE) 
     {
        count=1;
     } 
   if(count<=last)
      PWM=0;
   else 
      PWM=1;
   TH0=0xFC;
   TL0=0x66;
}

void INT_0 (void) interrupt 0  //外部中断0中断服务子程序，用于记录测速器模块产生的脉冲数目
{
   EX0=0;    //禁止外部中断0中断
   time++;
   EX0=1;    //允许外部中断0中断
}



void Timer1 (void) interrupt 3 //定时器1溢出中断服务子程序，用于获取速度值
{
   TH1=0x4C;      //重装定时初值
   TL1=0x00;      //50ms定时
   time=time*300;        //防止个位被去除
   speed=(time/3)*20;    //速度：r/s
   speed=speed/300;
   Dis[8]=speed/100+0x30; //速度百位值显示
   if(Dis[8]==0x30) Dis[8]=0x20;//如果百位为0，则显示为空格
   speed=speed%100;
   Dis[9]=speed/10+0x30;  //速度十位值显示
   Dis[10]=speed%10+0x30; //速度个位值显示
   time=0;
}


void INT_Init() //系统初始化函数，初始化定时器T0、T1和外部中断0
{
   TMOD=0x10;     //选择T1工作于方式1
   TH1=0x4C;
   TL1=0x00;      //50ms定时
   ET1=1;         //允许T1中断
   TR1=1;         //启动T1中断

   ET0=1;         //允许T0中断
   TH0=0xFC;
   TL0=0x66;
   TR0=1;         //启动T0中断

   IT0=1;         //下降沿触发
   EX0=1;         //允许外部中断0中断

   EA=1;          //开所有中断
}


void main(void)   //主函数
{
   uchar i;
   INT_Init();
   LCMInit();
   while(1)
     {
        pwmkey();
        Dir_key();
        if(flag)//正传
           {
              Moto1=PWM;
              Moto2=0;
           }
        if(!flag)//反传
           {
              Moto2=PWM;
              Moto1=0;
           }
        for(i=0;i<0x10;i++)
           {
              DisplayOneChar(i,0,Dis[i]);
           }
     }
}