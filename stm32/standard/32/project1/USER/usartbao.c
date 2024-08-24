#include "stm32f10x.h"                  // Device header
uint8_t RXData1,RXFlag1;  
uint8_t TXPacket[4];
uint8_t RXPacket[4];

void USART_INIT_baoRX()//�жϽ���ģʽ
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

void sendbyte1(uint8_t byte)
{
	USART_SendData(USART1,byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//�ȴ�TXE��һ��ȷ�����ݷ������
	//����Ҫ�ֶ����㣬�´ε��û��Զ�����,�����Զ�����
}

void sendarray1(uint8_t *array,uint16_t length)
{
	uint16_t i;
	for(i=0;i<length;i++)
	{
		sendbyte1(array[i]);
	}
}

void sendpacket1()
{
	sendbyte1(0xFF);//����İ�ͷ
	
	sendarray1(TXPacket,4);
	sendbyte1(0xFE);//����İ�β
}



uint8_t GETRX_flag1(void)
{
	if(RXFlag1==1)
	{
		RXFlag1=0;
		return 1;
	}
	return 0;
}


void USART1_IRQGandler(void)
{
	static uint8_t stat=0,count=0;
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET)
	{
		uint8_t RXDATA=USART_ReceiveData(USART1);
		if(stat==0)
		{
			if(RXDATA==0xFF)
			{
				stat=1;
				count=0;
			}
		}
		else if(stat==1)
		{
			RXPacket[count]=RXDATA;
			count++;
			if(count>=4)
			{stat=2;}
		}
		else if(stat==2)
		{
			if(RXDATA==0xFE)
			{
				stat=0;
				RXFlag1=1;
			}
		}
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}


