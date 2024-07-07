#include "stm32f10x.h"                  // Device header

void  exchange()//引脚重映射
{
	//RCC开启时钟，TIM，GPIO
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		
	
	
	//引脚重映射配置
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//定义AFIO
	
		GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//部分重映射，将PA0换到PA15
	
	//关闭PA15的调试端口复用
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);
	//打开AFIO时钟->重映射管脚->解除调试端口
	
	
	
	//配置时基单元
		TIM_InternalClockConfig(TIM2);
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//分频
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数方式
		TIM_TimeBaseInitStruct.TIM_Period=100-1;//自动重装,arr
		TIM_TimeBaseInitStruct.TIM_Prescaler=720-1;//预分频,psc
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复计数器，高级计数器才有，这里给0就行
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	//配置输出比较单元
		TIM_OCInitTypeDef TIM_OCInitStruct;
	  TIM_OCStructInit(&TIM_OCInitStruct);//给结构体成员赋初始值，防止转用高级定时器时因未给其他成员赋值而出现问题
		//TIM_OCInitStruct.TIM_OCIdleState=Idle高级定时器才需要用
	
		TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;//PWM1模式//设置输出比较的模式//TIM_SelectOCxM单独修改输出比较模式
	
		//TIM_OCInitStruct.TIM_OCNIdleState=带N的表示有互补通道，一般高级定时器才需要用
		//TIM_OCInitStruct.TIM_OCNPolarity=
		
		TIM_OCInitStruct.TIM_OCPolarity=TIM_OCNPolarity_High;//高极性//设置输出比较的极性//TIM_OC1PolarityConfig单独设置极性
		//TIM_OCInitStruct.TIM_OutputNState=
		
		TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//设置输出使能
		
		TIM_OCInitStruct.TIM_Pulse=0;//设置CCR,ccr,要计算,占空比ccr/(arr+1)
		
		TIM_OC1Init(TIM2,&TIM_OCInitStruct);//初始化OC1通道，看手册引脚选择
	
	//配置GPIO
		GPIO_InitTypeDef GPIO_InitStructre;//定义结构体
		GPIO_InitStructre.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出，让定时器控制引脚
		GPIO_InitStructre.GPIO_Pin= GPIO_Pin_15;//记得改成映射后的代码
		GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructre);//开启GPIO，A0
	
	//运行控制
		TIM_Cmd(TIM2,ENABLE);//启动定时器

}