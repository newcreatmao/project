#include"Ic.h"
void PWMIC_init()
{
	//��ʱ��
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//TIM2���������PWM����ע�⻻����
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//GPIO��ʼ�������ó�����ģʽ
		GPIO_InitTypeDef GPIO_InitStructre;//����ṹ��
		GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;//��������
		GPIO_InitStructre.GPIO_Pin= GPIO_Pin_6;
		GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructre);//����GPIO��A6
	
	
	//����ʱ����Ԫ
		TIM_InternalClockConfig(TIM3);
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//��Ƶ
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//������ʽ
		TIM_TimeBaseInitStruct.TIM_Period=65536-1;//��ֹ�������
		TIM_TimeBaseInitStruct.TIM_Prescaler=72-1;
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//�ظ����������߼����������У������0����
		TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
		
		
	//�������벶��Ԫ
	
		TIM_ICInitTypeDef TIM_ICInitStruct;
		TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;//ѡ��ͨ��
		TIM_ICInitStruct.TIM_ICFilter=0xF;//ѡ�����벶����˲���,�˲����ƴβ���ı��źŵ�ԭ��Ƶ�ʣ���Ƶ��Ҳ�Ǽƴεĵ���ı�ԭ��Ƶ�ʣ�һ�����Ƶ��Զ�����ź�Ƶ�ʣ������ڹ��˸�Ƶ������ʹ�źŸ�ƽ��
		TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;//����
		TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;//���ô����źŷ�Ƶ��������Ƶ��ÿ���źŶ���Ч,����Ƶ��ÿ��һ����Чһ��
		TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;//ѡ�񴥷��źŵ��������ţ�ֱ��ͨ��
		//����һ������һ��ͨ��
		/*TIM_ICInitStruct.TIM_Channel=TIM_Channel_2;//ѡ��ͨ��
		TIM_ICInitStruct.TIM_ICFilter=0xF;//ѡ�����벶����˲���,�˲����ƴβ���ı��źŵ�ԭ��Ƶ�ʣ���Ƶ��Ҳ�Ǽƴεĵ���ı�ԭ��Ƶ�ʣ�һ�����Ƶ��Զ�����ź�Ƶ�ʣ������ڹ��˸�Ƶ������ʹ�źŸ�ƽ��
		TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Falling;//����
		TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;//���ô����źŷ�Ƶ��������Ƶ��ÿ���źŶ���Ч,����Ƶ��ÿ��һ����Чһ��
		TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_IndirectTI;//ѡ�񴥷��źŵ��������ţ�����ͨ��*/
		//�������ú���
		TIM_PWMIConfig(TIM3,&TIM_ICInitStruct);//���Զ���ʣ�µ�ͨ���ͼ������ó����裬ֻ֧��ͨ��1��2
		
		TIM_ICInit(TIM3,&TIM_ICInitStruct);
	
	
	//ѡ���ģʽ�Ĵ���Դ
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI1FP1);//��Ӧ��ģʽ�Ķ�Ӧͨ��
	//ѡ�񴥷�֮��ִ�еĲ���
	TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);//����ģʽ���reset
	
	//�򿪶�ʱ��
	TIM_Cmd(TIM3,ENABLE);
}

uint32_t ICgetHZ()//Ƶ��
{
	return 1000000/(TIM_GetCapture1(TIM3)+1);//1MHZ
}

uint32_t ICgetDUTY()//ռ�ձ�
{
	return ((TIM_GetCapture2(TIM3)*100)/TIM_GetCapture1(TIM3)+1);
}