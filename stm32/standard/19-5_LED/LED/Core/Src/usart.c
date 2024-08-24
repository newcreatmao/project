/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.c
  * @brief   This file provides code for the configuration
  *          of the USART instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
typedef struct __FILE FILE;
extern uint8_t Usart1_ReadBuf[255];	//����1 ��������
extern uint8_t Usart1_ReadCount;	//����1 �����ֽڼ���

extern int8_t g_cThisState ;//���״̬

extern uint8_t g_ucUsart2ReceiveData;  //���洮�ڶ����յ�����

 uint8_t state = 0;//���徲̬static ����
 
int g_lHW_State = 0;//�����Ӿ����� ���ڱ�ʾ����Թܻ����Ӿ�����ͷʶ��״̬

uint8_t g_ucaUsart2ReceiveBuffer[10];//���洮�ڽ�����Ч���ݵ�����
uint8_t g_ucUsart2ReceivCounter=0;//���ڽ��ռ���ֵ
	
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}
/* USART3 init function */

void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspInit 0 */

  /* USER CODE END USART3_MspInit 0 */
    /* USART3 clock enable */
    __HAL_RCC_USART3_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* USART3 interrupt Init */
    HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspInit 1 */

  /* USER CODE END USART3_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART3)
  {
  /* USER CODE BEGIN USART3_MspDeInit 0 */

  /* USER CODE END USART3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART3_CLK_DISABLE();

    /**USART3 GPIO Configuration
    PB10     ------> USART3_TX
    PB11     ------> USART3_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);

    /* USART3 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART3_IRQn);
  /* USER CODE BEGIN USART3_MspDeInit 1 */

  /* USER CODE END USART3_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
* @brief �ض���printf (�ض���fputc)��
					ʹ��ʱ��ǵù�ѡ��ħ����->Target->UseMicro LIB 
					������Ҫ��C�ļ���typedef struct __FILE FILE;
					��������ļ�#include "stdio.h"
* @param 
* @return 
*/
int fputc(int ch,FILE *stream)
{
	HAL_UART_Transmit(&huart1,( uint8_t *)&ch,1,0xFFFF);//huart1����Ϊ�������ھͻ��ض�����������
	return ch;
}
//�жϷ������һ֡����
uint8_t Usart_WaitReasFinish(void)
{
	static uint16_t Usart_LastReadCount = 0;//��¼�ϴεļ���ֵ
	if(Usart1_ReadCount == 0)
	{
		Usart_LastReadCount = 0;//�������ֵ
		return 1;//��ʾû���ڽ�������
	}
	if(Usart1_ReadCount == Usart_LastReadCount)//�����μ���ֵ�����ϴμ���ֵ
	{
		Usart1_ReadCount = 0;//��������������ֵ
		Usart_LastReadCount = 0;//����ϴμ���ֵ
		return 0;//�Ѿ����������
	}
	Usart_LastReadCount = Usart1_ReadCount;//��μ���ֵ��ֵ���ϴμ���ֵ
	return 2;//��ʾ���ڽ�����
}
/*******************
*  @brief  ����ͷ����Э��������� ��������K210��openmv��
*  @param  data:���ڽ��յ���ÿ���ֽ�
*  @return  
*
*******************/
void usartCamera_Receive_Data(uint8_t data)
{
	static uint8_t state = 0;//���徲̬static ����
	
	if(state==0&&data==0xA5) //�жϵ�һ���ǲ���֡ͷ0xA5
	{
		state=1;//��֡ͷ0xA5 ��ֵstate=1 ��ʾ������һ������
		//���ݴ洢�������� "g_ucUsart2ReceivCounter++",���������ú�ӣ�����g_ucUsart2ReceivCounter ��ֵΪ0��ִ���������g_ucaUsart2ReceiveBuffer[0]=data��Ȼ��g_ucUsart2ReceivCounter++������g_ucUsart2ReceivCounter = 1��
		g_ucaUsart2ReceiveBuffer[g_ucUsart2ReceivCounter++] = data;
	}
	else if(state==1&&data==0xA6) //�ڶ����ǲ���֡ͷ0xA6
	{
		state=2;//����ڶ�����֡ͷ0xA6 ��ֵstate=2 ��ʾ������һ������
		g_ucaUsart2ReceiveBuffer[g_ucUsart2ReceivCounter++] = data;//��������
	}
	else if(state==2)//Ȼ��ȷ����ͷ��0XA5 0XA6 �Ϳ�ʼ����
	{
		g_ucaUsart2ReceiveBuffer[g_ucUsart2ReceivCounter++]=data;
		if(g_ucUsart2ReceivCounter>9||data==0x5B) state=3;  //���մ���9�����߽��յ�֡β0X5B ����λ״̬��
	}
	else if(state==3) //״̬��
	{
		if(g_ucaUsart2ReceiveBuffer[g_ucUsart2ReceivCounter-1] == 0x5B)  //ȷ�� ���һ���ǲ���0x5B֡β ��֡β0x5B ����Ϊͨ����ȷ ��������
		{
			state = 0;					//����Ϳ��Դ��������ˡ�������ǵ������������ñ�־λ�����ֵ
			g_ucUsart2ReceivCounter = 0;//�������ֵ
			//��������������ú�����תƫ��״̬

			//1.���ÿ��� �����ұ� ��� ���ִ洢�ı�������: [0]��[1]:֡ͷ��[2]:����ͷ�������һ������Ȥ����[3]:��ߵڶ�����[4]:��ߵ�������[5]:��ߵ��ĸ���[6]:��ߵ������[7]:֡β
				 if(g_ucaUsart2ReceiveBuffer[6]==0&&g_ucaUsart2ReceiveBuffer[5]==0&&g_ucaUsart2ReceiveBuffer[3]==0&&g_ucaUsart2ReceiveBuffer[2]==0)
				 {
					g_cThisState=0;//ǰ��
					g_lHW_State=22222;//���������ʾ��OLED�Ϸ������ ���ֵ �Դ˴������ұ�ʾ �������ҵ��������
				 }
				 if(g_ucaUsart2ReceiveBuffer[6]==0&&g_ucaUsart2ReceiveBuffer[5]==1&&g_ucaUsart2ReceiveBuffer[3]==0&&g_ucaUsart2ReceiveBuffer[2]==0)
				 {
					g_cThisState=-1;//Ӧ����ת
					g_lHW_State=22212;	//��ʾ�����ڶ��� ʶ����
				 }
				 if(g_ucaUsart2ReceiveBuffer[6]==1&&g_ucaUsart2ReceiveBuffer[5]==0&&g_ucaUsart2ReceiveBuffer[3]==0&&g_ucaUsart2ReceiveBuffer[2]==0)
				 {g_cThisState=-2;//������ת
				 g_lHW_State=22221;
				 }
				 if(g_ucaUsart2ReceiveBuffer[6]==1&&g_ucaUsart2ReceiveBuffer[5]==1&&g_ucaUsart2ReceiveBuffer[3]==0&&g_ucaUsart2ReceiveBuffer[2]==0)
				 {g_cThisState=-3;//������ת
				 g_lHW_State=22211;
				 }
				 if(g_ucaUsart2ReceiveBuffer[6]==0&&g_ucaUsart2ReceiveBuffer[5]==0&&g_ucaUsart2ReceiveBuffer[3]==1&&g_ucaUsart2ReceiveBuffer[2]==0)
				 {g_cThisState=1;//Ӧ����ת
				 g_lHW_State=21222;
				 }
                 if(g_ucaUsart2ReceiveBuffer[6]==0&&g_ucaUsart2ReceiveBuffer[5]==0&&g_ucaUsart2ReceiveBuffer[3]==0&&g_ucaUsart2ReceiveBuffer[2]==1)
				 {g_cThisState=2;//������ת
				 g_lHW_State=12222;
				 }
                 if(g_ucaUsart2ReceiveBuffer[6]==0&&g_ucaUsart2ReceiveBuffer[5]==0&&g_ucaUsart2ReceiveBuffer[3]==1&&g_ucaUsart2ReceiveBuffer[2]==1)
				 {g_cThisState=3;//������ת
				 g_lHW_State=11222;
				 }

				//2.Ȼ���������
				for(int i=0;i<10;i++) g_ucaUsart2ReceiveBuffer[i]=0x00;//�������
				
		}
		else //����֡β˵��ͨ�Ŵ������¿�ʼ����
		{
			state=0;
			g_ucUsart2ReceivCounter =0;
			for(int i=0;i<10;i++) g_ucaUsart2ReceiveBuffer[i]=0x00;//�������
		}
	}
	else
	{	//�����쳣���
		state=0;
		g_ucUsart2ReceivCounter =0;
		for(int i=0;i<10;i++) g_ucaUsart2ReceiveBuffer[i]=0x00;//�������
	}
}

/* UART ����ص����� �����ڴ��� */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if(__HAL_UART_GET_FLAG(huart,UART_FLAG_ORE) != RESET) //ʹ��__HAL_UART_GET_FLAG����UART��overrun�����־λ�Ƿ���λ���������ֵ������RESET����ʾoverrun�����־λ����λ����������overrun����
    {
        __HAL_UART_CLEAR_OREFLAG(huart);//ʹ��__HAL_UART_CLEAR_OREFLAG�����UART��overrun�����־λ
        HAL_UART_Receive_IT(&huart2,&g_ucUsart2ReceiveData,1);  //ʹ��HAL�⺯������UART2�����жϣ������ý��ջ������Ĵ�СΪ1�ֽ�
    }
}


/* USER CODE END 1 */
