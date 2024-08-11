#include "encoder.h"
#include "oled.h"
#include "stdio.h"
Motor motor_L,motor_R;

uint8_t LSpeed_Len = 0,RSpeed_Len = 0;
void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&L_TIM,TIM_CHANNEL_1 | TIM_CHANNEL_2);      //������������ʱ��
    __HAL_TIM_ENABLE_IT(&L_TIM,TIM_IT_UPDATE);                        //������������ʱ�������ж�,���������
		HAL_TIM_Encoder_Start(&R_TIM,TIM_CHANNEL_1 | TIM_CHANNEL_2);      
    __HAL_TIM_ENABLE_IT(&R_TIM,TIM_IT_UPDATE);           
	
    HAL_TIM_Base_Start_IT(&GAP_TIM);                       //����50ms��ʱ���ж�
	
    __HAL_TIM_SET_COUNTER(&L_TIM, 0);                //��������ʱ����ʼֵ�趨
		__HAL_TIM_SET_COUNTER(&R_TIM, 0);                //��������ʱ����ʼֵ�趨
    motor_L.lastCount = 0;                                   //�ṹ�����ݳ�ʼ��
    motor_L.totalCount = 0;
    motor_L.overflowNum = 0;                                  
    motor_L.speed = 0;
    motor_L.direct = 0;
		
	  motor_R.lastCount = 0;                                   //�ṹ�����ݳ�ʼ��
    motor_R.totalCount = 0;
    motor_R.overflowNum = 0;                                  
    motor_R.speed = 0;
    motor_R.direct = 0;
}
float applyEMAFilter(float new_Spe,float pre_Spe)
{
    return (double)ALPHA * new_Spe + (1 - ALPHA) * pre_Spe;//���ؾ�ֵ
}
void OLED_showLSpeed(uint8_t x,uint8_t y){
			  if(motor_L.speed < 0){
				OLED_showchar(x,y,'-');
				OLED_shownum(x,y+1,(int32_t)(-1)*motor_L.speed,4);
			}
			else
			OLED_shownum(x,y,(int32_t)motor_L.speed,5);
}
void OLED_showRSpeed(uint8_t x,uint8_t y){
			  if(motor_R.speed < 0){
				OLED_showchar(x,y,'-');
				OLED_shownum(x,y+1,(int32_t)(-1)*motor_R.speed,4);
			}
			else
			OLED_shownum(x,y,(int32_t)motor_R.speed,5);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//��ʱ���ص����������ڼ����ٶ�
{
    if(htim->Instance==L_TIM.Instance)  //���������붨ʱ������жϣ����ڷ����                   
    {      
				     if(COUNTERNUM1 < 65536 / 2) motor_L.overflowNum++;       //������������
       else if(COUNTERNUM1 >= 65536 / 2) motor_L.overflowNum--;       //������������
    }
		else if(htim->Instance==R_TIM.Instance){
						 if(COUNTERNUM2 < 65536 / 2) motor_R.overflowNum++;       //������������
       else if(COUNTERNUM2 >= 65536 / 2) motor_R.overflowNum--;       //������������
		}
    else if(htim->Instance==GAP_TIM.Instance)//�����ʱ���жϣ���ʱ������ٶ���
    {
			uint16_t cur_LCnt = COUNTERNUM1,cur_RCnt = COUNTERNUM2;
			
			motor_L.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&L_TIM);                      //������ϼ�������ת��������ֵΪ0�����򷵻�ֵΪ1
			motor_L.totalCount = cur_LCnt + motor_L.overflowNum * RELOADVALUE;         //һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
			motor_L.overflowNum = 0; 
			float temp = motor_L.totalCount - motor_L.lastCount;
			motor_L.speed = applyEMAFilter(temp,motor_L.speed);
			motor_L.lastCount = cur_LCnt;
			
			motor_R.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&R_TIM);                      //������ϼ�������ת��������ֵΪ0�����򷵻�ֵΪ1
			motor_R.totalCount = cur_RCnt + motor_R.overflowNum * RELOADVALUE;         //һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
			motor_R.overflowNum = 0;
			temp = motor_R.totalCount - motor_R.lastCount;
			motor_R.speed = applyEMAFilter(temp,motor_R.speed);
			motor_R.lastCount = cur_RCnt;
			printf("%f,%f,%f\n",motor_L.speed,motor_R.speed,L_SPID.TargetSpeed);
			spid_Flag++;
			if(spid_Flag >= 3){
		  spid_Flag = 0;
		  SPID_Ctrl();
	}
//			pid_Flag++;
    }
}

