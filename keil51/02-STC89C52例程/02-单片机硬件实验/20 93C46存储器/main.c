/***************************************************************************
实验名称： 93C46存储器读写实验

实验模块:  51单片机核心板、EEPROM区、液晶显示区（1602）

实验接线：  51单片机核心板------EEPROM区
					P3.4 --------- DO
					P3.5 --------- DI
					P3.6 --------- CLK
					P3.7 --------- CS
					
			51单片机核心板------液晶显示区（1602字符液晶）
					P2.0 --------- RS
					P2.1 --------- RW
					P2.2 --------- E
			   P0.0~P0.7 --------- BD0~BD7		
						
现象描述：	将数据先写入93C46芯片内，再将其数据逐个读出送LCD显示
			（为证明2401的作用，去掉2401连线，则不能读回MCU写出的数据）
			
			注意：在擦除或写入数据之前，必须先写入EWEN指令，用于8位模式

更新时间：	2017.10.17
***************************************************************************/

#include <reg52.h>
#include <intrins.h>

sbit CS  = P3^7;     //定义功能引脚
sbit SCL = P3^6;
sbit DI  = P3^5;
sbit DO  = P3^4;

sbit  LCM_RS = P2^0; //定义引脚
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

#define LCM_Data P0
#define Busy 0x80 	//用于检测LCM状态字中的Busy标识

unsigned char code  dis_code[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};//液晶显示字符表格                            

/**********************************************************/
/*******************93C46相关函数**************************/
/**********************************************************/

/**********************************************************/
//93C46端口初始化
void INIT_93C46(void)
{
    CS=0;//初始化端口
    SCL=0;
    DI=1;
    DO=1;
}

/**********************************************************/
//写入数据
void Write46(unsigned char indata)               
{
   unsigned char i;
   for(i = 0; i < 8; i++)
   {
      DI = (bit)(indata & 0x80);// 先移入高位
      SCL = 1;
      indata <<= 1;
      SCL = 0;      
   }
   DI = 1;
}

/**********************************************************/
// 读出数据
unsigned char Read46(void)         
{
   unsigned char i, out_data;
   for(i = 0; i < 8; i++)
   {
      SCL = 1;
      out_data <<= 1;
      SCL = 0;
      out_data |= (unsigned char)DO;
   }
   return(out_data);
}

/**********************************************************/
//发送一个位
void Sendbit (bit IO)            
{
    DI=IO;            //确定写入bit 0或bit 1
    SCL=1;SCL=0;      //写入脉冲
}

/*读写功能操作函数*/

/**********************************************************/
//设定 写允许 功能函数， 控制码 1 00 11XXXXX
void EWEN46 (void)            
{
    _nop_();
    CS=1;               //片选
    Sendbit(1);         //发送起始位
    Sendbit(0);         //发送操作码高位
    Write46(0x60);      //将地址信息与操作码低位整合，一起发送
    CS=0;               //取消片选
}

/**********************************************************/
//设定 写禁止 功能函数， 控制码 1 00 00XXXXX
void EWDS46 (void)            
{
    _nop_();
    CS=1;
    Sendbit(1);
    Sendbit(0);
    Write46(0x00);
    CS=0;
}

/**********************************************************/
//设定 擦除全部 功能函数，控制码 1 00 10XXXXX
void ERAL46 (void)            
{
    _nop_();
    CS=1;
    Sendbit(1);
    Sendbit(0);
    Write46(0x40);
    CS=0;
}

//用户接口功能函数

/**********************************************************/
//指定地址，读取一个字节，控制码 1 10 XXXXXXX
char ReadByte46 (unsigned char addr)       
{                                      //七位地址对应8bit模式    
    CS=SCL=0;
    CS=1;                              //片选开
    _nop_();                           //延时
    Sendbit(1);                        //发送开始位
    Sendbit(1);                        //发送操作码高位
    Write46(0x7F&addr);                //整合地址与操作码地位发送
    addr=Read46();                     //获取数据
    CS=0;_nop_();                      //关闭片选
    return (addr);                     //返回数据
}

/**********************************************************/
//指定地址，写入一个字节，控制码 1 01 XXXXXXX
void WriteByte46 (unsigned char addr,char thedata)    
{                                            //七位地址对应8bit模式
    unsigned int time=0;                     //定义超时变量
    unsigned char i=0;                       //定义写入循环变量
    do{                                      //开始三次写入循环，成功写入跳出
        CS=SCL=0;                                
        CS=1;                                //开片选信号
        EWEN46();                            //开写入允许
        _nop_();                             //延时
        CS=1;                                //重新开片选
        _nop_();
        Sendbit(1);                          //发送开始码
        Sendbit(0);                          //发送操作码高位
        Write46(0x80|addr);                  //整合操作码低位与七位地址
        Write46(thedata);                    //写入数据
        CS=0;                                //关闭片选
        _nop_();                             //延时
        CS=1;                                //重开片选
        do                                   //忙判别
        {
            if(time>500) break;              //如果期间有问题，超时退出
            time++;
        }while(!DO);                         //如果器件准备就绪，取消循环
        CS=0;                                //关闭片选
        if(ReadByte46(addr)==thedata) break; //判断写入是否正确，正确退出循环，否则写入三次
        i++;
    }while(i<3);                             //写入三次自动退出
}

/**********************************************************/
// 延时子程序
void delayms(unsigned int ms)   
{                  
   unsigned char i;
   while(ms--)
   {
      for(i = 0; i < 120; i++);
   }
}

/**********************************************************/
/*******************LCM1602相关函数************************/
/**********************************************************/
//读状态
////////////////////////////////////////////////////////////////////////////
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
    LCM_E = 0; 		//若晶振速度太高可以在这后加小的延时
    LCM_E = 0; 		//延时
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
   WriteCommandLCM(position|0x80);   //数据指针=80+地址码(00H~27H,40H~67H)
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
main()
{
    unsigned char i,j,x,y,temp=0,data_in=0;
    unsigned char Dis[]="Addr:00  Data:00";      //设定显示格式
    LCMInit();    	//LCM初始化
    INIT_93C46(); 	//93C46端口初始化
    EWEN46();       // 使能写入操作
    ERAL46();       // 擦除全部内容*/
    while(1)
    {                            
       for(i = 0 ; i <128; i++)   
          {
              WriteByte46(i,data_in);     //写入显示代码到AT93C46

              temp=i;                    //写入AT93C46数据的地址

              x=temp%16;                 //获取地址低位
              Dis[6]=dis_code[x];
              y=temp>>4;                 //获取地址高位
              Dis[5]=dis_code[y];
              x=data_in%16;              //获取数据低位
              Dis[15]=dis_code[x];
              y=data_in>>4;              //获取数据高位
              Dis[14]=dis_code[y];
              for(j=0;j<16;j++)
                 {
                     DisplayOneChar(j,0,Dis[j]);//在第一行显示本次写入的地址和数据
                 }

              temp=ReadByte46(i);      	//读取AT93C46内容
              x=i%16;                   //获取地址低位
              Dis[6]=dis_code[x];
              y=i>>4;                   //获取地址高位
              Dis[5]=dis_code[y];
              x=temp%16;                //获取数据低位
              Dis[15]=dis_code[x];
              y=temp>>4;                //获取数据高位
              Dis[14]=dis_code[y];
              for(j=0;j<16;j++)
                  {
                     DisplayOneChar(j,1,Dis[j]);//在第二行显示本次读取的地址和数据
                  }
              data_in++;
              if(data_in==128) data_in=0;
              delayms(1000);
              }
           }
}
/**********************************************************/
