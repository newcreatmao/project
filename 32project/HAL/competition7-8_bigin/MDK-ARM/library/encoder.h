#ifndef _ENCODER_H_
#define _ENCODER_H_
#include "stm32f4xx.h"
#include "tim.h"
#include "main.h"
////���1�ı�������������
#define MOTO1_ENCODER1_PORT GPIOA
#define MOTO1_ENCODER1_PIN  GPIO_PIN_0
#define MOTO1_ENCODER2_PORT GPIOA
#define MOTO1_ENCODER2_PIN  GPIO_PIN_1


////���2�ı�������������
#define MOTO2_ENCODER1_PORT GPIOA
#define MOTO2_ENCODER1_PIN  GPIO_PIN_6
#define MOTO2_ENCODER2_PORT GPIOA
#define MOTO2_ENCODER2_PIN  GPIO_PIN_7

////��ʱ����
#define ENCODER_TIM htim2
#define PWM_TIM     htim3
#define GAP_TIM     htim5

#define MOTOR_SPEED_RERATIO 30u    //������ٱ�
#define PULSE_PRE_ROUND 500 //һȦ���ٸ�����
#define RADIUS_OF_TYRE 88 //��̥�뾶����λ����
#define LINE_SPEED_C RADIUS_OF_TYRE * 2 * 3.14
#define RELOADVALUE __HAL_TIM_GetAutoreload(&ENCODER_TIM)    //��ȡ�Զ�װ��ֵ,������Ϊ20000
#define COUNTERNUM __HAL_TIM_GetCounter(&ENCODER_TIM)        //��ȡ��������ʱ���еļ���ֵ

typedef struct _Motor
{
    int32_t lastCount;   //��һ�μ���ֵ
    int32_t totalCount;  //�ܼ���ֵ
    int16_t overflowNum; //�������
    float speed;         //���ת��
    uint8_t direct;      //��ת����
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
