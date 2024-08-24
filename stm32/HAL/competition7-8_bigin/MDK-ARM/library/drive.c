#include "drive.h"

/*
PE13			left 
PE14

PC7			right
PC8

*/
void Drive_Init(void)
{	
		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
	
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,0);//+
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);
	
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);//+
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,0);
}


void L_speed(int16_t L_speed)
{
	if(L_speed>=0){
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,L_speed);//+
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,0);}
	
  if(L_speed<0){
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_4,0);
		__HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_3,-L_speed);}
}

void R_speed(int16_t R_speed)
{
	if(R_speed>0){
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,R_speed);//+
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,0);}
								
	
  if(R_speed<0){
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_3,0);
		__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_2,-R_speed);}
}

