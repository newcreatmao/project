/***************************************************************************
实验名称： 外部中断实验

实验模块:  51单片机核心板、发光管、拨码开关、轻触开关区

实验接线： 51单片机核心板------发光管、拨码开关、轻触开关区

						P1---------J4	
						
						P3.2---------K1
						
现象描述：按动一下K1，LED按照二进制加的方式熄灭

更新时间：2017.10.17
***************************************************************************/


#include<reg52.h>	//添加库文件
#define uint unsigned int

void delay(int t){
	while(t--){
	unsigned char data i, j;
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
	}
}

void light_flout(){
	int i;
	for(i=0;i<8;i++){
		P1=(0x01<<i);
		delay(50);
	}
	for(i=7;i>-1;i--){
		P1=(0x01<<i);
		delay(50);
	}
}

void main(void)
{	
	IE=0x85;
	PX1=1;
	IT0 = 1;		//外部中断0，脉冲触发方式，下降沿触发有�
	IT1 = 1;
	while(1){
				light_flout();
	}
}

void INIT_0(void) interrupt 0
{
	int i=0;
	P1=0xFF;
	for(i=0;i<3;i++){
	P1=0x00;
	delay(50);
	P1=0xFF;
	delay(50);
	}
}

void INIT_1(void) interrupt 2
{
	int i=0;
	for(i=0;i<3;i++){
	P1=0x0F;
	delay(50);
	P1=0xF0;
	delay(50);
	}
}




