#include"Resver.h"


//��������ת
void MotorOutDirection(s16 LeftValue,s16 RightValue)
{
	  u16 LeftMotorOutput;
	  u16 RightMotorOutput;
	
    if(LeftValue<=0)			            //������PWM���Ϊ��ʱ PB14��Ϊ�� PB15��Ϊ��
    {	
	  GPIO_SetBits(GPIOB, GPIO_Pin_15 );				    
      GPIO_ResetBits(GPIOB, GPIO_Pin_14 );
      LeftValue = (-LeftValue);
    }
    else 
    {	
      GPIO_SetBits(GPIOB, GPIO_Pin_14 ); //������PWM���Ϊ��ʱ PB14��Ϊ�� PB15��Ϊ�� 
      GPIO_ResetBits(GPIOB, GPIO_Pin_15 ); 
      LeftValue = LeftValue;
    }

    if(RightValue<=0)
    {									 //���ҵ��PWM���Ϊ��ʱ PB12��Ϊ�� PB13��Ϊ�� 
      GPIO_SetBits(GPIOB, GPIO_Pin_12 );				    
      GPIO_ResetBits(GPIOB, GPIO_Pin_13 );
      RightValue = (-RightValue);
    }
    else								 //���ҵ��PWM���Ϊ��ʱ PB12��Ϊ�� PB13��Ϊ�� 
    {
	  GPIO_SetBits(GPIOB, GPIO_Pin_13 );				    
      GPIO_ResetBits(GPIOB, GPIO_Pin_12 );	
      RightValue = RightValue;
    }
		
	RightMotorOutput= (u16)RightValue;
	LeftMotorOutput = (u16)LeftValue;
	
	TIM_SetCompare4(TIM2,LeftMotorOutput);	 //��������PWMռ�ձ�
	TIM_SetCompare3(TIM2,RightMotorOutput);	 //��������PWMռ�ձ�
}

