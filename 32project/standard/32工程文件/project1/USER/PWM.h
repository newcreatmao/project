#ifndef __PWM_H
#define __PWM_H
void  PWM_init();
void PWMCCR(uint16_t CCR);
void angle(int num);
void PWMPSC(uint16_t PSC);
#endif