#include <REGX51.H>
#define uchar unsigned char 	//�궨�壬Ϊ������
#define uint unsigned int
#define DIGI P0 				//�궨�壬��P0�ڶ���Ϊ����ܶ�ѡ�ӿ�
#define SELECT P2 				//�궨�壬��P2����Ϊ�����ѡ���
uchar mod=0;
uchar chage;
uchar digivalue[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7f,0x6f,0x80};
//��ʾ���������飬����Ϊ0��1��..��7
uchar select[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; //ѡ����������飬����ѡ��1��2��..��8

uchar date[]={2,0,2,4,0,5,3,0};
uchar time[8];
uchar haomiao=0,second=0,min=0,t=0;

void delay() //�ӳٺ������������������ļ��ʱ��
{ 
	uchar ii=200; //�������������˸���������Ｔ��
	while(ii--);
}

void Timer0_Init(void)		//1??@12.000MHz
{
	TMOD &= 0xF0;			//???????
	TMOD |= 0x01;			//???????
	TL0 = 0x18;				//???????
	TH0 = 0xFC;				//???????
	TF0 = 1;				
	TR0 = 1;
}

void key_init(){
	IE=0x85;
	PX1=1;
	IT0 = 1;		//�ⲿ�ж�0�����崥����ʽ���½��ش������
	IT1 = 1;
}

main() //������
{
	uchar i=0;
	Timer0_Init();
	key_init();
	EA=1;
  while(1)
	{ 
		if(mod==1){
			for(i=0;i<8;i++) 		//8�������������ʾ
			{
				SELECT=select[i]; 	//ѡ���i�������
				DIGI=0x90;
				DIGI=digivalue[date[i]]; 	//��ʾi
				delay(); 
			}
		}
		else{
			ET0=1;
			time[0]=min/10;time[1]=min%10;time[2]=10;
			time[3]=second/10;time[4]=second%10;time[5]=10;
			time[6]=haomiao/10;time[7]=haomiao%10;
			for(i=0;i<8;i++) 		//8�������������ʾ
			{
				SELECT=select[i]; 	//ѡ���i�������
				DIGI=0x90;
				DIGI=digivalue[time[i]]; 	//��ʾi
				delay(); 
			}
		}
	}
}

void clock() interrupt 1
{
	t++;
	if(t>=10){
	haomiao++;
	if(haomiao==100){	haomiao=0;second++;}
	if(second==60){second=0;min++;}
	if(min==60){min=0;second=0;}
	t=0;
	}
	TL0 = 0x18;				//???????
	TH0 = 0xFC;				//???????
}

void INIT_0(void) interrupt 0
{
	uchar i=0;
	while(1){
		SELECT=select[0]; 	//ѡ���i�������
		DIGI=0x90;
		DIGI=digivalue[mod]; 	//��ʾi
		delay(); 
		if(P3_4==0){
			delay();
			if(P3_4==0){
				while(P3_4==0);
				break;
			}
		}
		if(P3_5==0){
			delay();
			if(P3_5==0){
				mod=(mod+1)%2;
				while(P3_5==0);
			}
		}
	}
}

void INIT_1(void) interrupt 2
{
	uchar i=0;
	while(1){
		time[0]=min/10;time[1]=min%10;time[2]=10;
		time[3]=second/10;time[4]=second%10;time[5]=10;
		time[6]=haomiao/10;time[7]=haomiao%10;
		for(i=0;i<8;i++) 		//8�������������ʾ
		{
				SELECT=select[i]; 	//ѡ���i�������
				DIGI=0x90;
				DIGI=digivalue[time[i]]; 	//��ʾi
				delay(); 
		}
		if(P3_6==0){
			delay();
			if(P3_6==0){
				while(P3_6==0);
				break;
			}
		}
		if(P3_7==0){
			delay();
			if(P3_7==0){
				chage=(chage+1)%3;
				SELECT=select[0]; 	//ѡ���i�������
				DIGI=0x90;
				DIGI=digivalue[chage]; 	//��ʾi
				delay(); 
				while(P3_7==0);
			}
		}
		if(P3_0==0){
			delay();
			if(P3_0==0){
				switch(chage){
					case 0: haomiao++;break;
					case 1: second++;break;
					case 2: min++;break;
				}
				while(P3_0==0);
			}
		}
		if(P3_1==0){
			delay();
			if(P3_1==0){
				switch(chage){
					case 0: haomiao--;break;
					case 1: second--;break;
					case 2: min--;break;
				}
				while(P3_1==0);
			}
		}		
	}
}

