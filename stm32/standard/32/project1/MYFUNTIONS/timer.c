#include "stm32f10x.h"                  // Device header
extern uint16_t num;//ȫ�ֱ�������
//����ʱ��
void Timer_init()//��ʼ��TIM2��ͨ�ü�ʱ��
{
	//RCC����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	
	//ѡ��ʱ����Ԫ��ʱ��Դ
	TIM_InternalClockConfig(TIM2);
	
	
	//����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//��Ƶ
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//������ʽ
	TIM_TimeBaseInitStruct.TIM_Period=10000-1;//�Զ���װ
	TIM_TimeBaseInitStruct.TIM_Prescaler=7200-1;//Ԥ��Ƶ
	//��������7200��Ƶ�¼�10000������7200��Ƶ��10kHz�ļ���Ƶ�ʣ���0.0001s��һ���������10000������Ϊ1sһ��
	//PSC��ARR��ȡֵҪ��0��65535֮��
	//Ԥ��Ƶ���ͼ���������һ������ƫ�����Ҫ��һ��1
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//�ظ����������߼����������У������0����
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//��ȥ����ͬ�������¼������ĸ����ã��ڽ����ж�֮ǰ��һ���жϣ��������ʼ���ͽ�����һ���жϵ����
	//��������жϿ���
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
		
		
	//����NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���оƬһ��ֻ��ѡһ�ַ��飬����ѡһ���͹���
		
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=  TIM2_IRQn ;//ָ���ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;//����Ϊ2����ѡ����ռ���ȼ�Ϊ0-3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//��Ӧ���ȼ�Ҳ��0-3
	NVIC_Init(&NVIC_InitStruct);
	
	//���п���:ʹ��ʱ����ʼ����
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


//�ⲿʱ��
void Timer_Init()//��ʼ��TIM2��ͨ�ü�ʱ��
{
	//RCC����ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//RCC���ⲿҪ���ã��ں���������
	GPIO_InitTypeDef GPIO_InitStructre;//����ṹ��
	GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructre.GPIO_Pin= GPIO_Pin_0;
	GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);//����GPIO��A0
	
	//ѡ��ʱ����Ԫ��ʱ��Դ
	TIM_ETRClockMode1Config(TIM2,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,0x00);
	
	
	//����ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//��Ƶ
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//������ʽ
	TIM_TimeBaseInitStruct.TIM_Period=10-1;//�Զ���װ,�ⲿʱ�Ӽ���10�μ������ж�
	TIM_TimeBaseInitStruct.TIM_Prescaler=1-1;//Ԥ��Ƶ
	//��������7200��Ƶ�¼�10000������7200��Ƶ��10kHz�ļ���Ƶ�ʣ���0.0001s��һ���������10000������Ϊ1sһ��
	//PSC��ARR��ȡֵҪ��0��65535֮��
	//Ԥ��Ƶ���ͼ���������һ������ƫ�����Ҫ��һ��1
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//�ظ����������߼����������У������0����
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);//��ȥ����ͬ�������¼������ĸ����ã��ڽ����ж�֮ǰ��һ���жϣ��������ʼ���ͽ�����һ���жϵ����
	//��������жϿ���
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
		
		
	//����NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���оƬһ��ֻ��ѡһ�ַ��飬����ѡһ���͹���
		
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel=  TIM2_IRQn ;//ָ���ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;//����Ϊ2����ѡ����ռ���ȼ�Ϊ0-3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//��Ӧ���ȼ�Ҳ��0-3
	NVIC_Init(&NVIC_InitStruct);
	
	//���п���:ʹ��ʱ����ʼ����
	TIM_Cmd(TIM2,ENABLE);
}

uint16_t Time_getcount()
{
	return TIM_GetCounter(TIM2);
}