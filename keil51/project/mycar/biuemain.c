//#include <REGX52.H>
//#include"HEAD.h"
//#include"user.h"
//unsigned char pwmfl=180,pwmfg=180,pwmbl=180,pwmbg=180,basic1=180;
//unsigned char pwm_t=0;
//unsigned char redata;//���յĵ����ݱ���
//void receive(unsigned char num)
//{
//	switch(num)
//	{
//		case '1':
//			forward();
//			break;
//		case '2':
//			backward();
//			break;
//		case '3':
//			tlf();
//			break;
//		case '4':
//			tgb();
//			break;
//		case '5':
//			tlb();
//			break;
//		case '6':
//			tgf();
//			break;
//		case '7':
//			basic1+=5;
//			reward();
//			break;
//		case '8':
//			basic1-=5;
//			reward();
//			break;
//		case '9':
//			look_road();
//			break;
//	}
//}
//void Uart_Init()//9600bps@11.0592
//{
//	PCON=0x00;//�ر�Ƶ
//	SCON=0x50;//8λ���ݣ��ɱ䲨����
//	TMOD &= 0x0F;	//���ö�ʱ��ģʽ
//	TMOD |= 0x20;
//	TL1=0xFD;//���ö�ʱ��ʼֵ
//	TH1=0xFD;
//	//��ֹ��ʱ��1�ж�
//  ET1=0;
//	//��ʱ��1��ʼ��ʱ
//	TR1=1;
//	EA=1;//���ж�
//	ES=1;//�򿪴����ж�
//}

//void main()
//{
//	timer();
//	Uart_Init();
//	while(1);
//}
//	
//void Uart_Routine() interrupt 4
//{
//	stop();
//	RI=0;//����жϱ�־λ
//	redata=SBUF;//
//	receive(redata);
//}	
//void pwm() interrupt 1
//{
//		TL0 = 0xA4;		//���ö�ʱ��ʼֵ
//	  TH0 = 0xFF;	
//	  pwm_t++;
//		if(pwm_t==255)  {pwm_t=efl=efg=ebl=ebg=0;}
//		if(pwm_t==pwmfl){efl=1;}
//		if(pwm_t==pwmfg){efg=1;}
//		if(pwm_t==pwmbl){ebl=1;}
//		if(pwm_t==pwmbg){ebg=1;}
//}