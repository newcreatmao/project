#ifndef __PCF8563_H__		//��ֹͷ�ļ����ظ�����
#define __PCF8563_H__

#include <STC8A.h>
#include <intrins.h>

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

 void time_display(uchar x0,uchar y0) 	//Һ��ʱ����ʾ
 {
     uchar date[]="2000.00.00";
     uchar time[]="00:00:00";
     uchar con[7];
     int i,j;
     GetPCF8563(0x02,7,con);
     date[2]=(con[6]>>4)+'0';
     date[3]=(con[6]&0x0f)+'0';         //��
     date[5]=((con[5]>>4)&0x01)+'0';
     date[6]=(con[5]&0x0f)+'0';         //��
     date[8]=((con[3]>>4)&0x03)+'0';
     date[9]=(con[3]&0x0f)+'0';         //��


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