#include"Resver.h"


//控制正反转
void MotorOutDirection(s16 LeftValue,s16 RightValue)
{
	  u16 LeftMotorOutput;
	  u16 RightMotorOutput;
	
    if(LeftValue<=0)			            //当左电机PWM输出为负时 PB14设为正 PB15设为负
    {	
	  GPIO_SetBits(GPIOB, GPIO_Pin_15 );				    
      GPIO_ResetBits(GPIOB, GPIO_Pin_14 );
      LeftValue = (-LeftValue);
    }
    else 
    {	
      GPIO_SetBits(GPIOB, GPIO_Pin_14 ); //当左电机PWM输出为正时 PB14设为负 PB15设为正 
      GPIO_ResetBits(GPIOB, GPIO_Pin_15 ); 
      LeftValue = LeftValue;
    }

    if(RightValue<=0)
    {									 //当右电机PWM输出为负时 PB12设为正 PB13设为负 
      GPIO_SetBits(GPIOB, GPIO_Pin_12 );				    
      GPIO_ResetBits(GPIOB, GPIO_Pin_13 );
      RightValue = (-RightValue);
    }
    else								 //当右电机PWM输出为正时 PB12设为负 PB13设为正 
    {
	  GPIO_SetBits(GPIOB, GPIO_Pin_13 );				    
      GPIO_ResetBits(GPIOB, GPIO_Pin_12 );	
      RightValue = RightValue;
    }
		
	RightMotorOutput= (u16)RightValue;
	LeftMotorOutput = (u16)LeftValue;
	
	TIM_SetCompare4(TIM2,LeftMotorOutput);	 //调节左轮PWM占空比
	TIM_SetCompare3(TIM2,RightMotorOutput);	 //调节右轮PWM占空比
}

