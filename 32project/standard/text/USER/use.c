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

//读取SD卡的指定扇区的内容，并通过串口1输出
//sec：扇区物理地址编号
void SD_Read_Sectorx(u32 sec)
{
	u8 *buf;
	u16 i;
	buf=mymalloc(512);				//申请内存
	if(SD_ReadDisk(buf,sec,1)==0)	//读取0扇区的内容
	{	
		LCD_ShowString(60,190,200,16,16,"USART1 Sending Data...");
		printf("SECTOR 0 DATA:\r\n");
		for(i=0;i<512;i++)printf("%x ",buf[i]);//打印sec扇区数据    	   
		printf("\r\nDATA ENDED\r\n");
		LCD_ShowString(60,190,200,16,16,"USART1 Send Data Over!");
	}
	myfree(buf);//释放内存	
}

void ReadSD(){
	FATFS fs;
	FIL File;
	UINT br;
	int ret=1,res=1;
	res=f_mount(&fs,"0:",1);		//挂载
	if(res == FR_OK)
	{
		printf("挂载成功! \r\n");		
	}
		else
	{
		printf("挂载失败! \r\n");
	}	
	ret = f_open(&File,SD_FileName,FA_OPEN_ALWAYS|FA_READ);
	if(res == FR_OK){
		printf("打开文件成功！\r\n");
		ret=f_read(&File,Read_data,f_size(&File),&br);
		if(ret == FR_OK)
			{
				printf("文件读出成功！ \r\n");			
			}
		else
			{
				printf("文件读出失败 \r\n");
			}
	}	
	else
	{
		printf("打开文件失败!\r\n");
	}		
	ret = f_close(&File); 
	f_mount(NULL,"0:",1);		 //取消挂载
}

void WritetoSD(char write_buff[],uint8_t bufSize)
{
	FATFS fs;
	FIL file;
	uint8_t res=0;
	UINT Bw;
	res=f_mount(&fs,"0:",1);		//挂载
	if(res == FR_NO_FILESYSTEM)		//没有文件系统，格式化
	{
		printf("没有文件系统! \r\n");		
		res = f_mkfs("", 0, 0);		//格式化sd卡
		if(res == FR_OK)
		{
			printf("格式化成功! \r\n");		
			res = f_mount(NULL,"0:",1); 		//格式化后先取消挂载
			res = f_mount(&fs,"0:",1);			//重新挂载	
			if(res == FR_OK)
			{
				printf("SD卡已经成功挂载，可以进进行文件写入测试!\r\n");
			}	
		}
		else
		{
			printf("格式化失败! \r\n");		
		}
	}
		else if(res == FR_OK)
	{
		printf("挂载成功! \r\n");		
	}
		else
	{
		printf("挂载失败! \r\n");
	}	
	res = f_open(&file,SD_FileName,FA_OPEN_ALWAYS |FA_WRITE);
	if((res & FR_DENIED) == FR_DENIED)
	{
		printf("卡存储已满，写入失败!\r\n");		
	}
	
	f_lseek(&file, f_size(&file));//确保写词写入不会覆盖之前的数据
	if(res == FR_OK)
	{
		printf("打开成功/创建文件成功！ \r\n");		
		res = f_write(&file,write_buff,bufSize,&Bw);		//写数据到SD卡
		if(res == FR_OK)
		{
			printf("文件写入成功！ \r\n");			
		}
		else
		{
			printf("文件写入失败！ \r\n");
		}		
	}
	else
	{
		printf("打开文件失败!\r\n");
	}	
	
	f_close(&file);						//关闭文件		
	f_mount(NULL,"0:",1);		 //取消挂载
	
}

void SD_Init(){
		FATFS fs;
		FIL file;
		uint8_t res=0;
		UINT Bw;
		res=f_mount(&fs,"0:",1);		//挂载
		res = f_mkfs("", 0, 0);		//格式化sd卡
		if(res == FR_OK)
		{
			printf("格式化成功! \r\n");		
			res = f_mount(NULL,"0:",1); 		//格式化后先取消挂载
			res = f_mount(&fs,"0:",1);			//重新挂载	
			if(res == FR_OK)
			{
				printf("SD卡已经成功挂载，可以进行文件写入测试!\r\n");
			}	
		}
		else
		{
			printf("格式化失败! \r\n");		
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