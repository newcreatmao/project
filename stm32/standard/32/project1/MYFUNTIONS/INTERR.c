#include "stm32f10x.h"                  // Device header
#include"Delay.h"
uint16_t countset;

void countsensor_init()
{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//����GPIOBʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//����AFIO
	
		GPIO_InitTypeDef GPIO_InitStructre;//����ṹ��
		GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;//exti�Ƽ��������룬���������룬�򸡿����룬ipu��������
		GPIO_InitStructre.GPIO_Pin= GPIO_Pin_14;
		GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_Init(GPIOB,&GPIO_InitStructre);//����GPIO
	
		GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource14);//AFIO�����ж���������
	
	
		EXTI_InitTypeDef EXTI_InitStructre;
		EXTI_InitStructre.EXTI_Line=EXTI_Line14;//ָ���ж���
		EXTI_InitStructre.EXTI_LineCmd=ENABLE;//ָ���ж��ߵĿ���
		EXTI_InitStructre.EXTI_Mode=EXTI_Mode_Interrupt;//�ж�ģʽ
		EXTI_InitStructre.EXTI_Trigger=EXTI_Trigger_Falling;//�½��ش���
		EXTI_Init(&EXTI_InitStructre);//EXTI����
		//�ⲿ�ж�����
	
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���оƬһ��ֻ��ѡһ�ַ��飬����ѡһ���͹���
		
		NVIC_InitTypeDef NVIC_InitStruct;
		NVIC_InitStruct.NVIC_IRQChannel= EXTI15_10_IRQn;//ָ���ж�ͨ��
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//����Ϊ2����ѡ����ռ���ȼ�Ϊ0-3
		NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//��Ӧ���ȼ�Ҳ��0-3
		NVIC_Init(&NVIC_InitStruct);
		//�ڲ��ж�����
		
		//IO��->AFIO->EXYI->NVIC->cpu
}

uint16_t countsensor_get()
{
	return countset;
}

void EXTI15_10_IRQHandler()//�жϺ�������Ҫ������ѡ�ж��ߵ������ļ�Ѱ��
{
	if(EXTI_GetITStatus(EXTI_Line14) == SET)//�ж��Ƿ����14�ߣ�SET��ʾ��
	{
		countset++;
		Delay_ms(50);
		EXTI_ClearITPendingBit(EXTI_Line14);//���жϱ�־λ���������һֱ��1�����������жϣ������ѭ��
	}
}//�жϺ���������ͷ�ļ������������Զ����õ�