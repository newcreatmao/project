#include"motor.h"


void ENA_PWMInit()
{
		//RCC����ʱ�ӣ�TIM��GPIO
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	//����ʱ����Ԫ
		TIM_InternalClockConfig(TIM2);
	
		TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
		TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;//��Ƶ
		TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//������ʽ
		TIM_TimeBaseInitStruct.TIM_Period=100-1;//�Զ���װ,arr,�̶�Ϊ100-1����ccr��ֱֵ�Ӿ���ռ�ձȣ��Ϻü��㣬�ֱ���Ϊ1%
		TIM_TimeBaseInitStruct.TIM_Prescaler=720-1;//Ԥ��Ƶ,psc����ͨ���ı�
		TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//�ظ����������߼����������У������0����
		TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	
	//��������Ƚϵ�Ԫ
		TIM_OCInitTypeDef TIM_OCInitStruct;
	    TIM_OCStructInit(&TIM_OCInitStruct);//���ṹ���Ա����ʼֵ����ֹת�ø߼���ʱ��ʱ��δ��������Ա��ֵ����������
		//TIM_OCInitStruct.TIM_OCIdleState=Idle�߼���ʱ������Ҫ��
	
		TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;//PWM1ģʽ//��������Ƚϵ�ģʽ//TIM_SelectOCxM�����޸�����Ƚ�ģʽ
	
		//TIM_OCInitStruct.TIM_OCNIdleState=��N�ı�ʾ�л���ͨ����һ��߼���ʱ������Ҫ��
		//TIM_OCInitStruct.TIM_OCNPolarity=
		
		TIM_OCInitStruct.TIM_OCPolarity=TIM_OCNPolarity_High;//�߼���//��������Ƚϵļ���//TIM_OC1PolarityConfig�������ü���
		//TIM_OCInitStruct.TIM_OutputNState=
		
		TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//�������ʹ��
		
		TIM_OCInitStruct.TIM_Pulse=0;//����CCR,ccr,Ҫ����,ռ�ձ�ccr/(arr+1)
		
		TIM_OC1Init(TIM2,&TIM_OCInitStruct);//��ʼ��OC1ͨ�������ֲ�����ѡ��
	//����GPIO
		GPIO_InitTypeDef GPIO_InitStructre;//����ṹ��
		GPIO_InitStructre.GPIO_Mode=GPIO_Mode_AF_PP;//��������������ö�ʱ����������
		GPIO_InitStructre.GPIO_Pin= GPIO_Pin_0;
		GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStructre);//����GPIO��A0
	//���п���
		TIM_Cmd(TIM2,ENABLE);//������ʱ��
}

void Motor_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2| GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void PWMCCR(uint16_t CCR)//�޸�ռ�ձȣ�ע��ռ�ձ���ccr��arr��ͬȷ����
{
	TIM_SetCompare1(TIM2,CCR);//��������CCR�Ĵ�����ֵ
}

void PWMPSC(uint16_t PSC)
{
	TIM_PrescalerConfig(TIM2,PSC,TIM_PSCReloadMode_Immediate);//д��PSC��ֵ,�����¼��ܱ����һ������
}

void moto(int i,int j) //i=0��ת i=1��ת jΪת�� ���100
{
	if(i==1)
	{
		PWMCCR(j);//ע��˳��
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
		GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
	}
	if(i==0)
	{
		PWMCCR(j);//ע��˳��
		GPIO_SetBits(GPIOA, GPIO_Pin_3);
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		GPIO_SetBits(GPIOA, GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	}
}
