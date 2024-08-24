#include "stm32f10x.h"                  // Device header
extern uint16_t num;//全局变量声明
//内置时钟
void Timer_init()//初始化TIM2，通用计时器
{
	//RCC开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	
	//选择时基单元的时钟源
	TIM_InternalClockConfig(TIM2);
	
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//分频
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数方式
	TIM_TimeBaseInitStruct.TIM_Period=10000-1;//自动重装
	TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;//预分频
	//这里是在7200分频下计10000个数，7200分频即10kHz的计数频率，即0.0001s计一个数，则计10000个数即为1s一次
	//PSC和ARR的取值要在0到65535之间
	//预分频器和计数器都有一个数的偏差，所以要减一个1
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复计数器，高级计数器才有，这里给0就行
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//消去函数同步更新事件带来的副作用（在进入中断之前有一次中断），避免初始化就进入了一次中断的情况
	//配置输出中断控制
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
		
		
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//这个芯片一次只能选一种分组，所以选一个就够了
		
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=  TIM2_IRQn ;//指定中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;//分组为2，可选的抢占优先级为0-3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//响应优先级也是0-3
	NVIC_Init(&NVIC_InitStruct);
	
	//运行控制:使定时器开始工作
	TIM_Cmd(TIM2,ENABLE);
}


void TIM2_IRQHandler()
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		num++;
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		
	}

}


//外部时钟
void Timer_Init()//初始化TIM2，通用计时器
{
	//RCC开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//RCC管外部要配置，内核则不需配置
	GPIO_InitTypeDef GPIO_InitStructre;//定义结构体
	GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructre.GPIO_Pin= GPIO_Pin_0;
	GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);//开启GPIO，A0
	
	//选择时基单元的时钟源
	TIM_ETRClockMode1Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x00);
	
	
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//分频
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数方式
	TIM_TimeBaseInitStruct.TIM_Period=10-1;//自动重装,外部时钟计数10次即进入中断
	TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//预分频
	//这里是在7200分频下计10000个数，7200分频即10kHz的计数频率，即0.0001s计一个数，则计10000个数即为1s一次
	//PSC和ARR的取值要在0到65535之间
	//预分频器和计数器都有一个数的偏差，所以要减一个1
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复计数器，高级计数器才有，这里给0就行
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//消去函数同步更新事件带来的副作用（在进入中断之前有一次中断），避免初始化就进入了一次中断的情况
	//配置输出中断控制
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
		
		
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//这个芯片一次只能选一种分组，所以选一个就够了
		
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=  TIM2_IRQn ;//指定中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;//分组为2，可选的抢占优先级为0-3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//响应优先级也是0-3
	NVIC_Init(&NVIC_InitStruct);
	
	//运行控制:使定时器开始工作
	TIM_Cmd(TIM2,ENABLE);
}

uint16_t Time_getcount()
{
	return TIM_GetCounter(TIM2);
}