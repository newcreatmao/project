/*************************************************************/
/********************** 10 阵列LED显示实验 *******************/
/*************************************************************/
/************************* 作者：XHCH ************************/
/*************************************************************/
/******************* 修改日期：2012年2月1日 ******************/
/*************************************************************/


#include<reg52.h>
#define uint unsigned int 
#define uchar unsigned char


sbit P1_0 = P1^0;
sbit P1_1 = P1^1;
sbit P1_2 = P1^2;
sbit P1_3 = P1^3;
sbit P1_4 = P1^4;
sbit P1_5 = P1^5;
sbit P1_6 = P1^6;
sbit P1_7 = P1^7;
sbit P3_0 = P3^0;
sbit P3_1 = P3^1;
sbit P3_2 = P3^2;
sbit P3_3 = P3^3;
sbit P3_4 = P3^4;
sbit P3_5 = P3^5;
sbit P3_6 = P3^6;
sbit P3_7 = P3^7;

uint Tab1[32] = 
	{0xFF,0xFC,0xFF,0xFC,0x80,0xFC,0x9F,0x80,0x1F,0x9E,0x49,0xCE,0x03,0xF9,0x87,0xF9,  
	0xE7,0xF9,0xC3,0xF0,0x93,0xF0,0x19,0xE6,0x7C,0xE6,0x3F,0xCF,0x9F,0x9F,0xCF,0x3F};	//  "欢" 1

void mDelay(uchar Delay)	//延时
{	uchar i;
	for(;Delay > 0;Delay--)
		for(i = 0;i < 110;i++);
}

void main()				//主函数
{

	while(1)
	{ 

		P1 = 0;
		P3 = 0;
		P0 = Tab1[0];
		P2 = Tab1[1];
		P1_0 = 1;
        mDelay(1);;
		P1_0 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[2];
		P2 = Tab1[3];
		P1_1 = 1;
        mDelay(1);
		P1_1 = 0;
		
		P1 = 0;
		P3 = 0;
		P0 = Tab1[4];
		P2 = Tab1[5];
		P1_2 = 1;
        mDelay(1);
		P1_2 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[6];
		P2 = Tab1[7];
		P1_3 = 1;
        mDelay(1);
		P1_3 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[8];
		P2 = Tab1[9];
		P1_4 = 1;
        mDelay(1);
		P1_4 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[10];
		P2 = Tab1[11];
		P1_5 = 1;
        mDelay(1);
		P1_5 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[12];
		P2 = Tab1[13];
		P1_6 = 1;
        mDelay(1);
		P1_6 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[14];
		P2 = Tab1[15];
		P1_7 = 1;
        mDelay(1);
		P1_7 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[16];
		P2 = Tab1[17];
		P3_0 = 1;
        mDelay(1);
		P3_0 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[18];
		P2 = Tab1[19];
		P3_1 = 1;
        mDelay(1);
		P3_1 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[20];
		P2 = Tab1[21];
		P3_2 = 1;
        mDelay(1);
		P3_2 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[22];
		P2 = Tab1[23];
		P3_3 = 1;
        mDelay(1);
		P3_3 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[24];
		P2 = Tab1[25];
		P3_4 = 1;
               mDelay(1);
		P3_4 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[26];
		P2 = Tab1[27];
		P3_5 = 1;
               mDelay(1);
		P3_5 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[28];
		P2 = Tab1[29];
		P3_6 = 1;
               mDelay(1);
		P3_6 = 0;

		P1 = 0;
		P3 = 0;
		P0 = Tab1[30];
		P2 = Tab1[31];
		P3_7 = 1;
               mDelay(1);
		P3_7 = 0;

		mDelay(2);
	}
}
