#ifndef __MOTOR_H
#define __MOTOR_H

#include<stm32f10x.h>
void ENA_PWMInit();
void Motor_Init();
void PWMCCR(uint16_t CCR);//修改占空比，注：占空比是ccr与arr共同确定的
void PWMPSC(uint16_t PSC);
void moto(int i,int j);

#endif