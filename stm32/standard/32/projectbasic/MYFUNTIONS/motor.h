#ifndef __MOTOR_H
#define __MOTOR_H

#include<stm32f10x.h>
void ENA_PWMInit();
void Motor_Init();
void PWMCCR(uint16_t CCR);//�޸�ռ�ձȣ�ע��ռ�ձ���ccr��arr��ͬȷ����
void PWMPSC(uint16_t PSC);
void moto(int i,int j);

#endif