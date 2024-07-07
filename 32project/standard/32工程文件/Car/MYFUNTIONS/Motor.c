#include"Motor.h"

/*
  控制GPIO PB12/PB13/PB14/PB15
  电机MOTOR  TIM2_CH3(PA2)/TIM2_CH4(PA3)
*/

void MOTOR_GPIO_Config(void)
{		
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIOB的外设时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

	/*选择要控制的GPIOB引脚*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	

	/*设置引脚模式为通用推挽输出*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*设置引脚速率为50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*调用库函数，初始化GPIOB*/
  	GPIO_Init(GPIOB, &GPIO_InitStructure);		  

	/* 低电平	*/
	GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_12 | GPIO_Pin_15);	 
}

/*
 * 函数名：TIM2_GPIO_Config
 * 描述  ：配置TIM2复用输出PWM时用到的I/O
 * 输入  ：无
 * 输出  ：无
 * 调用  ：内部调用
 */
static void TIM2_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
  /*GPIOA Configuration: TIM2 channel 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*GPIOA Configuration: TIM2 channel 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/*
 * 函数名：TIM2_Mode_Config
 * 描述  ：配置TIM2输出的PWM信号的模式，如周期、极性、占空比
 * 输入  ：arr定时周期，psc预分频
 * 输出  ：无
 * 调用  ：内部调用
 */
static void TIM2_Mode_Config(u16 arr,u16 psc)
{
	//PCLK1经过2倍频后作为TIM2的时钟源等于72MHz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	u16 CCR4_Val = 0;
	u16 CCR3_Val = 0;

	/* Time base configuration */		 
	TIM_TimeBaseStructure.TIM_Period = arr ;       //ARR 当定时器从0计数到999，即为1000次，为一个定时周期
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	   //设置预分频：不预分频，即为72MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0 ;	 //设置时钟分频系数：不分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	/* PWM2 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	          //配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	                  //设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //当定时器计数值小于CCRX_Val时为高电平

	TIM_OC4Init(TIM2, &TIM_OCInitStructure);	 //使能通道2
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	/* PWM2 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	          //配置为PWM模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	                  //设置跳变值，当计数器计数到这个值时，电平发生跳变
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //当定时器计数值小于CCRX_Val时为高电平

	TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 //使能通道3
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);                   //使能定时器2	
}

/*
 * 函数名：TIM2_PWM_Init
 * 描述  ：TIM2 输出PWM信号初始化，只要调用这个函数
 *         TIM2的两个通道就会有PWM信号输出
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void TIM2_PWM_Init(u16 arr,u16 psc)
{
	TIM2_GPIO_Config();
	TIM2_Mode_Config(arr,psc);	
}

/*
编码器 ：Tim3和Tim4
*/

void encoder_Tim3_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Prescaler = 0;					//这里我们把它设为1，即不分频
	TIM_TimeBaseStructure.TIM_Period = 71;					//每来一个脉冲信号的上升沿（下面有设置）计数值就累加（或累减），65535则为最大计数值，就溢出了
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //这里按理来说应该不起作用，因为计数方向是受TI1和TI2信号的影响的
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//使用编码器模式3
	TIM_ICStructInit(&TIM_ICInitStructure);						
	
	/*配置为编码器模式，计数器在TI1和TI2上升沿处均计数*/
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);		//清除TIM的更新标志位
	TIM_SetCounter(TIM3, 0);					//将脉冲计数值设为零
	TIM_Cmd(TIM3, ENABLE);						//使能TIM3
}

void encoder_Tim4_init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;
  
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* TIM3 clock source enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
   
  /* Timer configuration in Encoder mode */
  TIM_DeInit(TIM4);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;  					// No prescaling 
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  		//设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //向上计数模式 
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge); //TIM_ICPolarity_Rising上升沿捕获
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6; 			//无滤波器
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
   
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);	    //使能中断
  
  TIM_Cmd(TIM4, ENABLE);  	   						//使能定时器3
}

// 读取定时器3计数值
uint32_t read_cnt_TIM3(void)
{
	uint32_t encoder_cnt3;
	encoder_cnt3 = TIM3->CNT;		//读取计数器CNT的值，CNT系uint32_t型的变量
	TIM_SetCounter(TIM3, 0);		//每一次读取完计数值后将计数值清零，重新开始累加脉冲，方便下一次计数
	return encoder_cnt3;				//返回的值就是本次读到的计数值
}

// 读取定时器4计数值
uint32_t read_cnt_TIM4(void)
{
	uint32_t encoder_cnt4;
	encoder_cnt4 = TIM4->CNT;		//读取计数器CNT的值，CNT系uint32_t型的变量
	TIM_SetCounter(TIM4, 0);		//每一次读取完计数值后将计数值清零，重新开始累加脉冲，方便下一次计数
	return encoder_cnt4;				//返回的值就是本次读到的计数值
}

