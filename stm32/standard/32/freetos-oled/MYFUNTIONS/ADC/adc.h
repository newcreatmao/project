#ifndef __ADC_H
#define __ADC_H
#include "sys.h"

#define gpio_readA  GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)  //读取GPIOA的P0口电平（0/1）
 
void Gpio_Init(void);         //延时初始化函数
int Gpio_read(void);        //读取A0口
int Get_Adc_Average(int channel,int count);
int Get_Adc(int ch);
void Adc_Init(void);
#endif
