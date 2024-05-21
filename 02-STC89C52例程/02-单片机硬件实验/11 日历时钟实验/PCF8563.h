#ifndef __PCF8563_H__		//防止头文件被重复编译
#define __PCF8563_H__

#include <STC8A.h>
#include <intrins.h>

////////////////////////////////////////////////////////////////////////////
// 调用方式：void GetPCF8563(uchar firsttype,uchar count,uchar *buff) 
// 函数说明：读取时钟芯片PCF8563的时间，设置要读的第一个时间类型firsttype，
// 并设置读取的字节数，则会一次把时间读取到buff中。
// 顺序是： 0x02:秒/0x03:分/0x04:小时/0x05:日/0x06:星期/0x07:月(世纪)/0x08:年
////////////////////////////////////////////////////////////////////////////
 void GetPCF8563(uchar firsttype,uchar count,uchar *buff)
 {
     uchar i;
     I2CStart();
     I2CSendByte(0xA2);
     WaitAck();
     I2CSendByte(firsttype);
     WaitAck();
     I2CStart();
     I2CSendByte(0xA3);
     WaitAck();

     for (i=0;i<count;i++)
     {
         buff[i]=I2CReceiveByte();
         if (i!=count-1) SendAck();//除最后一个字节外，其他都要从MASTER发应答。
     }

     SendNotAck();
     I2CStop();
     }

////////////////////////////////////////////////////////////////////////////
//调用方式：void SetPCF8563(uchar timetype,uchar value) 
//函数说明：调整时钟。timetype是要改的时间类型，value是新设置的时间值(BCD格式)。
//0x02:秒/0x03:分/0x04:小时/0x05:日/0x06:星期/0x07:月(世纪)/0x08:年
////////////////////////////////////////////////////////////////////////////
 void SetPCF8563(uchar timetype,uchar value)
 {
     I2CStart();
     I2CSendByte(0xA2);
     WaitAck();
     I2CSendByte(timetype);
     WaitAck();
     I2CSendByte(value);
     WaitAck();
     I2CStop();
 }

////////////////////////////////////////////////////////////////////////////
//调用方式：void time_display(uchar x0,uchar y0 )
//函数说明：time_display()在指定的x0,y0坐标，以00:00:00格式显示当前时间。
////////////////////////////////////////////////////////////////////////////
//uchar time[]="00:11:11";

 void time_display(uchar x0,uchar y0) 	//液晶时间显示
 {
     uchar date[]="2000.00.00";
     uchar time[]="00:00:00";
     uchar con[7];
     int i,j;
     GetPCF8563(0x02,7,con);
     date[2]=(con[6]>>4)+'0';
     date[3]=(con[6]&0x0f)+'0';         //年
     date[5]=((con[5]>>4)&0x01)+'0';
     date[6]=(con[5]&0x0f)+'0';         //月
     date[8]=((con[3]>>4)&0x03)+'0';
     date[9]=(con[3]&0x0f)+'0';         //日


     time[0]=((con[2]>>4)&0x03)+'0';
     time[1]=(con[2]&0x0f)+'0';
     time[3]=(con[1]>>4)+'0';
     time[4]=((con[1]&0x0f)&0x07)+'0';
     time[6]=(con[0]>>4)+'0';
     time[7]=(con[0]&0x0f)+'0';
     for(i=0;i<10;i++)
     DisplayOneChar(x0+i,0,date[i]);
     for(j=0;j<8;j++)
     DisplayOneChar(x0+j,1,time[j]);
}