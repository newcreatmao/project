/***************************************************************************
实验名称： 红外接收实验

实验模块:  51单片机核心板、红外传输区、液晶显示区（1602）

实验接线：  51单片机核心板------红外传输区
					P3.2 --------- RXD				
					
			51单片机核心板------液晶显示区（1602字符液晶）
					P2.0 --------- RS
					P2.1 --------- RW
					P2.2 --------- E
			   P0.0~P0.7 --------- BD0~BD7		
						
现象描述：	按下红外遥控器，1602液晶屏显示接收到的红外数据信号

更新时间：	2017.10.17
***************************************************************************/

#include <reg52.h>		  
#define uchar unsigned char
#define uint  unsigned int

sbit IRIN = P3^2;    //红外接收器数据线

uchar IRCOM[7];

sbit  LCM_RS = P2^0; //定义引脚
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80    //用于检测LCM状态字中的Busy标识

uchar code  cdis1[ ] = {" REMOTE CONTROL "};
uchar code  cdis2[ ] = {"  IR-CODE: --H  "};


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


//x*0.14MS延时
void delay(unsigned char x)
{
   unsigned char i;
   while(x--)
     {
        for (i = 0; i<13; i++) {}
     }
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
    X &= 0xF;         		//限制X不能大于15，Y不能大于1
    if (Y) X |= 0x40; 		//当要显示第二行时地址码+0x40;
    X |= 0x80;        		//算出指令码
    WriteCommandLCM(X, 0); 	//这里不检测忙信号，发送地址码
    WriteDataLCM(DData);
}


main()
{
    uchar m;
  
    IE = 0x81;                //允许总中断中断,使能 INT0 外部中断
    TCON = 0x01;              //触发方式为脉冲负边沿触发
    
    IRIN=1;                   //I/O口初始化
	
    Delay5Ms();               //延时
    LCMInit();                //初始化LCD             
        
     m = 0;
    while(cdis1[m] != '\0')
     {                         //显示字符
       DisplayOneChar(m,0,cdis1[m]);
       m++;
     }

     m = 0;
    while(cdis2[m] != '\0')
     {
       DisplayOneChar(m,1,cdis2[m]);      //显示字符
       m++;
     }

   while(1)	;

}


//遥控键值获取和处理函数

void IR_IN() interrupt 0 using 0
{
    unsigned char j,k,N=0;
    EX0 = 0;   
	 delay(15);
	 if (IRIN==1)           //确认IR信号出现
       { 
          EX0 =1;
	       return;
	    } 
                           
     while (!IRIN)         //等IR变为高电平，跳过9ms的前导低电平信号。
       {
           delay(1);
       }

     for (j=0;j<4;j++)  //收集四组数据
       { 
           for (k=0;k<8;k++)		//每组数据有8位
               {
                   while (IRIN)		//等 IR 变为低电平，跳过4.5ms的前导高电平信号。
                       {
                           delay(1);
                       }
                   while (!IRIN)	//等 IR 变为高电平
                       {
                           delay(1);
                       }
                   while (IRIN) 	//计算IR高电平时长
                       {
                           delay(1);
                           N++;           
                           if (N>=30)
	                            { 
                                  EX0=1;
	                               return; //0.14ms计数过长自动离开。
                               } 
                       }                  //高电平计数完毕                
                   IRCOM[j]=IRCOM[j] >> 1;//数据最高位补“0
                   if (N>=8) 
                       {
                           IRCOM[j] = IRCOM[j] | 0x80;//数据最高位补“1”
                       }  
                   N=0;
               }//end for k
       }//end for j
   
   if (IRCOM[2]!=~IRCOM[3])
       { 
           EX0=1;
           return; 
       }

   IRCOM[5]=IRCOM[2]&0x0F;     //取键码的低四位
   IRCOM[6]=IRCOM[2]>>4;       //右移4次，高四位变为低四位

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

       DisplayOneChar(0x0b,1,IRCOM[6]);        //第一位数显示
       DisplayOneChar(0x0c,1,IRCOM[5]);        //第二位数显示

       EX0 = 1; 
} 
