#ifndef __SEARCH_H
#define __SEARCH_H

#include<stm32f10x.h>
// void Encoder_Init_TIM_ExitA(void);//用于检测编码器A相使用PA8引脚

// void Encoder_Init_TIM_ExitB(void);//用于检测编码器B相使用PA9引脚

// uint16_t Get_AB();

// int Read_Encoder(u8 TIMX);//读取计数器的值

void BianA_init();
void BianB_init();
uint16_t ENcoderA();
uint16_t ENcoderB();

#endif