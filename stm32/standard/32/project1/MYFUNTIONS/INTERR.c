#include "stm32f10x.h"                  // Device header
#include"Delay.h"
uint16_t countset;

void countsensor_init()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启GPIOB时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//开启AFIO
	
		GPIO_InitTypeDef GPIO_InitStructre;//定义结构体
		GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;//exti推荐上拉输入，或下拉输入，或浮空输入，ipu上拉输入
		GPIO_InitStructre.GPIO_Pin= GPIO_Pin_14;
		GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructre);//配置GPIO
	
		GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource14);//AFIO外设中断引脚配置
	
	
		EXTI_InitTypeDef EXTI_InitStructre;
		EXTI_InitStructre.EXTI_Line=EXTI_Line14;//指定中断线
		EXTI_InitStructre.EXTI_LineCmd=ENABLE;//指定中断线的开关
		EXTI_InitStructre.EXTI_Mode=EXTI_Mode_Interrupt;//中断模式
		EXTI_InitStructre.EXTI_Trigger=EXTI_Trigger_Falling;//下降沿触发
		EXTI_Init(&EXTI_InitStructre);//EXTI配置
		//外部中断配置
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//这个芯片一次只能选一种分组，所以选一个就够了
		
		NVIC_InitTypeDef NVIC_InitStruct;
		NVIC_InitStruct.NVIC_IRQChannel= EXTI15_10_IRQn;//指定中断通道
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//分组为2，可选的抢占优先级为0-3
		NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//响应优先级也是0-3
		NVIC_Init(&NVIC_InitStruct);
		//内部中断配置
		
		//IO口->AFIO->EXYI->NVIC->cpu
}

uint16_t countsensor_get()
{
	return countset;
}

void EXTI15_10_IRQHandler()//中断函数名，要按照所选中断线到启动文件寻找
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET)//判断是否控制14线，SET表示是
	{
		countset++;
		Delay_ms(50);
		EXTI_ClearITPendingBit(EXTI_Line14);//将中断标志位清除，否则一直置1，不断申请中断，造成死循环
	}
}//中断函数不需在头文件声明，它是自动调用的