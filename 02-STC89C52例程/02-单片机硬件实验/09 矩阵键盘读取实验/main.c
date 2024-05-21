/*************************************************************/
/********************* 24 矩阵键盘读取实验 *******************/
/*************************************************************/
/************************* 作者：XHCH ************************/
/*************************************************************/
/******************* 修改日期：2012年2月3日 ******************/
/*************************************************************/
/***************************************************************************
实验名称： 矩阵键盘读取实验

实验模块:  51单片机核心板、矩阵键盘区、液晶显示区（1602）

实验接线：  51单片机核心板------矩阵键盘区
				P1.0~P1.3 --------- ROW1~ROW4
				P1.4~P1.7 --------- LINE1~LINE4				
					
			51单片机核心板------液晶显示区（1602字符液晶）
					P2.0 --------- RS
					P2.1 --------- RW
					P2.2 --------- E
			   P0.0~P0.7 --------- BD0~BD7		
						
现象描述：	1602液晶屏上排显示按键的位码，下排显示按键所表示的字符

更新时间：	2017.10.17
***************************************************************************/

#include <reg52.h>               

unsigned char  dis_buf;       //显示缓存
unsigned char  temp;
unsigned char  key=0;         //键顺序码

sbit  LCM_RS = P2^0; 		  //定义引脚
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80 //用于检测LCM状态字中的Busy标识

unsigned char code  cdis1[ ] = {"KEY NUMBER:   H "};
unsigned char code  cdis2[ ] = {"  KEY-CODE:   H "};
unsigned char Code[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};

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
    X &= 0xF;         		//限制X不能大于15，Y不能大于1
    if (Y) X |= 0x40; 		//当要显示第二行时地址码+0x40;
    X |= 0x80;        		//算出指令码
    WriteCommandLCM(X, 0);  //这里不检测忙信号，发送地址码
    WriteDataLCM(DData);
}

/**********************************************************/
// 键扫描子程序
void  keyscan(void)
 { 
    P1=0xF0;                //行线为输入，列线为输出，并置列线输出全为0
	 temp=P1;               //读P1口       
    temp=temp&0xF0;
    temp=~((temp>>4)|0xF0);
    if(temp==1)
        key=0;
    else if(temp==2)
        key=1;
    else if(temp==4)
        key=2;
    else if(temp==8)
        key=3;
    P1=0x0F;                 //列线为输入，行线为输出，并置行线输出全为0  
	 temp=P1;                //读P1口 
    temp=temp&0x0F;
    temp=~(temp|0xF0);        
    if(temp==1)
        key=key+0;
    else if(temp==2)
        key=key+4;
    else if(temp==4)
        key=key+8;
    else if(temp==8)
        key=key+12;
    	
     dis_buf = key;	             //键值入显示缓存
     dis_buf = dis_buf&0x0f;

	 if(dis_buf>9)               //转换为ASCII码
      dis_buf = dis_buf+0x37;
    else
	   dis_buf = dis_buf+0x30;
 }

/*************************************************************/
//判断键是否按下
void  keydown(void)
 {  
  	P1=0xF0;
   Delay5Ms();
	if(P1!=0xF0)
	{
	  keyscan();
    }
 }

/*************************************************************/
// 主程序
main()
 {
    unsigned char m;
    P0=0xFF;                    //置P0口
    P2=0xFF;                    //置P2口  
    Delay5Ms();                 //延时
    LCMInit();                  //初始化LCD             
        
     m = 0;
    while(cdis1[m] != '\0')
     {                         //显示字符
       DisplayOneChar(m,0,cdis1[m]);
       m++;
     }

     m = 0;
    while(cdis2[m] != '\0')
     {
       DisplayOneChar(m,1,cdis2[m]);  //显示字符
       m++;
     }       
	  dis_buf = 0x2d;          		  //显示字符"-"

    while(1)
    { 
       keydown();
       DisplayOneChar(0x0c,0,dis_buf);    //显示按键值
       DisplayOneChar(0x0c,1,Code[key]);  //显示按键代码
    }
  }   

/************************************************************/  