#ifndef __SEARCH_H
#define __SEARCH_H

#include<stm32f10x.h>
// void Encoder_Init_TIM_ExitA(void);//���ڼ�������A��ʹ��PA8����

// void Encoder_Init_TIM_ExitB(void);//���ڼ�������B��ʹ��PA9����

// uint16_t Get_AB();

// int Read_Encoder(u8 TIMX);//��ȡ��������ֵ

void BianA_init();
void BianB_init();
uint16_t ENcoderA();
uint16_t ENcoderB();

#endif