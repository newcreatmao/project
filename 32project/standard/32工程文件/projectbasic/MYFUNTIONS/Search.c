#include"Search.h"
// uint16_t Encoder_A_EXTI=0;
// void Encoder_Init_TIM_ExitA(void)//用于检测编码器A相使用PA8引脚
// {
//    	GPIO_InitTypeDef GPIO_InitStructure;
//    	EXTI_InitTypeDef EXTI_InitStructure;
//    	NVIC_InitTypeDef NVIC_InitStructure;
   
//    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
//    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟
//    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	            //端口配置
//    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
//    	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//跳变沿触发
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
     
//   // 配置中断优先级 													
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
// }


// void Encoder_Init_TIM_ExitB(void)//用于检测编码器B相使用PA9引脚
// {
//    	GPIO_InitTypeDef GPIO_InitStructure;
//    	EXTI_InitTypeDef EXTI_InitStructure;
//    	NVIC_InitTypeDef NVIC_InitStructure;
//    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
//    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟
//    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	            //端口配置
//    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
//    	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//跳变沿触发
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
     
//   //配置中断优先级												
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;	  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
// }

// uint16_t Get_AB(){
//     return Encoder_A_EXTI;
// }

// void EXTI0_IRQHandler(void)  //外部中断线0服务函数
// {
// 	EXTI->PR=1<<0;  //清除LINE上的中断标志位
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)   //这里判断检测到的是否是下降沿
// 	{
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0)   Encoder_A_EXTI++;//看B相的电平如果是高电机就是正转则加1，否则就是反转减1
// 	else             Encoder_A_EXTI--;
// 	}
// 	else                  //上升沿
// 	{ 
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0)  Encoder_A_EXTI--; //B相低电平为正转，加1，高电平反转减1
// 	else             Encoder_A_EXTI++;
// 	}		
// }

// void EXTI1_IRQHandler(void)//外部中断线1服务函数
// {			
// 	EXTI->PR=1<<1;  //清除LINE上的中断标志位
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1) //这里判断检测到的是否是上升沿
// 	{
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)  Encoder_A_EXTI++;  //看A相的电平如果是低,电机就是正转则加1，否则就是反转减1 
// 	else            Encoder_A_EXTI--;
// 	}
// 	else
// 	{
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)  Encoder_A_EXTI--;
// 	else            Encoder_A_EXTI++;
// 	}		
// }


// int Read_Encoder(u8 TIMX)//读取计数器的值
// {
//   int Encoder_TIM;
// 	switch(TIMX)
// 	{
// 	  case 2:Encoder_TIM=(short)TIM2->CNT; TIM2 -> CNT=0;  break;
// 		case 3:Encoder_TIM=(short)TIM3->CNT; TIM3 -> CNT=0;  break;
// 		case 4:Encoder_TIM=(short)TIM4->CNT; TIM4 -> CNT=0;  break;
// 		default: Encoder_TIM=0;
// 	}
//   return Encoder_TIM;
// }



void BianA_init()
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

uint16_t ENcoderA()
{
	uint16_t temp;
	temp=TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return temp;
}

void BianB_init(){
		//打开时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//TIM2已用于输出PWM波，注意换引脚
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//GPIO初始化，配置成输入模式
		GPIO_InitTypeDef GPIO_InitStructre;//定义结构体
		GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;//上下拉输入,或浮空，看外部模块的默认电平
		GPIO_InitStructre.GPIO_Pin= GPIO_Pin_8|GPIO_Pin_9;
		GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructre);//开启GPIO，A6
	
	
	//配置时基单元
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//分频
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//计数方式
		TIM_TimeBaseInitStruct.TIM_Period=65536-1;//方便换算为负数
		TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//不分频
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//重复计数器，高级计数器才有，这里给0就行
		TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
		
		
		
	//配置输入捕获单元
	
		TIM_ICInitTypeDef TIM_ICInitStruct;
		TIM_ICStructInit(&TIM_ICInitStruct);
		TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;//选择通道
		TIM_ICInitStruct.TIM_ICFilter=0xF;//选择输入捕获的滤波器,滤波器计次不会改变信号的原有频率，分频器也是计次的但会改变原有频率，一般采样频率远高于信号频率，故用于过滤高频噪声，使信号更平滑

		TIM_ICInit(TIM1,&TIM_ICInitStruct);
		//配置通道2
		TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;//选择通道
		TIM_ICInitStruct.TIM_ICFilter=0xF;//选择输入捕获的滤波器,滤波器计次不会改变信号的原有频率，分频器也是计次的但会改变原有频率，一般采样频率远高于信号频率，故用于过滤高频噪声，使信号更平滑

		TIM_ICInit(TIM1,&TIM_ICInitStruct);
		
		TIM_EncoderInterfaceConfig(TIM1,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//1,2都计数,后两个参数与配置捕获单元的一致，故可删去之前的//极性,给上升就是不反向，下降就是反向
		
		TIM_Cmd(TIM1,ENABLE);
}

uint16_t ENcoderB()
{
	uint16_t temp;
	temp=TIM_GetCounter(TIM1);
	TIM_SetCounter(TIM1,0);
	return temp;
}