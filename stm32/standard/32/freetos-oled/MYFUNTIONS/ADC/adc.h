#ifndef __ADC_H
#define __ADC_H
#include "sys.h"

#define gpio_readA  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)  //��ȡGPIOA��P0�ڵ�ƽ��0/1��
 
void Gpio_Init(void);         //��ʱ��ʼ������
int Gpio_read(void);        //��ȡA0��
int Get_Adc_Average(int channel,int count);
int Get_Adc(int ch);
void Adc_Init(void);
#endif
