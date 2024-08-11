#ifndef	_DRIVE__H
#define	_DRIVE__H


#include "tim.h"

void Drive_Init(void);
void L_speed(int16_t L_speed);
void R_speed(int16_t R_speed);
void Left_turn(void);
void Right_turn(void);
void car_go(void);
void car_stop(void);
#endif
