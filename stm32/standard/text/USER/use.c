#include "use.h"
char SD_FileName[] = "data.txt";
char Read_data[512];
void Lock_show(){
		if(Serial_RxFlag==1){
			LCD_ShowString(60,210,200,16,16,Serial_RxPacket);
			if(strcmp(Serial_RxPacket,"Lock_open1 ")==0){
				Open_lock(1);
			}
			else if(strcmp(Serial_RxPacket,"Lock_open2 ")==0){
				Open_lock(2);
			}
			else if(strcmp(Serial_RxPacket,"Lock_open3 ")==0){
				Open_lock(3);
			}
			else if(strcmp(Serial_RxPacket,"Lock_open4 ")==0){
				Open_lock(4);
			}
			else if(strcmp(Serial_RxPacket,"Lock_open5 ")==0){
				Open_lock(5);
			}
			else if(strcmp(Serial_RxPacket,"Lock_close1")==0){
				Lock(1);
			}
			else if(strcmp(Serial_RxPacket,"Lock_close2")==0){
				Lock(2);
			}
			else if(strcmp(Serial_RxPacket,"Lock_close3")==0){
				Lock(3);
			}
			else if(strcmp(Serial_RxPacket,"Lock_close4")==0){
				Lock(4);
			}
			else if(strcmp(Serial_RxPacket,"Lock_close5")==0){
				Lock(5);
			}
			Serial_RxFlag=0;
		}
}

//��ȡSD����ָ�����������ݣ���ͨ������1���
//sec�����������ַ���
void SD_Read_Sectorx(u32 sec)
{
	u8 *buf;
	u16 i;
	buf=mymalloc(512);				//�����ڴ�
	if(SD_ReadDisk(buf,sec,1)==0)	//��ȡ0����������
	{	
		LCD_ShowString(60,190,200,16,16,"USART1 Sending Data...");
		printf("SECTOR 0 DATA:\r\n");
		for(i=0;i<512;i++)printf("%x ",buf[i]);//��ӡsec��������    	   
		printf("\r\nDATA ENDED\r\n");
		LCD_ShowString(60,190,200,16,16,"USART1 Send Data Over!");
	}
	myfree(buf);//�ͷ��ڴ�	
}

void ReadSD(){
	FATFS fs;
	FIL File;
	UINT br;
	int ret=1,res=1;
	res=f_mount(&fs,"0:",1);		//����
	if(res == FR_OK)
	{
		printf("���سɹ�! \r\n");		
	}
		else
	{
		printf("����ʧ��! \r\n");
	}	
	ret = f_open(&File,SD_FileName,FA_OPEN_ALWAYS|FA_READ);
	if(res == FR_OK){
		printf("���ļ��ɹ���\r\n");
		ret=f_read(&File,Read_data,f_size(&File),&br);
		if(ret == FR_OK)
			{
				printf("�ļ������ɹ��� \r\n");			
			}
		else
			{
				printf("�ļ�����ʧ�� \r\n");
			}
	}	
	else
	{
		printf("���ļ�ʧ��!\r\n");
	}		
	ret = f_close(&File); 
	f_mount(NULL,"0:",1);		 //ȡ������
}

void WritetoSD(char write_buff[],uint8_t bufSize)
{
	FATFS fs;
	FIL file;
	uint8_t res=0;
	UINT Bw;
	res=f_mount(&fs,"0:",1);		//����
	if(res == FR_NO_FILESYSTEM)		//û���ļ�ϵͳ����ʽ��
	{
		printf("û���ļ�ϵͳ! \r\n");		
		res = f_mkfs("", 0, 0);		//��ʽ��sd��
		if(res == FR_OK)
		{
			printf("��ʽ���ɹ�! \r\n");		
			res = f_mount(NULL,"0:",1); 		//��ʽ������ȡ������
			res = f_mount(&fs,"0:",1);			//���¹���	
			if(res == FR_OK)
			{
				printf("SD���Ѿ��ɹ����أ����Խ������ļ�д�����!\r\n");
			}	
		}
		else
		{
			printf("��ʽ��ʧ��! \r\n");		
		}
	}
		else if(res == FR_OK)
	{
		printf("���سɹ�! \r\n");		
	}
		else
	{
		printf("����ʧ��! \r\n");
	}	
	res = f_open(&file,SD_FileName,FA_OPEN_ALWAYS |FA_WRITE);
	if((res & FR_DENIED) == FR_DENIED)
	{
		printf("���洢������д��ʧ��!\r\n");		
	}
	
	f_lseek(&file, f_size(&file));//ȷ��д��д�벻�Ḳ��֮ǰ������
	if(res == FR_OK)
	{
		printf("�򿪳ɹ�/�����ļ��ɹ��� \r\n");		
		res = f_write(&file,write_buff,bufSize,&Bw);		//д���ݵ�SD��
		if(res == FR_OK)
		{
			printf("�ļ�д��ɹ��� \r\n");			
		}
		else
		{
			printf("�ļ�д��ʧ�ܣ� \r\n");
		}		
	}
	else
	{
		printf("���ļ�ʧ��!\r\n");
	}	
	
	f_close(&file);						//�ر��ļ�		
	f_mount(NULL,"0:",1);		 //ȡ������
	
}

void SD_Init(){
		FATFS fs;
		FIL file;
		uint8_t res=0;
		UINT Bw;
		res=f_mount(&fs,"0:",1);		//����
		res = f_mkfs("", 0, 0);		//��ʽ��sd��
		if(res == FR_OK)
		{
			printf("��ʽ���ɹ�! \r\n");		
			res = f_mount(NULL,"0:",1); 		//��ʽ������ȡ������
			res = f_mount(&fs,"0:",1);			//���¹���	
			if(res == FR_OK)
			{
				printf("SD���Ѿ��ɹ����أ����Խ����ļ�д�����!\r\n");
			}	
		}
		else
		{
			printf("��ʽ��ʧ��! \r\n");		
		}
}

void SD_rw(){
			if(Serial_RxFlag==1){
			LCD_ShowString(60,230,200,16,16,Serial_RxPacket);
			LCD_ShowString(60,90,200,16,strlen(Read_data),Read_data);
			if(strcmp(Serial_RxPacket,"Write_data")==0){
				Serial_RxFlag=0;
				while(Serial_RxFlag==0);
				WritetoSD(Serial_RxPacket,strlen(Serial_RxPacket));
				WritetoSD("\r\n",4);
			}
			else if(strcmp(Serial_RxPacket,"SD_init")==0){SD_Init();}
			else if(strcmp(Serial_RxPacket,"Read_data")==0){ReadSD();}
			Serial_RxFlag=0;
		}
}