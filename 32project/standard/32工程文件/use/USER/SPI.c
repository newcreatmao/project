#include"SPI.h"

/*******************************************************************************
* Function Name : SPI_FLASH_Init
* Description : Initializes the peripherals used by the SPI FLASH driver.
* Input : None
* Output : None
* Return : None
*******************************************************************************/
void SPI_SD_Init(void)
{
 
		GPIO_InitTypeDef GPIO_InitStructure;
		 
		/* ʹ��SPI��Ӧ���ŵ�ʱ�� ʹ��SPI1��ʱ�� */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
		 
		/*����SPI��ʱ����SCK��SPI��MOSI�ߺ�SPI��MISO�� */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //���ù��ܵ��������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/*����SPI��Ƭѡ�ߣ�CSN */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/* ����CSN���ţ�ֹͣʹ��SD*/
		GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_8);
		GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
		 
		// ����SPI,ʹ���ʺ�SD������
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //˫��˫��ȫ˫��
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //������
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//8λ���ݳ���
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //ʱ������ʱΪ��
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //���ݲ����ڵ�2��ʱ����
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS�ź����ⲿ�ܽŹ���
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//������Ԥ��ƵֵΪ4
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //���ݴ���ĵ�һ���ֽ�ΪMSB
		SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC�Ķ���ʽ
		SPI_Init(SPI1, &SPI_InitStructure);
		/* ʹ��SPI1 */
		SPI_Cmd(SPI1, ENABLE);
}
 
/*******************************************************************************
* Function Name : SPI_FLASH_SendByte
* Description : ����һ�����ݣ�ͬʱ���մ�FLASH������������
* Input : byte : byte to send.
* Output : None
* Return : The value of the received byte.
*******************************************************************************/
u8 SPIx_ReadWriteByte(u8 byte)
{
		/* �ȴ����ݷ��ͼĴ������ */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		 
		/* ͨ��SPI���ͳ�ȥһ���ֽ����� */
		SPI_I2S_SendData(SPI1, byte);
		 
		/* �ȴ����յ�һ�����ݣ����յ�һ�����ݾ��൱�ڷ���һ��������ϣ� */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		 
		/* ���ؽ��յ������� */
		return SPI_I2S_ReceiveData(SPI1);
}
 
/*******************************************************************************
* Function Name : SPI_FLASH_SendHalfWord
* Description : ���Ͳ�����һ���������ݣ�16λ��
* Input : Half Word : Half Word to send.
* Output : None
* Return : The value of the received Half Word.
*******************************************************************************/
u16 SPIx_ReadWriteHalfWord(u16 HalfWord)
{
		/* �ȴ����ݷ��ͼĴ������ */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		 
		/* ͨ��SPI���ͳ�ȥ����ֵ����� */
		SPI_I2S_SendData(SPI1, HalfWord);
		 
		/* �ȴ����յ�һ���������ݣ����յ�һ�����ݾ��൱�ڷ���һ��������ϣ� */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		 
		/* ���ؽ��յ������� */
		return SPI_I2S_ReceiveData(SPI1);
}
//SPI �ٶ����ú���
//SpeedSet:
//SPI_BaudRatePrescaler_2 2��Ƶ (SPI36M@sys72M)
//SPI_BaudRatePrescaler_8 8��Ƶ (SPI9M@sys72M)
//SPI_BaudRatePrescaler_16 16��Ƶ (SPI4.5M@sys72M)
//SPI_BaudRatePrescaler_256 256��Ƶ (SPI281.25K@sys72M)
 
void SPIx_SetSpeed(u8 SpeedSet)
{
		SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
		SPI_Init(SPI1, &SPI_InitStructure);
		SPI_Cmd(SPI1,ENABLE);
}
 
/******************************END OF INIT_SPI*****************************/