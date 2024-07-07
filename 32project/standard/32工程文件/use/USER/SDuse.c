#include"SDuse.h"

/******************************START OF SD_OPERATION***********************/
/*******************************************************************************
* 函数名称 : SD_Select
* 功能描述 : 选择SD卡，并等待SD卡准备好
* 进入参数 : 无.
* 返回参数 : 0：成功 1：失败
* 备注说明 : SD卡准备好会返回0XFF
*******************************************************************************/
u8 SD_Select(void)
{
		uint32_t t=0;
		SD_CS(OFF);//片选SD，低电平使能
		do
		{
		if(SD_SPI_ReadWriteByte(0XFF)==0XFF)return 0;//OK
		t++;
		}while(t<0XFFFFFF);//等待
		SD_DisSelect(); //释放总线
		return 1;//等待失败
}
/*******************************************************************************
* 函数名称 : SD_RecvData
* 功能描述 : 从sd卡读取一个数据包的内容
* 进入参数 : buf：数据缓存数组 len要读取的数据的长度
* 返回参数 : 0：成功 其他：失败
* 备注说明 : 读取时需要等待SD卡发送数据起始令牌0XFE
*******************************************************************************/
u8 SD_RecvData(u8*buf,u16 len)
{
		u16 Count=0xF000;//等待次数
		while ((SD_SPI_ReadWriteByte(0XFF)!=0xFE)&&Count)Count--;//等待得到读取数据令牌0xfe
		if (Count==0) return MSD_RESPONSE_FAILURE;//获取令牌失败,返回0XFF
		while(len--)//开始接收数据
		{
		*buf=SPIx_ReadWriteByte(0xFF);
		buf++;
}
//下面是2个伪CRC（dummy CRC），假装接收了2个CRC
SD_SPI_ReadWriteByte(0xFF);
SD_SPI_ReadWriteByte(0xFF);
return 0;//读取成功
}
/*******************************************************************************
* 函数名称 : SD_SendBlock
* 功能描述 : 向sd卡写入一个数据包的内容 512字节
* 进入参数 : buf:数据缓存区 cmd:数据发送的令牌
* 返回参数 : 0：成功 其他：失败
* 备注说明 : 写数据时需要先发送数据起始令牌0XFE/0XFC/0XFD
*******************************************************************************/
u8 SD_SendBlock(u8*buf,u8 cmd)
{
		u32 t,Count=0XFFFFFF;
		while ((SD_SPI_ReadWriteByte(0XFF)!=0xFF)&&Count)Count--;//等待SD卡准备好
		if (Count==0) return MSD_RESPONSE_FAILURE;//SD卡未准备好，失败，返回
		SD_SPI_ReadWriteByte(cmd);//发送数据起始或停止令牌
		if(cmd!=0XFD)//在不是结束令牌的情况下，开始发送数据
		{
		for(t=0;t<512;t++)SPIx_ReadWriteByte(buf[t]);//提高速度,减少函数传参时间
		SD_SPI_ReadWriteByte(0xFF);//发送2字节的CRC
		SD_SPI_ReadWriteByte(0xFF);
		t=SD_SPI_ReadWriteByte(0xFF);//紧跟在CRC之后接收数据写的状态
		if((t&0x1F)!=0x05)return MSD_DATA_WRITE_ERROR;//写入错误
		}
		return 0;//写入成功
}
/*******************************************************************************
* 函数名称 : SD_SendCmd
* 功能描述 : 向sd卡写入一个数据包的内容 512字节
* 进入参数 : cmd：命令 arg：命令参数crc：