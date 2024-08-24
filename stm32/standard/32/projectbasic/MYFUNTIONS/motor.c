#include"motor.h"


void ENA_PWMInit()
{
		//RCC开启时钟，TIM，GPIO
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//配置时基单元
		TIM_InternalClockConfig(TIM2);
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//分频
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数方式
		TIM_TimeBaseInitStruct.TIM_Period=100-1;//自动重装,arr,固定为100-1，则ccr数值直接就是占空比，较好计算，分辨率为1%
		TIM_TimeBaseInitStruct.TIM_Prescaler=720-1;//预分频,psc，可通过改变
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
		GPIO_InitStructre.GPIO_Pin= GPIO_Pin_0;
		GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructre);//开启GPIO，A0
	//运行控制
		TIM_Cmd(TIM2,ENABLE);//启动定时器
}

void Motor_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void PWMCCR(uint16_t CCR)//修改占空比，注：占空比是ccr与arr共同确定的
{
	TIM_SetCompare1(TIM2,CCR);//单独更改CCR寄存器的值
}

void PWMPSC(uint16_t PSC)
{
	TIM_PrescalerConfig(TIM2,PSC,TIM_PSCReloadMode_Immediate);//写入PSC的值,更新事件能保存好一个波型
}

void moto(int i,int j) //i=0反转 i=1正转 j为转速 最大100
{
	if(i==1)
	{
		PWMCCR(j);//注意顺序
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
	}
	if(i==0)
	{
		PWMCCR(j);//注意顺序
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	}
}
