/***************************************************************************
实验名称： 24C01存储器读写实验

实验模块:  51单片机核心板、EEPROM区、液晶显示区（1602）

实验接线：  51单片机核心板------EEPROM区
					P3.6 --------- SCL
					P3.7 --------- SDA
					
			51单片机核心板------液晶显示区（1602字符液晶）
					P2.0 --------- RS
					P2.1 --------- RW
					P2.2 --------- E
			   P0.0~P0.7 --------- BD0~BD7		
						
现象描述：	将数据先写入24C01芯片内，再将其数据逐个读出送LCD显示
			（为证明2401的作用，去掉2401连线，则不能读回MCU写出的数据 ）

更新时间：	2017.10.17
***************************************************************************/

#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int

#define OP_READ  0xa1          // 器件地址以及读取操作
#define OP_WRITE 0xa0          // 器件地址以及写入操作

sbit  LCM_RS = P2^0;			 //定义引脚
sbit  LCM_RW = P2^1;
sbit  LCM_E  = P2^2;

sbit SDA = P3^7;    
sbit SCL = P3^6;

#define LCM_Data P0
#define Busy 0x80 //用于检测LCM状态字中的Busy标识

unsigned char code  dis_code[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};//液晶显示字符表格                            

unsigned char shift;
unsigned char count=0;

/**********************************************************/
/*******************24C01操作相关函数**********************/
/**********************************************************/
//**********************************************************
//延时子程序
#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};

//**********************************************************
//延时子程序
void Delay_ms(uint ms) 
{
    uchar k;
    while(ms--)
       {
           for(k = 0; k < 120; k++);
       }
}

//**********************************************************
// 开始位
void Start()
{
   SDA = 1;
   SCL = 1;
   delayNOP();
   SDA = 0;
   delayNOP();
   SCL = 0;
}

//**********************************************************
//  停止位
void stop()
{
   SDA = 0;
   delayNOP();
   SCL = 1;
   delayNOP();
   SDA = 1;
}

//**********************************************************
// 从AT24C01读出数据到MCU
uchar read()
{
   uchar i,read_data;
   for(i = 0; i < 8; i++)
   {
     SCL = 1;
     read_data <<= 1;
     read_data |= SDA;
     SCL = 0;
   }
   return(read_data);
}

//**********************************************************
// 从MCU写入数据到AT24C01
bit write(uchar write_data) 
{
    uchar i;
    bit ack_bit;
    for(i = 0; i < 8; i++)  // 循环移入8个位
       {
          SDA = (bit)(write_data & 0x80);
          _nop_();
          SCL = 1;
          delayNOP();
          SCL = 0;
          write_data <<= 1;
       }
    SDA = 1;   // 读取应答
    delayNOP();
    SCL = 1;
    delayNOP();
    ack_bit = SDA;
    SCL = 0;
    return ack_bit; // 返回AT24C01应答位
}

//**********************************************************
// 在指定地址addr处写入数据write_data
void write_byte(uchar addr, uchar write_data)
{
    Start();
    write(OP_WRITE);
    write(addr);
    write(write_data);
    stop();
    Delay_ms(10);  // 写入周期
}

//**********************************************************
// 在当前地址读取
uchar read_current()
{
    uchar read_data;
    Start();
    write(OP_READ);
    read_data = read();
    stop();
    return read_data;
}

//**********************************************************
// 在指定地址读取
uchar read_random(uchar random_addr)
{
   Start();
   write(OP_WRITE);
   write(random_addr);
   return(read_current());
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

void LCMInit(void) //LCM初始化
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
    WriteCommandLCM(0x06,1); // 显示光标移动设置
    WriteCommandLCM(0x0C,1); // 显示开及光标设置
}

/**********************************************************/
//按指定位置显示一个字符
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
    Y &= 0x1;
    X &= 0xF; //限制X不能大于15，Y不能大于1
    if (Y) X |= 0x40; //当要显示第二行时地址码+0x40;
    X |= 0x80; //算出指令码
    WriteCommandLCM(X, 0); //这里不检测忙信号，发送地址码
    WriteDataLCM(DData);
}

/**********************************************************/
//**********************************************************
main()
{
	unsigned char i,j,x,y,temp=0,data_in=0;
	unsigned char Dis[]="Addr:00  Data:00";      //设定显示格式
	LCMInit();    //LCM初始化
	SDA = 1;
	SCL = 1;  		   
	while(1)
	{				       		   
		for(i = 0 ; i <128; i++)	
		{
			write_byte(i,data_in);     //写入显示代码到AT24C01
			
			temp=i;                    //写入AT24C01数据的地址
			
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
			
			temp=read_random(i);      //读取AT24C01内容
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
//***********************************************************
