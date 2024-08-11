#ifndef _ENCODER_H_
#define _ENCODER_H_
#include "stm32f4xx.h"
#include "tim.h"
#include "main.h"
////电机1的编码器输入引脚
#define MOTO1_ENCODER1_PORT GPIOA
#define MOTO1_ENCODER1_PIN  GPIO_PIN_0
#define MOTO1_ENCODER2_PORT GPIOA
#define MOTO1_ENCODER2_PIN  GPIO_PIN_1


////电机2的编码器输入引脚
#define MOTO2_ENCODER1_PORT GPIOA
#define MOTO2_ENCODER1_PIN  GPIO_PIN_6
#define MOTO2_ENCODER2_PORT GPIOA
#define MOTO2_ENCODER2_PIN  GPIO_PIN_7

////定时器号
#define ENCODER_TIM htim2
#define PWM_TIM     htim3
#define GAP_TIM     htim5

#define MOTOR_SPEED_RERATIO 30u    //电机减速比
#define PULSE_PRE_ROUND 500 //一圈多少个脉冲
#define RADIUS_OF_TYRE 88 //轮胎半径，单位毫米
#define LINE_SPEED_C RADIUS_OF_TYRE * 2 * 3.14
#define RELOADVALUE __HAL_TIM_GetAutoreload(&ENCODER_TIM)    //获取自动装载值,本例中为20000
#define COUNTERNUM __HAL_TIM_GetCounter(&ENCODER_TIM)        //获取编码器定时器中的计数值

typedef struct _Motor
{
    int32_t lastCount;   //上一次计数值
    int32_t totalCount;  //总计数值
    int16_t overflowNum; //溢出次数
    float speed;         //电机转速
    uint8_t direct;      //旋转方向
}Motor;


extern int l,r;

void Encoder_Init(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

//void Motor_Init(void);
////uint16_t getTIMx_DetaCnt(TIM_TypeDef * TIMx);
//void Get_Motor_Speed(int *leftSpeed,int *rightSpeed);
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
//int getTIMx_DetaCnt(TIM_HandleTypeDef *htim);
//void Get_Motor_Speed(int *leftSpeed, int *rightSpeed);
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif
