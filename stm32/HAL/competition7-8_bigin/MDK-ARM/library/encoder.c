#include "encoder.h"
#include "oled.h"


int l,r;

void Encoder_Init(void){
	
HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_1);
HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_2);
	
HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_1);
HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_2);
	
__HAL_TIM_SET_COUNTER(&htim2, 0);
__HAL_TIM_SET_COUNTER(&htim5, 0);
	
HAL_TIM_Base_Start_IT(&htim8);	
	
}	

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static unsigned char i = 0;
  //  8号定时器中断
	
  if(htim == (&htim8))
  {
    //  设置测量频率为100Hz(10ms)
    //int rate = 100;
    //OLED_ShowNum(4,10,1,1);
		
    //  获取编码器信号数
     uint16_t encoder_l = __HAL_TIM_GET_COUNTER(&htim2);
		 uint16_t encoder_r = __HAL_TIM_GET_COUNTER(&htim5);
    //  计算圈数rpm
     l =encoder_l   ;
		 r = encoder_r  ;
    //  编码器数据清零
	
    

      if(l>10000)l=-(65535-l); 
		   if(l>10000)r=-(65535-r); 
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		__HAL_TIM_SET_COUNTER(&htim5, 0);
		//i++;
		//OLED_ShowNum(3,10,i,5);
    //  扩大100倍输出
   
  }
}

///**************************************************************************
//函数功能：读取编码器脉冲差值，读取单位时间内的脉冲变化值
//入口参数：TIM_TypeDef * TIMx
//返回  值：无
//**************************************************************************/
//uint16_t getTIMx_DetaCnt(TIM_TypeDef * TIMx)
//{
//	uint16_t cnt;
//	cnt = TIMx->CNT-0x7fff;
//	TIMx->CNT = 0x7fff;
//	return cnt;
//}

///**************************************************************************
//函数功能：计算左右轮速
//入口参数：int *leftSpeed,int *rightSpeed
//返回  值：无
//		//计算左右车轮线速度，正向速度为正值 ，反向速度为负值，速度为乘以1000之后的速度 mm/s
//		//一定时间内的编码器变化值*转化率（转化为直线上的距离m）*200s（5ms计算一次） 得到 m/s *1000转化为int数据

//		一圈的脉冲数：
//			左：1560
//			右：1560
//		轮子半径：0.03m
//		轮子周长：2*pi*r
//		一个脉冲的距离：
//			左：0.000120830m
//			右：0.000120830m
//		速度分辨率：
//			左： 0.0240m/s 
//			右： 0.0240m/s 
//			200  5ms的倒数
//			1000 扩大分辨率
//**************************************************************************/

//void Get_Motor_Speed(int *leftSpeed,int *rightSpeed)
//{
//	//5ms测速 5ms即这里说的单位时间  	
//	*leftSpeed   = getTIMx_DetaCnt(TIM4)*1000*200*0.000120830;  
//	*rightSpeed  = getTIMx_DetaCnt(TIM2)*1000*200*0.000120830;
//}




//Motor motor1;
//Motor motor2;
//void Motor_Init(void)
//{  
//    HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);      //开启编码器定时器
//    __HAL_TIM_ENABLE_IT(&htim5,TIM_IT_UPDATE);           //开启编码器定时器更新中断,防溢出处理
//    HAL_TIM_Base_Start_IT(&GAP_TIM);                       //开启100ms定时器中断
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_2);            //开启PWM
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_1);            //开启PWM
//    __HAL_TIM_SET_COUNTER(&htim5, 10000);                //编码器定时器初始值设定为10000
//    motor1.lastCount = 0;                                   //结构体内容初始化
//    motor1.totalCount = 0;
//    motor1.overflowNum = 0;                                  
//    motor1.speed = 0;
//    motor1.direct = 0;
//	
//	
//	 HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);      //开启编码器定时器
//    __HAL_TIM_ENABLE_IT(&htim3,TIM_IT_UPDATE);           //开启编码器定时器更新中断,防溢出处理
//    HAL_TIM_Base_Start_IT(&GAP_TIM);                       //开启100ms定时器中断
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_2);            //开启PWM
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_1);            //开启PWM
//    __HAL_TIM_SET_COUNTER(&htim3, 10000);                //编码器定时器初始值设定为10000
//    motor2.lastCount = 0;                                   //结构体内容初始化
//    motor2.totalCount = 0;
//    motor2.overflowNum = 0;                                  
//    motor2.speed = 0;
//    motor2.direct = 0;
//	
//}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//定时器回调函数，用于计算速度
//{
//    if(htim->Instance==ENCODER_TIM.Instance)//编码器输入定时器溢出中断，用于防溢出                   
//    {      
//        if(COUNTERNUM < 10000) motor1.overflowNum++;       //如果是向上溢出
//        else if(COUNTERNUM >= 10000) motor1.overflowNum--; //如果是向下溢出
//        __HAL_TIM_SetCounter(&ENCODER_TIM, 10000);             //重新设定初始值
//    }
//    else if(htim->Instance==GAP_TIM.Instance)//间隔定时器中断，是时候计算速度了
//    {
//        motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM);//如果向上计数（正转），返回值为0，否则返回值为1
//        motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//一个周期内的总计数值等于目前计数值加上溢出的计数值
//        motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10;//算得每秒多少转
//        //motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10 * LINE_SPEED_C//算得车轮线速度每秒多少毫米
//        motor1.lastCount = motor1.totalCount; //记录这一次的计数值
//    }
//		if(htim->Instance==ENCODER_TIM.Instance)//编码器输入定时器溢出中断，用于防溢出                   
//    {      
//        if(COUNTERNUM < 10000) motor1.overflowNum++;       //如果是向上溢出
//        else if(COUNTERNUM >= 10000) motor1.overflowNum--; //如果是向下溢出
//        __HAL_TIM_SetCounter(&ENCODER_TIM, 10000);             //重新设定初始值
//    }
//    else if(htim->Instance==GAP_TIM.Instance)//间隔定时器中断，是时候计算速度了
//    {
//        motor2.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM);//如果向上计数（正转），返回值为0，否则返回值为1
//        motor2.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//一个周期内的总计数值等于目前计数值加上溢出的计数值
//        motor2.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10;//算得每秒多少转
//        //motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10 * LINE_SPEED_C//算得车轮线速度每秒多少毫米
//        motor2.lastCount = motor1.totalCount; //记录这一次的计数值
//    }
//		  
//}

/* USER CODE BEGIN 4 */
//int getTIMx_DetaCnt(TIM_HandleTypeDef *htim)
//{
//    int cnt;
//    cnt = htim->Instance->CNT - 0x7FFF;
//    htim->Instance->CNT = 0x7FFF;
//    return cnt;
//}

//void Get_Motor_Speed(int *leftSpeed, int *rightSpeed)
//{
//    *leftSpeed = getTIMx_DetaCnt(&htim1);
//    *rightSpeed = getTIMx_DetaCnt(&htim3);
//}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{   
//    if (htim == &htim8)
//    {
//        Get_Motor_Speed(&l, &r);
//    }
//}
/* USER CODE END 4 */



