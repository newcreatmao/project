#ifndef _ENCODER_H_
#define _ENCODER_H_
  #include "all_head.h"
	
	#define L_TIM htim1
	#define R_TIM htim2
	#define GAP_TIM htim4
	#define MOTOR_SPEED_RERATIO 34       //电机减速比
	#define PULSE_PRE_ROUND 500           //编码器线数
	#define RADIUS_OF_TYRE 32            //轮胎半径，单位毫米
	#define LINE_SPEED_C RADIUS_OF_TYRE * 2 * 3.14
	#define RELOADVALUE __HAL_TIM_GetAutoreload(&L_TIM)    //获取自动装载值
	#define COUNTERNUM1 __HAL_TIM_GetCounter(&L_TIM)        //获取编码器定时器中的计数值
	#define COUNTERNUM2 __HAL_TIM_GetCounter(&R_TIM)        //获取编码器定时器中的计数值
	#define ALPHA 0.25
	
	typedef struct _Motor{
			int32_t lastCount;   //上一次计数值
			int32_t totalCount;  //总计数值
			int32_t overflowNum; //溢出次数
			float speed;         //电机转速
			uint8_t direct;      //旋转方向
	}Motor;
	
	extern Motor motor_L,motor_R;
	void Encoder_Init(void);
	float applyEMAFilter(float new_Spe,float pre_Spe);
	void OLED_showLSpeed(uint8_t x,uint8_t y);
	void OLED_showRSpeed(uint8_t x,uint8_t y);
#endif
