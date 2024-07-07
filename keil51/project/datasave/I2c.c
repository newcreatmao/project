//����ģ��
#include <REGX52.H>
sbit SCL = P2^1;
sbit SDA = P2^0;
//��д������Ҫ5ms�⣬����Ĳ���ʱ�䶼�̣ܶ�����51����Ҫ��ʱ

//��ʼ
void start()
{
	SCL=SDA=1;//ȷ��SDA��SCLΪ�ߣ��൱�ڳ�ʼ��
	SDA=0;
	SCL=0;//ע��Ҫ��ʱ��ͼ��˳��
}

//ֹͣ
void stop()
{
	SDA=0;
	SCL=1;
	SDA=1;
}

//����һ��bit
void sendbyte(unsigned char byte)
{
	int i;
	for(i=0;i<8;i++)
	{
	SDA=byte&(0x80>>i)://ȡ���λ
	SCL=1;
	SDA=0;
	}
}

//����һ��bit
unsigned char receivebyte()
{
	unsigned char byte=0x00,i;//��ʼ��byte���ܽ�������sda�ж�
	
	SDA=1;//�ͷ����ߣ����ôӻ��������ߣ�Ҫ���ӻ�����Ķ���0��������Ƶ���Ҫ������
	for(i=0;i<8;i++)
	{
		//��������������Ǵ�sda�϶�
	SCL=1;//scl���ߺ�sda��ֵ��Ϊ���ݵ����λ��ÿ��scl���ߣ�sda���ն�Ӧλ�õ�����
	if(SDA){byte|=(0x80>>i);}//SDA���ص����������Ҳ��010101�ģ���ֻ��Ҫ�ж�sdaֵ�Ϳɽ�һ��byte��ֵ������գ���1��λ��1
	//������Ҫ��ȡ�ӻ����ص����ݣ��ӻ����ڿ���sda��������Ҫ��sda��״̬д��byte�У�������ȡbyte����ֱ���ӻ����ص�ֵ��
	SCL=0;
	return byte;
	}
}

//����Ӧ��
void endack(unsigned char ack)
{
	SDA=ack;
	SCL=1;
	SCL=0;
}

//����Ӧ��
unsigned char receiveack()
{
	unsigned char ackbit;
	SDA=1;
	SCL=1;
	if(SDA)ackbit=1;
	SCL=0;
	return ackbit;//0ΪӦ��1Ϊ��Ӧ��
}