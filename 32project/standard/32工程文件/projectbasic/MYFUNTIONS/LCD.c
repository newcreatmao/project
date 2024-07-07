#include<stm32f10x.h>
void LCD_Init(){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode= GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStruct);
}

void LCD_light(){
    GPIO_ResetBits(GPIOA,GPIO_Pin_1);
}

void LCD_off(){
    GPIO_SetBits(GPIOA,GPIO_Pin_1);
}