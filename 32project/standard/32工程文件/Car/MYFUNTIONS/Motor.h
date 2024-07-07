#ifndef __MOTOR_INIT_H__
#define __MOTOR_INIT_H__
#include "stm32f10x.h"
#include "stm32f10x_exti.h"

void TIM2_PWM_Init(u16 arr,u16 psc);
void MOTOR_GPIO_Config(void);

uint32_t read_cnt_TIM3(void);
uint32_t read_cnt_TIM4(void);

void encoder_Tim3_init(void);
void encoder_Tim4_init(void);

#endif
