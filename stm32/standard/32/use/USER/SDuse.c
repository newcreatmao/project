#include"SDuse.h"

/******************************START OF SD_OPERATION***********************/
/*******************************************************************************
* �������� : SD_Select
* �������� : ѡ��SD�������ȴ�SD��׼����
* ������� : ��.
* ���ز��� : 0���ɹ� 1��ʧ��
* ��ע˵�� : SD��׼���û᷵��0XFF
*******************************************************************************/
u8 SD_Select(void)
{
		uint32_t t=0;
		SD_CS(OFF);//ƬѡSD���͵�ƽʹ��
		do
		{
		if(SD_SPI_ReadWriteByte(0XFF)==0XFF)return 0;//OK
		t++;
		}while(t<0XFFFFFF);//�ȴ�
		SD_DisSelect(); //�ͷ�����
		return 1;//�ȴ�ʧ��
}
/*******************************************************************************
* �������� : SD_RecvData
* �������� : ��sd����ȡһ�����ݰ�������
* ������� : buf�����ݻ������� lenҪ��ȡ�����ݵĳ���
* ���ز��� : 0���ɹ� ������ʧ��
* ��ע˵�� : ��ȡʱ��Ҫ�ȴ�SD������������ʼ����0XFE
*******************************************************************************/
u8 SD_RecvData(u8*buf,u16 len)
{
		u16 Count=0xF000;//�ȴ�����
		while ((SD_SPI_ReadWriteByte(0XFF)!=0xFE)&&Count)Count--;//�ȴ��õ���ȡ��������0xfe
		if (Count==0) return MSD_RESPONSE_FAILURE;//��ȡ����ʧ��,����0XFF
		while(len--)//��ʼ��������
		{
		*buf=SPIx_ReadWriteByte(0xFF);
		buf++;
}
//������2��αCRC��dummy CRC������װ������2��CRC
SD_SPI_ReadWriteByte(0xFF);
SD_SPI_ReadWriteByte(0xFF);
return 0;//��ȡ�ɹ�
}
/*******************************************************************************
* �������� : SD_SendBlock
* �������� : ��sd��д��һ�����ݰ������� 512�ֽ�
* ������� : buf:���ݻ����� cmd:���ݷ��͵�����
* ���ز��� : 0���ɹ� ������ʧ��
* ��ע˵�� : д����ʱ��Ҫ�ȷ���������ʼ����0XFE/0XFC/0XFD
*******************************************************************************/
u8 SD_SendBlock(u8*buf,u8 cmd)
{
		u32 t,Count=0XFFFFFF;
		while ((SD_SPI_ReadWriteByte(0XFF)!=0xFF)&&Count)Count--;//�ȴ�SD��׼����
		if (Count==0) return MSD_RESPONSE_FAILURE;//SD��δ׼���ã�ʧ�ܣ�����
		SD_SPI_ReadWriteByte(cmd);//����������ʼ��ֹͣ����
		if(cmd!=0XFD)//�ڲ��ǽ������Ƶ�����£���ʼ��������
		{
		for(t=0;t<512;t++)SPIx_ReadWriteByte(buf[t]);//����ٶ�,���ٺ�������ʱ��
		SD_SPI_ReadWriteByte(0xFF);//����2�ֽڵ�CRC
		SD_SPI_ReadWriteByte(0xFF);
		t=SD_SPI_ReadWriteByte(0xFF);//������CRC֮���������д��״̬
		if((t&0x1F)!=0x05)return MSD_DATA_WRITE_ERROR;//д�����
		}
		return 0;//д��ɹ�
}
/*******************************************************************************
* �������� : SD_SendCmd
* �������� : ��sd��д��һ�����ݰ������� 512�ֽ�
* ������� : cmd������ arg���������crc��