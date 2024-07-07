#include"Motor.h"

/*
  ����GPIO PB12/PB13/PB14/PB15
  ���MOTOR  TIM2_CH3(PA2)/TIM2_CH4(PA3)
*/

void MOTOR_GPIO_Config(void)
{		
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOB������ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 

	/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	

	/*��������ģʽΪͨ���������*/
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

	/*������������Ϊ50MHz */   
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	/*���ÿ⺯������ʼ��GPIOB*/
  	GPIO_Init(GPIOB, &GPIO_InitStructure);		  

	/* �͵�ƽ	*/
	GPIO_SetBits(GPIOB, GPIO_Pin_13 | GPIO_Pin_14|GPIO_Pin_12 | GPIO_Pin_15);	 
}

/*
 * ��������TIM2_GPIO_Config
 * ����  ������TIM2�������PWMʱ�õ���I/O
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
static void TIM2_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
  /*GPIOA Configuration: TIM2 channel 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /*GPIOA Configuration: TIM2 channel 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

}

/*
 * ��������TIM2_Mode_Config
 * ����  ������TIM2�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ��arr��ʱ���ڣ�pscԤ��Ƶ
 * ���  ����
 * ����  ���ڲ�����
 */
static void TIM2_Mode_Config(u16 arr,u16 psc)
{
	//PCLK1����2��Ƶ����ΪTIM2��ʱ��Դ����72MHz
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	u16 CCR4_Val = 0;
	u16 CCR3_Val = 0;

	/* Time base configuration */		 
	TIM_TimeBaseStructure.TIM_Period = arr ;       //ARR ����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	   //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = 0 ;	 //����ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	/* PWM2 Mode configuration: Channel2 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	          //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	                  //��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //����ʱ������ֵС��CCRX_ValʱΪ�ߵ�ƽ

	TIM_OC4Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��2
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	/* PWM2 Mode configuration: Channel3 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	          //����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	                  //��������ֵ�������������������ֵʱ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //����ʱ������ֵС��CCRX_ValʱΪ�ߵ�ƽ

	TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��3
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

	/* TIM2 enable counter */
	TIM_Cmd(TIM2, ENABLE);                   //ʹ�ܶ�ʱ��2	
}

/*
 * ��������TIM2_PWM_Init
 * ����  ��TIM2 ���PWM�źų�ʼ����ֻҪ�����������
 *         TIM2������ͨ���ͻ���PWM�ź����
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void TIM2_PWM_Init(u16 arr,u16 psc)
{
	TIM2_GPIO_Config();
	TIM2_Mode_Config(arr,psc);	
}

/*
������ ��Tim3��Tim4
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

	TIM_TimeBaseStructure.TIM_Prescaler = 0;					//�������ǰ�����Ϊ1��������Ƶ
	TIM_TimeBaseStructure.TIM_Period = 71;					//ÿ��һ�������źŵ������أ����������ã�����ֵ���ۼӣ����ۼ�����65535��Ϊ������ֵ���������
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ﰴ����˵Ӧ�ò������ã���Ϊ������������TI1��TI2�źŵ�Ӱ���
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);//ʹ�ñ�����ģʽ3
	TIM_ICStructInit(&TIM_ICInitStructure);						
	
	/*����Ϊ������ģʽ����������TI1��TI2�����ش�������*/
	TIM_ICInit(TIM3, &TIM_ICInitStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);		//���TIM�ĸ��±�־λ
	TIM_SetCounter(TIM3, 0);					//���������ֵ��Ϊ��
	TIM_Cmd(TIM3, ENABLE);						//ʹ��TIM3
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
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  		//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;   //���ϼ���ģʽ 
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
 
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge); //TIM_ICPolarity_Rising�����ز���
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6; 			//���˲���
  TIM_ICInit(TIM4, &TIM_ICInitStructure);
   
  TIM_ClearFlag(TIM4, TIM_FLAG_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);	    //ʹ���ж�
  
  TIM_Cmd(TIM4, ENABLE);  	   						//ʹ�ܶ�ʱ��3
}

// ��ȡ��ʱ��3����ֵ
uint32_t read_cnt_TIM3(void)
{
	uint32_t encoder_cnt3;
	encoder_cnt3 = TIM3->CNT;		//��ȡ������CNT��ֵ��CNTϵuint32_t�͵ı���
	TIM_SetCounter(TIM3, 0);		//ÿһ�ζ�ȡ�����ֵ�󽫼���ֵ���㣬���¿�ʼ�ۼ����壬������һ�μ���
	return encoder_cnt3;				//���ص�ֵ���Ǳ��ζ����ļ���ֵ
}

// ��ȡ��ʱ��4����ֵ
uint32_t read_cnt_TIM4(void)
{
	uint32_t encoder_cnt4;
	encoder_cnt4 = TIM4->CNT;		//��ȡ������CNT��ֵ��CNTϵuint32_t�͵ı���
	TIM_SetCounter(TIM4, 0);		//ÿһ�ζ�ȡ�����ֵ�󽫼���ֵ���㣬���¿�ʼ�ۼ����壬������һ�μ���
	return encoder_cnt4;				//���ص�ֵ���Ǳ��ζ����ļ���ֵ
}

