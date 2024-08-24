#ifndef _ENCODER_H_
#define _ENCODER_H_
  #include "all_head.h"
	
	#define L_TIM htim1
	#define R_TIM htim2
	#define GAP_TIM htim4
	#define MOTOR_SPEED_RERATIO 34       //������ٱ�
	#define PULSE_PRE_ROUND 500           //����������
	#define RADIUS_OF_TYRE 32            //��̥�뾶����λ����
	#define LINE_SPEED_C RADIUS_OF_TYRE * 2 * 3.14
	#define RELOADVALUE __HAL_TIM_GetAutoreload(&L_TIM)    //��ȡ�Զ�װ��ֵ
	#define COUNTERNUM1 __HAL_TIM_GetCounter(&L_TIM)        //��ȡ��������ʱ���еļ���ֵ
	#define COUNTERNUM2 __HAL_TIM_GetCounter(&R_TIM)        //��ȡ��������ʱ���еļ���ֵ
	#define ALPHA 0.25
	
	typedef struct _Motor{
			int32_t lastCount;   //��һ�μ���ֵ
			int32_t totalCount;  //�ܼ���ֵ
			int32_t overflowNum; //�������
			float speed;         //���ת��
			uint8_t direct;      //��ת����
	}Motor;
	
	extern Motor motor_L,motor_R;
	void Encoder_Init(void);
	float applyEMAFilter(float new_Spe,float pre_Spe);
	void OLED_showLSpeed(uint8_t x,uint8_t y);
	void OLED_showRSpeed(uint8_t x,uint8_t y);
#endif
