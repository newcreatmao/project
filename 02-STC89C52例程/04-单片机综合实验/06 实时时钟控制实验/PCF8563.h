#ifndef __PCF8563_H__		//��ֹͷ�ļ����ظ�����
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
// ���÷�ʽ��void GetPCF8563(uchar firsttype,uchar count,uchar *buff) 
// ����˵������ȡʱ��оƬPCF8563��ʱ�䣬����Ҫ���ĵ�һ��ʱ������firsttype��
// �����ö�ȡ���ֽ��������һ�ΰ�ʱ���ȡ��buff�С�
// ˳���ǣ� 0x02:��/0x03:��/0x04:Сʱ/0x05:��/0x06:����/0x07:��(����)/0x08:��
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
         if (i!=count-1) SendAck();//�����һ���ֽ��⣬������Ҫ��MASTER��Ӧ��
     }

     SendNotAck();
     I2CStop();
     }

////////////////////////////////////////////////////////////////////////////
//���÷�ʽ��void SetPCF8563(uchar timetype,uchar value) 
//����˵��������ʱ�ӡ�timetype��Ҫ�ĵ�ʱ�����ͣ�value�������õ�ʱ��ֵ(BCD��ʽ)��
//0x02:��/0x03:��/0x04:Сʱ/0x05:��/0x06:����/0x07:��(����)/0x08:��
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
//���÷�ʽ��void time_display(uchar x0,uchar y0 )
//����˵����time_display()��ָ����x0,y0���꣬��00:00:00��ʽ��ʾ��ǰʱ�䡣
////////////////////////////////////////////////////////////////////////////
//uchar time[]="00:11:11";

 void time_display(uchar ff) 	//Һ��ʱ����ʾ
 {

     uchar con[7],date[10],time[8],time0[8];
     GetPCF8563(0x02,7,con);
     date[2]=(con[6]>>4)&0x0f;
     date[3]=(con[6]&0x0f);         //��
     date[5]=((con[5]>>4)&0x01);
     date[6]=(con[5]&0x0f);         //��
     date[8]=((con[3]>>4)&0x03);
     date[9]=(con[3]&0x0f);         //��


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










