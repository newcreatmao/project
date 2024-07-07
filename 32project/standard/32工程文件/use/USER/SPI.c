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
		 
		/* 使能SPI对应引脚的时钟 使能SPI1的时钟 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
		 
		/*配置SPI的时钟线SCK和SPI的MOSI线和SPI的MISO线 */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用功能的推挽输出
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/*配置SPI的片选线：CSN */
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_8;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//推挽输出
		GPIO_Init(GPIOA, &GPIO_InitStructure);
		/* 拉高CSN引脚，停止使能SD*/
		GPIO_SetBits(GPIOA,GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_8);
		GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
		 
		// 配置SPI,使它适合SD的特性
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //双线双向全双工
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //主器件
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;//8位数据长度
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //时钟悬空时为高
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //数据捕获于第2个时钟沿
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS信号由外部管脚管理
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;//波特率预分频值为4
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //数据传输的第一个字节为MSB
		SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC的多项式
		SPI_Init(SPI1, &SPI_InitStructure);
		/* 使能SPI1 */
		SPI_Cmd(SPI1, ENABLE);
}
 
/*******************************************************************************
* Function Name : SPI_FLASH_SendByte
* Description : 发送一个数据，同时接收从FLASH返回来的数据
* Input : byte : byte to send.
* Output : None
* Return : The value of the received byte.
*******************************************************************************/
u8 SPIx_ReadWriteByte(u8 byte)
{
		/* 等待数据发送寄存器清空 */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		 
		/* 通过SPI发送出去一个字节数据 */
		SPI_I2S_SendData(SPI1, byte);
		 
		/* 等待接收到一个数据（接收到一个数据就相当于发送一个数据完毕） */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		 
		/* 返回接收到的数据 */
		return SPI_I2S_ReceiveData(SPI1);
}
 
/*******************************************************************************
* Function Name : SPI_FLASH_SendHalfWord
* Description : 发送并接受一个半字数据（16位）
* Input : Half Word : Half Word to send.
* Output : None
* Return : The value of the received Half Word.
*******************************************************************************/
u16 SPIx_ReadWriteHalfWord(u16 HalfWord)
{
		/* 等待数据发送寄存器清空 */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
		 
		/* 通过SPI发送出去半个字的数据 */
		SPI_I2S_SendData(SPI1, HalfWord);
		 
		/* 等待接收到一个半字数据（接收到一个数据就相当于发送一个数据完毕） */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
		 
		/* 返回接收到的数据 */
		return SPI_I2S_ReceiveData(SPI1);
}
//SPI 速度设置函数
//SpeedSet:
//SPI_BaudRatePrescaler_2 2分频 (SPI36M@sys72M)
//SPI_BaudRatePrescaler_8 8分频 (SPI9M@sys72M)
//SPI_BaudRatePrescaler_16 16分频 (SPI4.5M@sys72M)
//SPI_BaudRatePrescaler_256 256分频 (SPI281.25K@sys72M)
 
void SPIx_SetSpeed(u8 SpeedSet)
{
		SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
		SPI_Init(SPI1, &SPI_InitStructure);
		SPI_Cmd(SPI1,ENABLE);
}
 
/******************************END OF INIT_SPI*****************************/