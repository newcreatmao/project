////////////////////////////////////////////////////////////////////////////
// 〖说明〗I2C总线驱动程序(用两个普通IO模拟I2C总线)
// 包括100Khz(T=10us)的标准模式(慢速模式)选择，
// 和400Khz(T=2.5us)的快速模式选择，
// 默认11.0592Mhz的晶振。
////////////////////////////////////////////////////////////////////////////

#ifndef __I2C_H__		//防止头文件被重复编译
#define __I2C_H__

sbit SDA =P1^0;			//定义管脚
sbit SCL =P1^1;

#include <STC8A.h>
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int
#define Byte unsigned char
#define Word unsigned int
#define bool bit
#define true 1
#define false 0

extern uchar SystemError;

#define FourNOPs(); _nop_();_nop_();_nop_();_nop_();	//_nop_()为延时
////////////////////////////////////////////////////////////////////////////
//I2C开始位                                                               //
//调用方式：void I2CStart(void)  函数说明：私有函数，I2C专用
////////////////////////////////////////////////////////////////////////////
void I2CStart(void)
{
    SDA=1;
	 SCL=1; 
	 FourNOPs();		//INI
    SDA=0; 
	 FourNOPs(); 		//START
    SCL=0;
}

////////////////////////////////////////////////////////////////////////////
//I2C停止位                                                               //
// 调用方式：void I2CStop(void) 函数说明：私有函数，I2C专用
////////////////////////////////////////////////////////////////////////////
void I2CStop(void)
{
    SCL=0; 
    SDA=0; 
    FourNOPs(); 		//INI
    SCL=1; 
    FourNOPs(); 
    SDA=1; 			//STOP
}

////////////////////////////////////////////////////////////////////////////
// 调用方式：bit I2CAck(void) 
// 函数说明：私有函数，I2C专用，等待从器件接收方的应答
////////////////////////////////////////////////////////////////////////////
 bool WaitAck(void)
{
    uchar errtime=255;		//因故障接收方无ACK，超时值为255。
    SDA=1;
    FourNOPs();
    SCL=1;
    FourNOPs();
    while(SDA) 
    {
        errtime--; if (!errtime) {I2CStop();SystemError=0x11;
        return false;}
	}
    SCL=0;
    return true;
}
////////////////////////////////////////////////////////////////////////////
// 调用方式：void SendAck(void) 
// 函数说明：私有函数，I2C专用，主器件为接收方，从器件为发送方时，应答信号。
////////////////////////////////////////////////////////////////////////////
void SendAck(void)
{
    SDA=0; 
    FourNOPs();
    SCL=1; 
    FourNOPs();
    SCL=0;
}

////////////////////////////////////////////////////////////////////////////
// 调用方式：void SendNotAck(void) 
// 函数说明：私有函数，I2C专用，主器件为接收方，从器件为发送方时，非应答信号。
////////////////////////////////////////////////////////////////////////////
void SendNotAck(void)
{
    SDA=1; 
    FourNOPs();
    SCL=1; 
    FourNOPs();
    SCL=0;
}
////////////////////////////////////////////////////////////////////////////
//调用方式：void I2CSendByte(uchar ch) 
//函数说明：私有函数，I2C专用
////////////////////////////////////////////////////////////////////////////
 void I2CSendByte(Byte ch)
{
    uchar i=8;
    while (i--)
    {
        SCL=0;_nop_();
        SDA=(bit)(ch&0x80); 
        ch<<=1; 
        FourNOPs();
        SCL=1; 
        FourNOPs();
    }
    SCL=0;
 }

////////////////////////////////////////////////////////////////////////////
// 调用方式：uchar I2CReceiveByte(void) 
// 函数说明：私有函数，I2C专用
////////////////////////////////////////////////////////////////////////////
 Byte I2CReceiveByte(void)
 {
    uchar i=8;
    Byte ddata=0;
    SDA=1;
    while (i--)
    {
        ddata<<=1;
        SCL=0;
        FourNOPs();
        SCL=1;
        FourNOPs();
        ddata|=SDA;
    }
    SCL=0;
    return ddata;
 }