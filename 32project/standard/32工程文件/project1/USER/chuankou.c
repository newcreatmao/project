#include "stm32f10x.h"       
uint8_t RXData,RXFlag;           // Device header
void USART_INIT_TX()//发送模式
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
	
	//配置USART
	USART_InitTypeDef USART_Initstruture;
	USART_Initstruture.USART_BaudRate=9600;//波特率
	USART_Initstruture.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Initstruture.USART_Mode=USART_Mode_Tx;//发送模式
	USART_Initstruture.USART_Parity=USART_Parity_No;//校验位
	USART_Initstruture.USART_StopBits=USART_StopBits_1;//停止位
	USART_Initstruture.USART_WordLength=USART_WordLength_8b;//字长，无校验
	USART_Init(USART1,&USART_Initstruture);
	//只有发送模式
	
	//发送则开启USART，接收则需要配置中断，即ITconfig和NVIC配置
	USART_Cmd(USART1,ENABLE);
}

void sendbyte(uint8_t byte)
{
	USART_SendData(USART1,byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);//等待TXE置一，确保数据发送完成
	//不需要手动清零，下次调用会自动清零,发完自动清零
}

void USART_INIT_RX()//接收+发送模式
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
	USART_Cmd(USART1,ENABLE);
}

//接受查询
unsigned char revice()
{
	unsigned char mm;
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==SET)
	{
		mm=USART_ReceiveData(USART1);//读完自动清零
		RXFlag=1;
		return mm;
	}
}


void USART_INIT_interRX()//中断接收模式
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