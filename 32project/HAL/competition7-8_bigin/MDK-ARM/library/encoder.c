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
  //  8�Ŷ�ʱ���ж�
	
  if(htim == (&htim8))
  {
    //  ���ò���Ƶ��Ϊ100Hz(10ms)
    //int rate = 100;
    //OLED_ShowNum(4,10,1,1);
		
    //  ��ȡ�������ź���
     uint16_t encoder_l = __HAL_TIM_GET_COUNTER(&htim2);
		 uint16_t encoder_r = __HAL_TIM_GET_COUNTER(&htim5);
    //  ����Ȧ��rpm
     l =encoder_l   ;
		 r = encoder_r  ;
    //  ��������������
	
    

      if(l>10000)l=-(65535-l); 
		   if(l>10000)r=-(65535-r); 
		__HAL_TIM_SET_COUNTER(&htim2, 0);
		__HAL_TIM_SET_COUNTER(&htim5, 0);
		//i++;
		//OLED_ShowNum(3,10,i,5);
    //  ����100�����
   
  }
}

///**************************************************************************
//�������ܣ���ȡ�����������ֵ����ȡ��λʱ���ڵ�����仯ֵ
//��ڲ�����TIM_TypeDef * TIMx
//����  ֵ����
//**************************************************************************/
//uint16_t getTIMx_DetaCnt(TIM_TypeDef * TIMx)
//{
//	uint16_t cnt;
//	cnt = TIMx->CNT-0x7fff;
//	TIMx->CNT = 0x7fff;
//	return cnt;
//}

///**************************************************************************
//�������ܣ�������������
//��ڲ�����int *leftSpeed,int *rightSpeed
//����  ֵ����
//		//�������ҳ������ٶȣ������ٶ�Ϊ��ֵ �������ٶ�Ϊ��ֵ���ٶ�Ϊ����1000֮����ٶ� mm/s
//		//һ��ʱ���ڵı������仯ֵ*ת���ʣ�ת��Ϊֱ���ϵľ���m��*200s��5ms����һ�Σ� �õ� m/s *1000ת��Ϊint����

//		һȦ����������
//			��1560
//			�ң�1560
//		���Ӱ뾶��0.03m
//		�����ܳ���2*pi*r
//		һ������ľ��룺
//			��0.000120830m
//			�ң�0.000120830m
//		�ٶȷֱ��ʣ�
//			�� 0.0240m/s 
//			�ң� 0.0240m/s 
//			200  5ms�ĵ���
//			1000 ����ֱ���
//**************************************************************************/

//void Get_Motor_Speed(int *leftSpeed,int *rightSpeed)
//{
//	//5ms���� 5ms������˵�ĵ�λʱ��  	
//	*leftSpeed   = getTIMx_DetaCnt(TIM4)*1000*200*0.000120830;  
//	*rightSpeed  = getTIMx_DetaCnt(TIM2)*1000*200*0.000120830;
//}




//Motor motor1;
//Motor motor2;
//void Motor_Init(void)
//{  
//    HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);      //������������ʱ��
//    __HAL_TIM_ENABLE_IT(&htim5,TIM_IT_UPDATE);           //������������ʱ�������ж�,���������
//    HAL_TIM_Base_Start_IT(&GAP_TIM);                       //����100ms��ʱ���ж�
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_2);            //����PWM
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_1);            //����PWM
//    __HAL_TIM_SET_COUNTER(&htim5, 10000);                //��������ʱ����ʼֵ�趨Ϊ10000
//    motor1.lastCount = 0;                                   //�ṹ�����ݳ�ʼ��
//    motor1.totalCount = 0;
//    motor1.overflowNum = 0;                                  
//    motor1.speed = 0;
//    motor1.direct = 0;
//	
//	
//	 HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);      //������������ʱ��
//    __HAL_TIM_ENABLE_IT(&htim3,TIM_IT_UPDATE);           //������������ʱ�������ж�,���������
//    HAL_TIM_Base_Start_IT(&GAP_TIM);                       //����100ms��ʱ���ж�
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_2);            //����PWM
//    HAL_TIM_PWM_Start(&PWM_TIM, TIM_CHANNEL_1);            //����PWM
//    __HAL_TIM_SET_COUNTER(&htim3, 10000);                //��������ʱ����ʼֵ�趨Ϊ10000
//    motor2.lastCount = 0;                                   //�ṹ�����ݳ�ʼ��
//    motor2.totalCount = 0;
//    motor2.overflowNum = 0;                                  
//    motor2.speed = 0;
//    motor2.direct = 0;
//	
//}

//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)//��ʱ���ص����������ڼ����ٶ�
//{
//    if(htim->Instance==ENCODER_TIM.Instance)//���������붨ʱ������жϣ����ڷ����                   
//    {      
//        if(COUNTERNUM < 10000) motor1.overflowNum++;       //������������
//        else if(COUNTERNUM >= 10000) motor1.overflowNum--; //������������
//        __HAL_TIM_SetCounter(&ENCODER_TIM, 10000);             //�����趨��ʼֵ
//    }
//    else if(htim->Instance==GAP_TIM.Instance)//�����ʱ���жϣ���ʱ������ٶ���
//    {
//        motor1.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM);//������ϼ�������ת��������ֵΪ0�����򷵻�ֵΪ1
//        motor1.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
//        motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10;//���ÿ�����ת
//        //motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10 * LINE_SPEED_C//��ó������ٶ�ÿ����ٺ���
//        motor1.lastCount = motor1.totalCount; //��¼��һ�εļ���ֵ
//    }
//		if(htim->Instance==ENCODER_TIM.Instance)//���������붨ʱ������жϣ����ڷ����                   
//    {      
//        if(COUNTERNUM < 10000) motor1.overflowNum++;       //������������
//        else if(COUNTERNUM >= 10000) motor1.overflowNum--; //������������
//        __HAL_TIM_SetCounter(&ENCODER_TIM, 10000);             //�����趨��ʼֵ
//    }
//    else if(htim->Instance==GAP_TIM.Instance)//�����ʱ���жϣ���ʱ������ٶ���
//    {
//        motor2.direct = __HAL_TIM_IS_TIM_COUNTING_DOWN(&ENCODER_TIM);//������ϼ�������ת��������ֵΪ0�����򷵻�ֵΪ1
//        motor2.totalCount = COUNTERNUM + motor1.overflowNum * RELOADVALUE;//һ�������ڵ��ܼ���ֵ����Ŀǰ����ֵ��������ļ���ֵ
//        motor2.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10;//���ÿ�����ת
//        //motor1.speed = (float)(motor1.totalCount - motor1.lastCount) / (4 * MOTOR_SPEED_RERATIO * PULSE_PRE_ROUND) * 10 * LINE_SPEED_C//��ó������ٶ�ÿ����ٺ���
//        motor2.lastCount = motor1.totalCount; //��¼��һ�εļ���ֵ
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



