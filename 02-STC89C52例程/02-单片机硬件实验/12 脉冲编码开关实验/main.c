/*************************************************************/
/********************** 12 脉冲编码开关实验 ******************/
/*************************************************************/
/************************* 作者：XHCH ************************/
/*************************************************************/
/******************* 修改日期：2012年2月2日 ******************/
/*************************************************************/
/***************************************************************************
实验名称： 脉冲编码开关实验

实验模块:  51单片机核心板、液晶显示区、脉冲编码器区

实验接线：  51单片机核心板------脉冲编码器区
					P3.2---------B
					P3.3---------A
					P3.4---------D
					
			51单片机核心板------液晶显示区（1602字符液晶）
					P2.0---------RS
					P2.1---------RW
					P2.2---------E
			   P0.0~P0.7---------BD0~BD7	
						
现象描述：	1.按下脉冲编码器，LCD1602显示“You Pressed it！”
			2.顺时针转动脉冲编码器，1602显示的变量增加；反之，减小。

更新时间：2017.10.17
***************************************************************************/
#include "reg52.h"       
#include "intrins.h"     	//_nop_();延时函数用

sbit  LCM_RS = P2^0; 		//定义引脚
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

sbit  Pulse_coder_A = P3^3;
sbit  Pulse_coder_B = P3^2;
sbit  Pulse_coder_D = P3^4;

#define LCM_Data P0
#define Busy 0x80 //用于检测LCM状态字中的Busy标识

unsigned char DisP[]="You Pressed it!";       //设定显示字符
unsigned char Now_Num[]="Now the Uum:    ";   //现在的值

unsigned char i,temp;
unsigned char num=0x80;

/**********************************************************/
// 1ms延时子程序
void delay1ms(int ms)
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

/**********************************************************/
/*******************LCM1602相关函数************************/
/**********************************************************/
//读状态
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

/**********************************************************/
//5ms延时
void Delay5Ms(void)
{
    unsigned int TempCyc = 5552;
    while(TempCyc--);
}

/**********************************************************/
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

/**********************************************************/
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

/**********************************************************/
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

/**********************************************************/
//LCD数据指针位置程序
void LCM_pos(char position)
{						
	WriteCommandLCM(position|0x80);	//数据指针=80+地址码(00H~27H,40H~67H)
}

/**********************************************************/
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

/**********************************************************/
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

/**********************************************************/
//中断设置初始化
void Int_Init(void)
{
    TCON=0x01;//设定外部中断0为边沿触发方式
    EX0=1;    //允许外部中断0
    PX0=1;    //设置外部中断0为高优先级
    EA=1;     //开总中断
}

/**********************************************************/
main()
{
    LCMInit();    //LCM初始化
    Int_Init();   //系统初始化
    while(1)
       {
           if(!Pulse_coder_D)
              {
              for(i=0;i<0x0F;i++)
                 {
                     DisplayOneChar(i,0,DisP[i]);
                 }
              }
           delay1ms(100);
       }
}

/**********************************************************/
//外部中断0中断服务子程序
void Out_interrupt0 (void) interrupt 0
{
   EA=0;     //关总中断
   _nop_();_nop_();_nop_();_nop_();_nop_();
   _nop_();_nop_();_nop_();_nop_();_nop_();//微量延时
   if(Pulse_coder_B==Pulse_coder_A)
      {
         if(num==0xFF)
         {
            num=0xFF;
         }
         else
         {
            num=num+1;
         }
         temp=num/16;
         if(temp>9)               //转换为ASCII码
            temp= temp+0x37;
         else
	         temp=temp+0x30;
         Now_Num[12]=temp;
         temp=num%16;
         if(temp>9)               //转换为ASCII码
            temp= temp+0x37;
         else
	         temp=temp+0x30;
         Now_Num[13]=temp;
      }
   else if(Pulse_coder_B==(~Pulse_coder_A))
      {
         if(num==0x00)
         {
            num=0x00;
         }
         else
         {
            num=num-1;
         }
            temp=num/16;
         if(temp>9)               //转换为ASCII码
            temp= temp+0x37;
         else
	         temp=temp+0x30;
         Now_Num[12]=temp;
         temp=num%16;
         if(temp>9)               //转换为ASCII码
            temp= temp+0x37;
         else
	         temp=temp+0x30;
         Now_Num[13]=temp;
      }
   for(i=0;i<0x10;i++)
       {
          DisplayOneChar(i,0,Now_Num[i]);
       }
   EA=1;     //开总中断
}