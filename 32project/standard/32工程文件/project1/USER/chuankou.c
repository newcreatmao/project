#include "stm32f10x.h"       
uint8_t RXData,RXFlag;           // Device header
void USART_INIT_TX()//����ģʽ
{
	//����ʱ�ӣ���GPIO��USART
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//GPIO��ʼ����tx���������Rx����
	GPIO_InitTypeDef GPIO_InitStructre;//����ṹ��
	GPIO_InitStructre.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructre.GPIO_Pin= GPIO_Pin_9;
	GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);//����GPIO
	
	//����USART
	USART_InitTypeDef USART_Initstruture;
	USART_Initstruture.USART_BaudRate=9600;//������
	USART_Initstruture.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Initstruture.USART_Mode=USART_Mode_Tx;//����ģʽ
	USART_Initstruture.USART_Parity=USART_Parity_No;//У��λ
	USART_Initstruture.USART_StopBits=USART_StopBits_1;//ֹͣλ
	USART_Initstruture.USART_WordLength=USART_WordLength_8b;//�ֳ�����У��
	USART_Init(USART1,&USART_Initstruture);
	//ֻ�з���ģʽ
	
	//��������USART����������Ҫ�����жϣ���ITconfig��NVIC����
	USART_Cmd(USART1,ENABLE);
}

void sendbyte(uint8_t byte)
{
	USART_SendData(USART1,byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//�ȴ�TXE��һ��ȷ�����ݷ������
	//����Ҫ�ֶ����㣬�´ε��û��Զ�����,�����Զ�����
}

void USART_INIT_RX()//����+����ģʽ
{
	//����ʱ�ӣ���GPIO��USART
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//GPIO��ʼ����tx���������Rx����
	GPIO_InitTypeDef GPIO_InitStructre;//����ṹ��
	GPIO_InitStructre.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructre.GPIO_Pin= GPIO_Pin_9;
	GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);//����GPIO
	//TX
	GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructre.GPIO_Pin= GPIO_Pin_10;
	GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);//����GPIO
	//RX
	//����USART
	USART_InitTypeDef USART_Initstruture;
	USART_Initstruture.USART_BaudRate=9600;//������
	USART_Initstruture.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Initstruture.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;//���ͺͽ���ģʽ
	USART_Initstruture.USART_Parity=USART_Parity_No;//У��λ
	USART_Initstruture.USART_StopBits=USART_StopBits_1;//ֹͣλ
	USART_Initstruture.USART_WordLength=USART_WordLength_8b;//�ֳ�����У��
	USART_Init(USART1,&USART_Initstruture);
	
	//��������USART����������Ҫ�����жϣ���ITconfig��NVIC����
	USART_Cmd(USART1,ENABLE);
}

//���ܲ�ѯ
unsigned char revice()
{
	unsigned char mm;
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==SET)
	{
		mm=USART_ReceiveData(USART1);//�����Զ�����
		RXFlag=1;
		return mm;
	}
}


void USART_INIT_interRX()//�жϽ���ģʽ
{
	//����ʱ�ӣ���GPIO��USART
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//GPIO��ʼ����tx���������Rx����
	GPIO_InitTypeDef GPIO_InitStructre;//����ṹ��
	GPIO_InitStructre.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructre.GPIO_Pin= GPIO_Pin_9;
	GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);//����GPIO
	//TX
	GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructre.GPIO_Pin= GPIO_Pin_10;
	GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);//����GPIO
	//RX
	//����USART
	USART_InitTypeDef USART_Initstruture;
	USART_Initstruture.USART_BaudRate=9600;//������
	USART_Initstruture.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Initstruture.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;//���ͺͽ���ģʽ
	USART_Initstruture.USART_Parity=USART_Parity_No;//У��λ
	USART_Initstruture.USART_StopBits=USART_StopBits_1;//ֹͣλ
	USART_Initstruture.USART_WordLength=USART_WordLength_8b;//�ֳ�����У��
	USART_Init(USART1,&USART_Initstruture);
	
	//��������USART����������Ҫ�����жϣ���ITconfig��NVIC����
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//���оƬһ��ֻ��ѡһ�ַ��飬����ѡһ���͹���
		
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel= USART1_IRQn ;//ָ���ж�ͨ��
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//����Ϊ2����ѡ����ռ���ȼ�Ϊ0-3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//��Ӧ���ȼ�Ҳ��0-3
	NVIC_Init(&NVIC_InitStruct);
	
	USART_Cmd(USART1,ENABLE);
}//�����жϺ������������

uint8_t GETRX_flag(void)
{
	if(RXFlag==1)
	{
		RXFlag=0;
		return 1;
	}
	return 0;
}

uint8_t GET_data(void)
{
	return RXData;
}

//void USART1_IRQGandler(void)
//{

//	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
//	{
//		RXData=USART_ReceiveData(USART1);
//		RXFlag=1;
//	}
//}