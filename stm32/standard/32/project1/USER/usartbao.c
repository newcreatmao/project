#include "stm32f10x.h"                  // Device header
uint8_t RXData1,RXFlag1;  
uint8_t TXPacket[4];
uint8_t RXPacket[4];

void USART_INIT_baoRX()//中断接收模式
{
	//开启时钟，打开GPIO和USART
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	//GPIO初始化，tx复用输出，Rx输入
	GPIO_InitTypeDef GPIO_InitStructre;//定义结构体
	GPIO_InitStructre.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructre.GPIO_Pin= GPIO_Pin_9;
	GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);//开启GPIO
	//TX
	GPIO_InitStructre.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructre.GPIO_Pin= GPIO_Pin_10;
	GPIO_InitStructre.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructre);//开启GPIO
	//RX
	//配置USART
	USART_InitTypeDef USART_Initstruture;
	USART_Initstruture.USART_BaudRate=9600;//波特率
	USART_Initstruture.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Initstruture.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;//发送和接收模式
	USART_Initstruture.USART_Parity=USART_Parity_No;//校验位
	USART_Initstruture.USART_StopBits=USART_StopBits_1;//停止位
	USART_Initstruture.USART_WordLength=USART_WordLength_8b;//字长，无校验
	USART_Init(USART1,&USART_Initstruture);
	
	//发送则开启USART，接收则需要配置中断，即ITconfig和NVIC配置
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//这个芯片一次只能选一种分组，所以选一个就够了
		
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel= USART1_IRQn ;//指定中断通道
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;//分组为2，可选的抢占优先级为0-3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;//响应优先级也是0-3
	NVIC_Init(&NVIC_InitStruct);
	
	USART_Cmd(USART1,ENABLE);
}//可在中断函数里接收数据

void sendbyte1(uint8_t byte)
{
	USART_SendData(USART1,byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//等待TXE置一，确保数据发送完成
	//不需要手动清零，下次调用会自动清零,发完自动清零
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
	sendbyte1(0xFF);//定义的包头
	
	sendarray1(TXPacket,4);
	sendbyte1(0xFE);//定义的包尾
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


