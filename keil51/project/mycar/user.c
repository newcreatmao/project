#include <REGX52.H>
#include"delay.h"
#include"HEAD.h"
unsigned char Key_KeyNumber;
extern unsigned char pwmfl,pwmfg,pwmbl,pwmbg,basic1;
unsigned char distance;


void timer()		//100΢��@11.0592MHz
{
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0xA4;		//���ö�ʱ��ʼֵ
	TH0 = 0xFF;		
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	
	ET0=1;			//1����ʱ���ж�
	EA=1;			//�������ж�
	PT0=0;			//�ж����ȼ�
}

void uart()
{
	PCON |= 0x80;		//�����ʱ���
	SCON = 0x40;		//8λ����,�ɱ䲨����,�������
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	TL1 = 0xF3;		//���ö�ʱ��ʼֵ
	TH1 = 0xF3;		//���ö�ʱ����ֵ
	ET1 = 0;		//��ֹ��ʱ��ET�жϣ������жϽ��ջ��������
	TR1 = 1;		//��ʱ��1��ʼ��ʱ
}

void sendbyte(unsigned char byte)
{
	SBUF=byte;//SBUF���ݽ�����
	while(TI==0);//TI���ͱ�־λ��0Ϊ�ȴ��������ݣ�1Ϊ�������
	TI=0;
}





/**
  * @brief  ��ȡ��������
  * @param  ��
  * @retval ���°����ļ��룬��Χ��0,1~4,0��ʾ�ް�������
  */
unsigned char Keyreturn(void)
{
	unsigned char Temp=0;
	Temp=Key_KeyNumber;
	Key_KeyNumber=0;
	return Temp;
}

/**
  * @brief  ��ȡ��ǰ������״̬�������������ּ��
  * @param  ��
  * @retval ���°����ļ��룬��Χ��0,1~4,0��ʾ�ް�������
  */
unsigned char Key_GetState()
{
	unsigned char KeyNumber=0;
	
	if(key1==0){KeyNumber=1;}
	if(key2==0){KeyNumber=2;}
	if(key3==0){KeyNumber=3;}
	if(key4==0){KeyNumber=4;}
	
	return KeyNumber;
}

/**
  * @brief  �����������������ж��е���
  * @param  ��
  * @retval ��
  */
void Key_Loop(void)
{
	static unsigned char NowState,LastState;
	LastState=NowState;				//����״̬����
	NowState=Key_GetState();		//��ȡ��ǰ����״̬
	//����ϸ�ʱ��㰴�����£����ʱ���δ���£���������˲�䣬�Դ˱������������ּ��
	if(LastState==1 && NowState==0)
	{
		Key_KeyNumber=1;
	}
	if(LastState==2 && NowState==0)
	{
		Key_KeyNumber=2;
	}
	if(LastState==3 && NowState==0)
	{
		Key_KeyNumber=3;
	}
	if(LastState==4 && NowState==0)
	{
		Key_KeyNumber=4;
	}
}


unsigned char red()
{
	TMOD |= 0x11;//���ö�ʱ��ģʽ
	TL1 = 0;//���ö�ʱ����ʼֵ
	TH1 = 0;//���ö�ʱ����ʼֵ
	
	TRIG = 1;
	delayus(20);//����һ�����壬����20us
	TRIG = 0;
	
	while(!ECHO);//�ȴ�������ģ�鷵������
	TR1=1;//�򿪶�ʱ��
	while(ECHO);//�ȴ���������ʱ�������������
	TR1 = 0;//ֹͣ����������ʱ����
	
	distance=((TH1*256+TL1)*0.034)/2+1;//�������,��ʱ��1�ļ�������12tΪ1usһ������������ʱ��Ϊ��ô��
	
	return distance;
}

void forward()
{
	blf=1;
	blb=0;
	bgf=1;
	bgb=0;
	flf=1;
	flb=0;
	fgf=1;
	fgb=0;
}

void backward()
{
	blf=0;
	blb=1;
	bgf=0;
	bgb=1;
	flf=0;
	flb=1;
	fgf=0;
	fgb=1;
}

void stop()
{
	blf=0;
	blb=0;
	bgf=0;
	bgb=0;
	flf=0;
	flb=0;
	fgf=0;
	fgb=0;
}

void reward()
{pwmfl=pwmfg=pwmbl=pwmbg=basic1;}

void tlf()//��ǰת
{
	forward();
	pwmfl=255;
	pwmbl=255;
	pwmbg=100;
	pwmfg=pwmbg+20;

}

void tgf()
{
	forward();
	pwmfg=255;
	pwmbg=255;
	pwmbl=100;
	pwmfl=pwmbl+20;

}

void tlb()
{
	backward();
	pwmfl=255;
	pwmbl=255;
	pwmfg=100;
	pwmbg=pwmfg+20;

}

void tgb()
{
	backward();
	pwmfg=255;
	pwmbg=255;
	pwmbl=100;
	pwmfl=pwmbl+20;

}
void look_road()
{
	if(clx){tgf();}
	if(crx){tlf();}
	if(mlx&&clx){tgf();}
	if(mrx&&crx){tlf();}
	if(clx==0&&crx==0&&mlx==0&&mrx==0){reward();}
}