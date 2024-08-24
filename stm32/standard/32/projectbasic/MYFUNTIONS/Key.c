#include "Key.h"
void KEY_INITB(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStruct);
}
void KEY_INITA(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
}
uint8_t KEY_GETNUM()
{
	int keynum=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)==0);
		Delay_ms(20);
		keynum=1;
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)==0);
		Delay_ms(20);
		keynum=2;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_10)==0);
		Delay_ms(20);
		keynum=3;
	}
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)==0);
		Delay_ms(20);
		keynum=4;
	}
	return keynum;
}
