#include"Search.h"
// uint16_t Encoder_A_EXTI=0;
// void Encoder_Init_TIM_ExitA(void)//���ڼ�������A��ʹ��PA8����
// {
//    	GPIO_InitTypeDef GPIO_InitStructure;
//    	EXTI_InitTypeDef EXTI_InitStructure;
//    	NVIC_InitTypeDef NVIC_InitStructure;
   
//    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
//    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��PA�˿�ʱ��
//    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	            //�˿�����
//    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
//    	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource8);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//�����ش���
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
     
//   // �����ж����ȼ� 													
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
// }


// void Encoder_Init_TIM_ExitB(void)//���ڼ�������B��ʹ��PA9����
// {
//    	GPIO_InitTypeDef GPIO_InitStructure;
//    	EXTI_InitTypeDef EXTI_InitStructure;
//    	NVIC_InitTypeDef NVIC_InitStructure;
//    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
//    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��PA�˿�ʱ��
//    	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	            //�˿�����
//    	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //��������
//    	GPIO_Init(GPIOA, &GPIO_InitStructure);					      //�����趨������ʼ��GPIOB 
//  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource9);
//  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
//  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
//  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//�����ش���
//  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
     
//   //�����ж����ȼ�												
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;	  
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
// }

// uint16_t Get_AB(){
//     return Encoder_A_EXTI;
// }

// void EXTI0_IRQHandler(void)  //�ⲿ�ж���0������
// {
// 	EXTI->PR=1<<0;  //���LINE�ϵ��жϱ�־λ
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)   //�����жϼ�⵽���Ƿ����½���
// 	{
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0)   Encoder_A_EXTI++;//��B��ĵ�ƽ����Ǹߵ��������ת���1��������Ƿ�ת��1
// 	else             Encoder_A_EXTI--;
// 	}
// 	else                  //������
// 	{ 
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==0)  Encoder_A_EXTI--; //B��͵�ƽΪ��ת����1���ߵ�ƽ��ת��1
// 	else             Encoder_A_EXTI++;
// 	}		
// }

// void EXTI1_IRQHandler(void)//�ⲿ�ж���1������
// {			
// 	EXTI->PR=1<<1;  //���LINE�ϵ��жϱ�־λ
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_9)==1) //�����жϼ�⵽���Ƿ���������
// 	{
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)  Encoder_A_EXTI++;  //��A��ĵ�ƽ����ǵ�,���������ת���1��������Ƿ�ת��1 
// 	else            Encoder_A_EXTI--;
// 	}
// 	else
// 	{
// 	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)==0)  Encoder_A_EXTI--;
// 	else            Encoder_A_EXTI++;
// 	}		
// }


// int Read_Encoder(u8 TIMX)//��ȡ��������ֵ
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
	//��ʱ��
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM2���������PWM����ע�⻻����
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//GPIO��ʼ�������ó�����ģʽ
		GPIO_InitTypeDef GPIO_InitStructre;//����ṹ��
		GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;//����������,�򸡿գ����ⲿģ���Ĭ�ϵ�ƽ
		GPIO_InitStructre.GPIO_Pin= GPIO_Pin_6|GPIO_Pin_7;
		GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructre);//����GPIO��A6
	
	
	//����ʱ����Ԫ
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//��Ƶ
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//������ʽ
		TIM_TimeBaseInitStruct.TIM_Period=65536-1;//���㻻��Ϊ����
		TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//����Ƶ
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//�ظ����������߼����������У������0����
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
		
		
		
	//�������벶��Ԫ
	
		TIM_ICInitTypeDef TIM_ICInitStruct;
		TIM_ICStructInit(&TIM_ICInitStruct);
		TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;//ѡ��ͨ��
		TIM_ICInitStruct.TIM_ICFilter=0xF;//ѡ�����벶����˲���,�˲����ƴβ���ı��źŵ�ԭ��Ƶ�ʣ���Ƶ��Ҳ�Ǽƴεĵ���ı�ԭ��Ƶ�ʣ�һ�����Ƶ��Զ�����ź�Ƶ�ʣ������ڹ��˸�Ƶ������ʹ�źŸ�ƽ��

		TIM_ICInit(TIM3,&TIM_ICInitStruct);
		//����ͨ��2
		TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;//ѡ��ͨ��
		TIM_ICInitStruct.TIM_ICFilter=0xF;//ѡ�����벶����˲���,�˲����ƴβ���ı��źŵ�ԭ��Ƶ�ʣ���Ƶ��Ҳ�Ǽƴεĵ���ı�ԭ��Ƶ�ʣ�һ�����Ƶ��Զ�����ź�Ƶ�ʣ������ڹ��˸�Ƶ������ʹ�źŸ�ƽ��

		TIM_ICInit(TIM3,&TIM_ICInitStruct);
		
		TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//1,2������,���������������ò���Ԫ��һ�£��ʿ�ɾȥ֮ǰ��//����,���������ǲ������½����Ƿ���
		
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
		//��ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);//TIM2���������PWM����ע�⻻����
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//GPIO��ʼ�������ó�����ģʽ
		GPIO_InitTypeDef GPIO_InitStructre;//����ṹ��
		GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;//����������,�򸡿գ����ⲿģ���Ĭ�ϵ�ƽ
		GPIO_InitStructre.GPIO_Pin= GPIO_Pin_8|GPIO_Pin_9;
		GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructre);//����GPIO��A6
	
	
	//����ʱ����Ԫ
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//��Ƶ
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//������ʽ
		TIM_TimeBaseInitStruct.TIM_Period=65536-1;//���㻻��Ϊ����
		TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//����Ƶ
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//�ظ����������߼����������У������0����
		TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);
		
		
		
	//�������벶��Ԫ
	
		TIM_ICInitTypeDef TIM_ICInitStruct;
		TIM_ICStructInit(&TIM_ICInitStruct);
		TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;//ѡ��ͨ��
		TIM_ICInitStruct.TIM_ICFilter=0xF;//ѡ�����벶����˲���,�˲����ƴβ���ı��źŵ�ԭ��Ƶ�ʣ���Ƶ��Ҳ�Ǽƴεĵ���ı�ԭ��Ƶ�ʣ�һ�����Ƶ��Զ�����ź�Ƶ�ʣ������ڹ��˸�Ƶ������ʹ�źŸ�ƽ��

		TIM_ICInit(TIM1,&TIM_ICInitStruct);
		//����ͨ��2
		TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;//ѡ��ͨ��
		TIM_ICInitStruct.TIM_ICFilter=0xF;//ѡ�����벶����˲���,�˲����ƴβ���ı��źŵ�ԭ��Ƶ�ʣ���Ƶ��Ҳ�Ǽƴεĵ���ı�ԭ��Ƶ�ʣ�һ�����Ƶ��Զ�����ź�Ƶ�ʣ������ڹ��˸�Ƶ������ʹ�źŸ�ƽ��

		TIM_ICInit(TIM1,&TIM_ICInitStruct);
		
		TIM_EncoderInterfaceConfig(TIM1,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);//1,2������,���������������ò���Ԫ��һ�£��ʿ�ɾȥ֮ǰ��//����,���������ǲ������½����Ƿ���
		
		TIM_Cmd(TIM1,ENABLE);
}

uint16_t ENcoderB()
{
	uint16_t temp;
	temp=TIM_GetCounter(TIM1);
	TIM_SetCounter(TIM1,0);
	return temp;
}