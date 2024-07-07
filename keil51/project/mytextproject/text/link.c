#include <REGX52.H>
#include "link.h"
#include <INTRINS.H>

//���Ŷ���

/*
sbit XPY2046_DIN=P3^4;
sbit XPY2046_CS=P3^5;
sbit XPY2046_DCLK=P3^6;
sbit XPY2046_DOUT=P3^7;
*/

#define XPY2046_DIN P3_4
#define XPY2046_CS P3_5
#define XPY2046_DCLK P3_6
#define XPY2046_DOUT P3_7

/**
  * @brief  ZPT2046��ȡADֵ
  * @param  Command �����֣���Χ��ͷ�ļ��ڶ���ĺ꣬��β�����ֱ�ʾת����λ��
  * @retval ADת���������������Χ��8λΪ0~255��12λΪ0~4095
  */
unsigned int XPT2046_ReadAD(unsigned char Command)
{
	unsigned char i;
	unsigned int Data=0;
	XPY2046_DCLK=0;
	XPY2046_CS=0;
	for(i=0;i<8;i++)
	{
		XPY2046_DIN=Command&(0x80>>i);
		XPY2046_DCLK=1;
		XPY2046_DCLK=0;
	}
	for(i=0;i<16;i++)
	{
		XPY2046_DCLK=1;
		XPY2046_DCLK=0;
		if(XPY2046_DOUT){Data|=(0x8000>>i);}
	}
	XPY2046_CS=1;
	return Data>>8;
}