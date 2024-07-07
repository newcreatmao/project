#include"Ic.h"
void PWMIC_init()
{
	//打开时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM2已用于输出PWM波，注意换引脚
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//GPIO初始化，配置成输入模式
		GPIO_InitTypeDef GPIO_InitStructre;//定义结构体
		GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;//上拉输入
		GPIO_InitStructre.GPIO_Pin= GPIO_Pin_6;
		GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructre);//开启GPIO，A6
	
	
	//配置时基单元
		TIM_InternalClockConfig(TIM3);
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//分频
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数方式
		TIM_TimeBaseInitStruct.TIM_Period=65536-1;//防止计数溢出
		TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复计数器，高级计数器才有，这里给0就行
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
		
		
	//配置输入捕获单元
	
		TIM_ICInitTypeDef TIM_ICInitStruct;
		TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;//选择通道
		TIM_ICInitStruct.TIM_ICFilter=0xF;//选择输入捕获的滤波器,滤波器计次不会改变信号的原有频率，分频器也是计次的但会改变原有频率，一般采样频率远高于信号频率，故用于过滤高频噪声，使信号更平滑
		TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;//极性
		TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;//配置触发信号分频器，不分频则每次信号都有效,二分频是每隔一次有效一次
		TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;//选择触发信号的输入引脚，直连通道
		//方法一配置另一条通道
		/*TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;//选择通道
		TIM_ICInitStruct.TIM_ICFilter=0xF;//选择输入捕获的滤波器,滤波器计次不会改变信号的原有频率，分频器也是计次的但会改变原有频率，一般采样频率远高于信号频率，故用于过滤高频噪声，使信号更平滑
		TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Falling;//极性
		TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;//配置触发信号分频器，不分频则每次信号都有效,二分频是每隔一次有效一次
		TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_IndirectTI;//选择触发信号的输入引脚，交叉通道*/
		//方法二用函数
		TIM_PWMIConfig(TIM3,&TIM_ICInitStruct);//可自动将剩下的通道和极性配置成所需，只支持通道1，2
		
		TIM_ICInit(TIM3,&TIM_ICInitStruct);
	
	
	//选择从模式的触发源
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);//对应从模式的对应通道
	//选择触发之后执行的操作
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);//将从模式变成reset
	
	//打开定时器
	TIM_Cmd(TIM3,ENABLE);
}

uint32_t ICgetHZ()//频率
{
	return 1000000/(TIM_GetCapture1(TIM3)+1);//1MHZ
}

uint32_t ICgetDUTY()//占空比
{
	return ((TIM_GetCapture2(TIM3)*100)/TIM_GetCapture1(TIM3)+1);
}