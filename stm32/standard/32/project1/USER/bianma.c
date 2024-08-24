#include "stm32f10x.h"                  // Device header
void bianma_init()
{
	//打开时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM2已用于输出PWM波，注意换引脚
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//GPIO初始化，配置成输入模式
		GPIO_InitTypeDef GPIO_InitStructre;//定义结构体
		GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;//上下拉输入,或浮空，看外部模块的默认电平
		GPIO_InitStructre.GPIO_Pin= GPIO_Pin_6|GPIO_Pin_7;
		GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructre);//开启GPIO，A6
	
	
	//配置时基单元
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//分频
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数方式
		TIM_TimeBaseInitStruct.TIM_Period=65536-1;//方便换算为负数
		TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//不分频
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复计数器，高级计数器才有，这里给0就行
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
		
		
		
	//配置输入捕获单元
	
		TIM_ICInitTypeDef TIM_ICInitStruct;
		TIM_ICStructInit(&TIM_ICInitStruct);
		TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;//选择通道
		TIM_ICInitStruct.TIM_ICFilter=0xF;//选择输入捕获的滤波器,滤波器计次不会改变信号的原有频率，分频器也是计次的但会改变原有频率，一般采样频率远高于信号频率，故用于过滤高频噪声，使信号更平滑

		TIM_ICInit(TIM3,&TIM_ICInitStruct);
		//配置通道2
		TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;//选择通道
		TIM_ICInitStruct.TIM_ICFilter=0xF;//选择输入捕获的滤波器,滤波器计次不会改变信号的原有频率，分频器也是计次的但会改变原有频率，一般采样频率远高于信号频率，故用于过滤高频噪声，使信号更平滑

		TIM_ICInit(TIM3,&TIM_ICInitStruct);
		
		TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//1,2都计数,后两个参数与配置捕获单元的一致，故可删去之前的//极性,给上升就是不反向，下降就是反向
		
		TIM_Cmd(TIM3,ENABLE);
		
}

uint16_t ENcoder()
{
	uint16_t temp;
	temp=TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return temp;
	
}