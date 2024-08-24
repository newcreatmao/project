#include "stm32f10x.h"                  // Device header
void bianma_init()
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

uint16_t ENcoder()
{
	uint16_t temp;
	temp=TIM_GetCounter(TIM3);
	TIM_SetCounter(TIM3,0);
	return temp;
	
}