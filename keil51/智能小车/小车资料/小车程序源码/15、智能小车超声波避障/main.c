/*
* ����дʱ�䡿�� 2016��12��9��
* ����    �ߡ��� �������:03
* ����    ������ 1.6
* ����    վ���� http://www.qxmcu.com/ 
* ���Ա����̡��� http://qxmcu.taobao.com/ (ֱ����)
* ��ʵ��ƽ̨���� QX-MCS51 ��Ƭ�������� & QX-A51����С��
* ���ⲿ���񡿣� 11.0592mhz	
* ������оƬ���� STC89C52
* �����뻷������ Keil ��Visio4
* ********************************������˵����********************************
             ����"A_"��ʾ����С���װ�~~~"B_"��ʾ������     
*�����幩����  ��A_J5-VCC~~~B_VCC��5V0    A_J6-GND~~~B_GND ��һ��ʹ��2���Ű��ߣ�
*���������    ��A_J10-P1.2��P1.7 ��Ӧ�ӵ�B_P1.2��P1.7 ��һ��ʹ��6���Ű��ߣ�
*������ģ�鷴���ߣ�A_J2-P20~~~B_P20    A_J2-P21~~~B_P21 ��һ��ʹ��2���Ű��ߣ�
			ʹ��ǰ��������ȷ��ʽ���ϳ�����ģ����1602Һ��
******************************************************************************
* �������ܡ���QX-A51����С������������ʵ��		   			            			    
* ��ʹ��˵�����������������д����򿪵�Դ��������S2�����������������ʾ��1�������С��
* ��ע�����������С��ײ���ϰ����С�����Ӷ�ת��С����ѹ���ܵ���6V
				�˳���ֻ���ο���ʵ������Ч������ݲ�ͬʵ�鳡�ؽ��в�ͬ����
				ʹ��ǰ������1602Һ�������Һ��������ʾ�ַ�����˳ʱ�����Һ���Աȶȵ�λ����
				�����ʾ�ַ���Ũ������ʱ�����Һ���Աȶȵ�λ��
				���������������������������������������������
	�����������	���û��ʹ��1602Һ�������P07�ӵ�GND�ϣ������޷����С����������
				���������������������������������������������
**********************************************************************************/
#include <reg52.h> //51ͷ�ļ�
#include <intrins.h>   //����nop��ϵͳ����
#include <..\CONFIG\QXA51.h>//QX-A51����С�������ļ�

sbit DU = P2^6;//����ܶ�ѡ
sbit RX = P2^0;//ECHO������ģ������
sbit TX = P2^1;//TRIG������ģ�鴥����
sbit LCM_RW = P3^6;     //����LCD����
sbit LCM_RS = P3^5;
sbit LCM_E = P3^4;
#define LCM_Data  P0   //����Һ�������ݿ�
#define Busy    0x80   //���ڼ��LCM״̬���е�Busy��ʶ

unsigned char pwm_left_val = 100;//����ռ�ձ�ֵ ȡֵ��Χ0-170��0���
unsigned char pwm_right_val = 110;//�ҵ��ռ�ձ�ֵȡֵ��Χ0-170 ,0���
unsigned char pwm_t;//����
unsigned int  time = 0;//����ʱ��
unsigned long S = 0;//����
bit      flag = 0;//����������Χ��־λ

unsigned char code Range[] ="==Range Finder==";//LCD1602��ʾ��ʽ
unsigned char code ASCII[13] = "0123456789.-M";
unsigned char code table[]="Distance:000.0cm";
unsigned char code table1[]="!!! Out of range";
unsigned char disbuff[4] = { 0,0,0,0};//������ʾ����

void delay(unsigned int z)//���뼶��ʱ
{
	unsigned int x,y;
	for(x = z; x > 0; x--)
		for(y = 114; y > 0 ; y--);
}

void Delay10us(unsigned char i)    	//10us��ʱ���� ����������ģ��ʱʹ��
{ 
   unsigned char j; 
	do{ 
		j = 10; 
		do{ 
			_nop_(); 
		}while(--j); 
	}while(--i); 
}
 
void cmg88()//�������������
{
    DU=1;  	  
    P0=0X00;//������������������͵�ƽ��ȫ��Ϩ��
    DU=0;
} 

/************************************LCD1602Һ������������************************************************/
//*******************��״̬*************************//
unsigned char ReadStatusLCM(void)
{
	LCM_Data = 0xFF; 
	LCM_RS = 0;
	Delay10us(1); 
	LCM_RW = 1;
	Delay10us(1); 
	do{
	LCM_E = 0;
	Delay10us(1); 
	LCM_E = 0;
	Delay10us(1); 
	LCM_E = 1;
	Delay10us(1); 
	}
	while (LCM_Data & Busy); //���æ�ź�
	return(LCM_Data);
}

/****************д����************************/
void WriteDataLCM(unsigned char WDLCM) 
{
	ReadStatusLCM(); //���æ
	LCM_Data = WDLCM;
	LCM_RS = 1;
	Delay10us(1); 
	LCM_RW = 0;
	Delay10us(1); 
	LCM_E = 0; //�������ٶ�̫�߿���������С����ʱ
	Delay10us(1); 
	LCM_E = 0; //��ʱ
	Delay10us(1); 
	LCM_E = 1;
	Delay10us(1); 
}

//****************дָ��*************************//
void WriteCommandLCM(unsigned char WCLCM,BuysC) //BuysCΪ0ʱ����æ���
{
	if (BuysC) ReadStatusLCM(); //������Ҫ���æ
	LCM_Data = WCLCM;
	LCM_RS = 0;
	Delay10us(1); 
	LCM_RW = 0;	
	Delay10us(1); 
	LCM_E = 0;
	Delay10us(1); 
	LCM_E = 0;
	Delay10us(1); 
	LCM_E = 1;
	Delay10us(1); 
}



//*******************LCM��ʼ��**********************//
void LCMInit(void) 
{
	LCM_Data = 0;
	WriteCommandLCM(0x38,0); //������ʾģʽ���ã������æ�ź�
	delay(5); 
	WriteCommandLCM(0x38,0);
	delay(5); 
	WriteCommandLCM(0x38,0);
	delay(5); 

	WriteCommandLCM(0x38,1); //��ʾģʽ����,��ʼҪ��ÿ�μ��æ�ź�
	WriteCommandLCM(0x08,1); //�ر���ʾ
	WriteCommandLCM(0x01,1); //��ʾ����
	WriteCommandLCM(0x06,1); // ��ʾ����ƶ�����
	WriteCommandLCM(0x0c,1); // ��ʾ�����������
}

//*********************��ָ��λ����ʾһ���ַ�***********************//
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData)
{
	Y &= 0x1;
	X &= 0xF; //����X���ܴ���15��Y���ܴ���1
	if (Y) X |= 0x40; //��Ҫ��ʾ�ڶ���ʱ��ַ��+0x40;
	X |= 0x80; //���ָ����
	WriteCommandLCM(X, 1); //��������
	WriteDataLCM(DData); //������
}

//**********************��ָ��λ����ʾһ���ַ�*************************//
void DisplayListChar(unsigned char X, unsigned char Y, unsigned char code *DData)
{
	unsigned char ListLength;

  ListLength = 0;
	Y &= 0x1;
	X &= 0xF; //����X���ܴ���15��Y���ܴ���1
	while (DData[ListLength]>0x19) //�������ִ�β���˳�
		{
			if (X <= 0xF) //X����ӦС��0xF
				{
					DisplayOneChar(X, Y, DData[ListLength]); //��ʾ�����ַ�
					ListLength++;
					X++;
				}
		}
}


/***************************************************************************/

/*��ʱ��0�ж�*/
void timer0() interrupt 1	//T0�ж��������������,������෶Χ
{
	flag=1;							 //�ж������־			 
}
void  StartModule() 		         //����������ģ��
{
	  TX=1;			                     //����һ��ģ��
      Delay10us(2);
	  TX=0;
}
	
/*С��ǰ��*/
void forward()
{
	left_motor_go; //����ǰ��
	right_motor_go; //�ҵ��ǰ��
}

/*PWM����ʹ�� С������*/
void backward()
{
	left_motor_back; //��������
	right_motor_back; //�ҵ������	
}

/*С��ֹͣ*/
void stop()
{
	right_motor_stops;//�ҵ��ֹͣ
	left_motor_stops; //����ֹͣ	
}

/*PWM����ʹ�� С��������ת*/
void left_rapidly()
{
	left_motor_back;
	right_motor_go;	
}

/*��ʱ��1�ж����PWM�ź�*/
void timer1() interrupt 3
{
	pwm_t++;//���ڼ�ʱ��
	if(pwm_t == 255)
		pwm_t = EN1 = EN2 = 0;
	if(pwm_left_val == pwm_t)//����ռ�ձ�	
		EN1 = 1;		
	if(pwm_right_val == pwm_t)//�ҵ��ռ�ձ�
		EN2 = 1;			 
}
/*�ж�S2�Ƿ񱻰���*/
void keyscan()
{
	for(;;)	//��ѭ��
	{
		if(key_s2 == 0)// ʵʱ���S2�����Ƿ񱻰���
		{
			delay(5); //�������
			if(key_s2 == 0)//�ټ��S2�Ƿ񱻰���
			{
				while(!key_s2);//���ּ��
				beep = 0;	//ʹ����Դ������
				delay(200);//200������ʱ
				beep = 1;	//�ر���Դ������
				break;		//�˳�FOR��ѭ��
			}
		}
	}	
}

/*���㳬����������벢��ʾ*/
void Conut(void)
{
	time=TH0*256+TL0;
	TH0=0;
	TL0=0;
	
	S=(float)(time*1.085)*0.17;     //�������MM
	if((S>=7000)||flag==1) //����������Χ
	{	 
		flag=0;
		DisplayListChar(0, 1, table1);//1602��ʾ����table1
	}
	else
	{
		disbuff[0]=S/1000; //������ֵǧλ
		disbuff[1]=S%1000/100;//������ֵ��λ
		disbuff[2]=S%100/10;//������ֵʮλ
		disbuff[3]=S%10; //������ֵ��λ
	    DisplayListChar(0, 1, table); //��ʾ��Distance:000.0cm
	    DisplayOneChar(9, 1, ASCII[disbuff[0]]); //��ʾǧλ
	    DisplayOneChar(10, 1, ASCII[disbuff[1]]);	
	    DisplayOneChar(11, 1, ASCII[disbuff[2]]);
        DisplayOneChar(12, 1, ASCII[10]);		//��ʾ .	
	    DisplayOneChar(13, 1, ASCII[disbuff[3]]);
	}
}

/*����������*/
void	Avoid()
{
	if(S < 400)//���ñ��Ͼ��� ����λ����	ɲ������
	{
		beep = 0;//ʹ�ܷ�����
		stop();//ͣ��
		backward();//����
		delay(100);//����ʱ��Խ��������ԽԶ��������Ϊ����������ת��Ŀռ�
		do{
			left_rapidly();//������ת
			delay(90);//ʱ��Խ�� ת��Ƕ�Խ����ʵ����ʻ�����й�
			stop();//ͣ��
			delay(100);//ʱ��Խ�� ֹͣʱ��Խ�ó�

			StartModule();	//����ģ���࣬�ٴ��ж��Ƿ�
			while(!RX);		//��RX��ECHO�źŻ��죩Ϊ��ʱ�ȴ�
			TR0=1;			    //��������
			while(RX);			//��RXΪ1�������ȴ�
			TR0=0;				//�رռ���
			Conut();			//�������
			}while(S < 280);//�ж�ǰ���ϰ������
		beep = 1;//�رշ�����
	}
	else
	{
		forward();//ǰ��
	}	
}

void main()
{

	
	cmg88();//�������
	LCMInit(); //LCM��ʼ��
	delay(5);//��ʱƬ��

	DisplayListChar(0, 0, Range);//1602��һ����ʾRange��������
	DisplayListChar(0, 1, table);//1602�ڶ�����ʾtable��������
	keyscan();//�ȴ�����S2����С��
	delay(1000);//��ʱ1��
	TMOD |= 0x20;//��ʱ��1����ģʽ2,8λ�Զ���װ�����ڲ���PWM
	TMOD |= 0x01;//��ʱ��0����ģ��1,16λ��ʱģʽ��T0�ò�ECH0���峤��
	TH1 = 220; //
	TL1 = 220; //100HZ T1
	TH0	= 0;
    TL0	= 0;//T0,16λ��ʱ�������ڼ�¼ECHO�ߵ�ƽʱ��         
    ET1	= 1;//����T1�ж�
	ET0 = 1;//����T0�ж�
	TR1 = 1;//������ʱ��1
	EA  = 1;//�������ж�
	
	while(1)
	{
		 StartModule();	//����ģ����
		 while(!RX);		//��RX��ECHO�źŻ��죩Ϊ��ʱ�ȴ�
		 TR0=1;			    //��������
		 while(RX);			//��RXΪ1�������ȴ�
		 TR0=0;				//�رռ���
	     Conut();			//�������
		 Avoid();			//����
		 delay(65);			//�������ڲ�����60MS		  
	}
}