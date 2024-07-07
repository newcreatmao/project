#ifndef __PCF8563_H__		//防止头文件被重复编译
#define __PCF8563_H__

#include <reg52.h>
#include <intrins.h>
sbit bee=P3^0;
uchar xx=0;

void been()
{
	bee=~bee;	
	mDelay(500);
}


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

 void time_display(uchar ff) 	//液晶时间显示
 {

     uchar con[7],date[10],time[8],time0[8];
     GetPCF8563(0x02,7,con);
     date[2]=(con[6]>>4)&0x0f;
     date[3]=(con[6]&0x0f);         //年
     date[5]=((con[5]>>4)&0x01);
     date[6]=(con[5]&0x0f);         //月
     date[8]=((con[3]>>4)&0x03);
     date[9]=(con[3]&0x0f);         //日


     time[0]=((con[2]>>4)&0x03) ;
     time[1]=(con[2]&0x0f) ;
     time[3]=(con[1]>>4) ;
     time[4]=((con[1]&0x0f)&0x07) ;
     time[6]=(con[0]>>4) ;
     time[7]=(con[0]&0x0f) ;


     time0[0]=(tt[2]>>4) ;
     time0[1]=(tt[2]&0x0f) ;
     time0[2]=(tt[1]>>4) ;
     time0[3]=(tt[1]&0x0f) ;
     time0[4]=(tt[0]>>4) ;
     time0[5]=(tt[0]&0x0f); 

	if(tt[0]==con[0]&&tt[1]==con[1]&&tt[2]==con[2])
		xx=1;
	if(xx)
	 been();
	 if(ff==0)
 	 	display(date,time);
	 if(ff==1)
 	 	display1(date);
	 if(ff==2)
 	 	display2(time);
	 if(ff==3)
 	 	display3(time0);
}

#endif










