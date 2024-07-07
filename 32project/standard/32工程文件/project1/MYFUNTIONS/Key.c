#include "stm32f10x.h"                  // Device header
#include"Delay.h"
void KEY_INIT(char select,int n,int m[])
{
	
	
	
	switch(select)
	{
		case 'A':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		break;
		case'B':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		break;
		case'C':
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		break;
	}
	int k;
	GPIO_InitTypeDef GPIO_InitStructre;
	GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;//上拉输入，读取按键
	for(k=0;k<n;k++)
	{
		switch(m[k])
		{
			case 0:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_0 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 1:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_1 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 2:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_2 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 3:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_3 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 4:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_4 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 5:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_5 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 6:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_6 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 7:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_7 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 8:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_8 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 9:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_9 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 10:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_10 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 11:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_11 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 12:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_12 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 13:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_13 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 14:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_14 | GPIO_InitStructre.GPIO_Pin;
			break;
			case 15:
				GPIO_InitStructre.GPIO_Pin= GPIO_Pin_15 | GPIO_InitStructre.GPIO_Pin;
			break;
		}
	
	}
	GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
	switch(select)
	{
		case 'A':
			GPIO_Init(GPIOA,&GPIO_InitStructre);
		break;
		case'B':
			GPIO_Init(GPIOB,&GPIO_InitStructre);
		break;
		case'C':
			GPIO_Init(GPIOC,&GPIO_InitStructre);
		break;
	}
}

uint8_t KEY_GETNUM()
{
	int keynum=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
		Delay_ms(20);
		keynum=1;
	}
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);//上拉输入，按键处强制为1，按下为0
		Delay_ms(20);
		keynum=2;
	}
	return keynum;
}

