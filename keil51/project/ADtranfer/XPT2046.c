#include <REGX52.H>

sbit XPT2046_CS=P3^5;
sbit XPT2046_DCLK=P3^6;
sbit XPT2046_DIN=P3^4;
sbit XPT2046_DOUT=P3^7;

unsigned int READ(unsigned char command)//����ʱ��ͼ����
{
	int i;
	unsigned int value;
	XPT2046_CS=0;
	XPT2046_DCLK=0;
	for(i=0;i<8;i++)
	{
	XPT2046_DIN=command&(0x80>>i);//��λ����
	
	XPT2046_DCLK=1;//���޸�λ����
	//ע��ʱ��,ns������
	XPT2046_DCLK=0;
	}
	for(i=0;i<16;i++)
	{
	XPT2046_DCLK=1;//���޸�λ����
	//ע��ʱ��,ns������
	XPT2046_DCLK=0;
		if(XPT2046_DOUT){value|=(0x8000>>i);}//��16λ
	}
	XPT2046_DCLK=1;//����ʱ��
	if(command&0x08)
	return value>>8;//����8λ����Ϊ�˾�ȷ����16λ�����ƻ�ȥ��0-255
	else
	return value>>4;//����12λ��0-4096
}

