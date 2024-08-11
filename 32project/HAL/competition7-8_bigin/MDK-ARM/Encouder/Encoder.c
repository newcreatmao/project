#include "encoder.h"
#include "oled.h"
#include "stdio.h"
Motor motor_L,motor_R;

uint8_t LSpeed_Len = 0,RSpeed_Len = 0;
void Encoder_Init(void)
{
    HAL_TIM_Encoder_Start(&L_TIM,TIM_CHANNEL_1 | TIM_CHANNEL_2);      //开启编码器定时器
    __HAL_TIM_ENABLE_IT(&L_TIM,TIM_IT_UPDATE);                        //开启编码器定时器更新中断,防溢出处理
		HAL_TIM_Encoder_Start(&R_TIM,TIM_CHANNEL_1 | TIM_CHANNEL_2);      
    __HAL_TIM_ENABLE_IT(&R_TIM,TIM_IT_UPDATE);           
	
    HAL_TIM_Base_Start_IT(&GAP_TIM);                       //开启50ms定时器中断
	
    __HAL_TIM_SET_COUNTER(&L_TIM, 0);                //编码器定时器初始值设定
		__HAL_TIM_SET_COUNTER(&R_TIM, 0);                //编码器定时器初始值设定
    motor_L.lastCount = 0;                                   //结构体内容初始化
    motor_L.totalCount = 0;
    motor_L.overflowNum = 0;                                  
    motor_L.speed = 0;
    motor_L.direct = 0;
		
	  motor_R.lastCount = 0;                                   //结构体内容初始化
    motor_R.totalCount = 0;
    motor_R.overflowNum = 0;                                  
    motor_R.speed = 0;
    motor_R.direct = 0;
}
float applyEMAFilter(float new_Spe,float pre_Spe)
{
    return (double)ALPHA * new_Spe + (1 - ALPHA) * pre_Spe;//返回均值
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
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//定时器回调函数，用于计算速度
{
    if(htim->Instance==L_TIM.Instance)  //编码器输入定时器溢出中断，用于防溢出                   
    {      
				     if(COUNTERNUM1 < 65536 / 2) motor_L.overflowNum++;       //如果是向上溢出
       else if(COUNTERNUM1 >= 65536 / 2) motor_L.overflowNum--;       //如果是向下溢出
    }
		else if(htim->Instance==R_TIM.Instance){
						 if(COUNTERNUM2 < 65536 / 2) motor_R.overflowNum++;       //如果是向上溢出
       else if(COUNTERNUM2 >= 65536 / 2) motor_R.overflowNum--;       //如果是向下溢出
		}
    else if(htim->Instance==GAP_TIM.Instance)//间隔定时器中断，是时候计算速度了
    {
			uint16_t cur_LCnt = COUNTERNUM1,cur_RCnt = COUNTERNUM2;
			
			motor_L.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&L_TIM);                      //如果向上计数（正转），返回值为0，否则返回值为1
			motor_L.totalCount = cur_LCnt + motor_L.overflowNum * RELOADVALUE;         //一个周期内的总计数值等于目前计数值加上溢出的计数值
			motor_L.overflowNum = 0; 
			float temp = motor_L.totalCount - motor_L.lastCount;
			motor_L.speed = applyEMAFilter(temp,motor_L.speed);
			motor_L.lastCount = cur_LCnt;
			
			motor_R.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&R_TIM);                      //如果向上计数（正转），返回值为0，否则返回值为1
			motor_R.totalCount = cur_RCnt + motor_R.overflowNum * RELOADVALUE;         //一个周期内的总计数值等于目前计数值加上溢出的计数值
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

