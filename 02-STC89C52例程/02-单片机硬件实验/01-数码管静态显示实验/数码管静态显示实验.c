/***************************************************************************
实验名称： 静态数码管显示实验

实验模块:  51单片机核心板、静态数码管区

实验接线： 51单片机核心板------静态数码管区
						P1.0---------CLK
						
						P1.1---------SDA
						
现象描述：循环显示“0~f”

更新时间：2017.10.17
***************************************************************************/


#include<reg52.h> 
#define uint unsigned int 
#define uchar unsigned char 
sbit DAT = P1^1;		//定义管脚P1.1
sbit CLK = P1^0;		//定义管脚P1.0
uchar code tab[] = {0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,
					0xff,0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e};//0-F在数码管上显示的16进制数

 
void sendbyte(uchar byte) 	   	//发送字节的程序
{     
	uchar num,c;  
	num = tab[byte];		   	//取段码
	for(c = 0; c < 8; c++) 		//发送8位段码
	{ 
		CLK = 0; 
		DAT = num&0x01; 		//发送最低位数据
		CLK = 1; 
		num>>=1; 				//数据右移一位
	       
	} 
} 
void mDelay(uint Delay)	//延时
{	uint i;
	for(;Delay > 0;Delay--)
		for(i = 0;i < 110;i++);
}


main() 
{  
	unsigned char h; 
	while(1){ 
		for(h = 0; h < 16; h++){   	//依次把tab中16个数输入进去
			mDelay(50);				//调用延时程序，延时50毫秒 
			sendbyte(h); 	  		//调用发送字节的程序
			mDelay(500);			//调用延时程序，延时500毫秒 
		} 
		h = 0; 
	} 
     
} 

