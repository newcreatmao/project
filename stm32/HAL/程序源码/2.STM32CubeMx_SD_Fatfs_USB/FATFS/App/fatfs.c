/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

#include "fatfs.h"

uint8_t retSD;    /* Return value for SD */
char SDPath[4];   /* SD logical drive path */
FATFS SDFatFS;    /* File system object for SD logical drive */
FIL SDFile;       /* File object for SD */
uint8_t retUSBH;    /* Return value for USBH */
char USBHPath[4];   /* USBH logical drive path */
FATFS USBHFatFS;    /* File system object for USBH logical drive */
FIL USBHFile;       /* File object for USBH */

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

void MX_FATFS_Init(void)
{
  /*## FatFS: Link the SD driver ###########################*/
  retSD = FATFS_LinkDriver(&SD_Driver, SDPath);
  /*## FatFS: Link the USBH driver ###########################*/
  retUSBH = FATFS_LinkDriver(&USBH_Driver, USBHPath);

  /* USER CODE BEGIN Init */
  /* additional user code for init */
  /* USER CODE END Init */
}

/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  return 0;
  /* USER CODE END get_fattime */
}

/* USER CODE BEGIN Application */
static void MSC_Application(void) //USB大容量存储区测试代码
{
	FRESULT res;
	uint32_t byteswritten;  //file write/read counts
	uint8_t wtext[] = "This is USB Mass Storage Application Example!\r\n";
	
	FATFS fs;                 //工作空间
	FIL fil;                  // 文件项目
	const TCHAR usbpath[] = "1:";
	char filename[] = "1:UsbFatfs_test.txt"; // 文件名
	
	uint32_t bytesread;       // 读文件计数
	uint8_t rtext[1024];             // 读取的buff
	
	printf("\r\n \r\n MSC_Application USB \r\n");
	
	//1.挂载USB
	res = f_mount(&fs,usbpath,1);
	if(res != FR_OK){
		printf(" mount USB fail: %d \r\n",res);
		return;
	}
	printf(" mount USB sucess!!! \r\n");

	//2.打开
	res = f_open(&fil, filename, FA_CREATE_ALWAYS | FA_WRITE);
	if(res != FR_OK){
		printf(" open file error : %d\r\n",res);
		return;
	}
	printf(" open file sucess!!! \r\n");
	
	//3.写数据
	res = f_write(&fil, wtext, sizeof(wtext), (void *)&byteswritten);	//在文件内写入wtext内的内容
	if(res != FR_OK){
		printf(" write file error : %d\r\n",res);	
		//return;
		goto ERROR_CONTROL;
	}
	printf(" write file sucess!!! writen count: %d \r\n",byteswritten);
    printf(" write Data : %s\r\n",wtext);
	
	//4.关闭文件
    res = f_close(&fil);
	
	printf("\r\n read USB mass storage data.\r\n");
	//5.打开文件
	res = f_open(&fil, filename, FA_READ);				//打开文件，权限为只读
    if(res != FR_OK){									//返回值不为0（出现问题）
        printf(" open file error : %d\r\n",res);		//打印问题代码
		//return;
		goto ERROR_CONTROL;
	}
    printf(" open file sucess!!! \r\n");
	
	//6.读取txt文件数据
    res = f_read(&fil, rtext, sizeof(rtext), (UINT*)&bytesread);//读取文件内容放到rtext中
    if(res){													//返回值不为0（出现问题）
        printf(" read error!!! %d\r\n",res);					//打印问题代码
		//return;
		goto ERROR_CONTROL;
    }else{
        printf(" read sucess!!! \r\n");
        printf(" read Data : %s\r\n",rtext);				   //打印读取到的数据
    }
	
	//7.读写一致性检测
    if(bytesread == byteswritten)										//如果读写位数一致
    { 
        printf(" bytesread == byteswritten，写入与读出数据一致。\r\n");						//打印文件系统工作正常
    }

ERROR_CONTROL:	
	//8.关闭文件
    res = f_close(&fil);												//关闭该文件
    if(res)  															//返回值不为0（出现问题）
        printf(" close error!!! %d\r\n",res);							//打印问题代码
    else
        printf(" close sucess!!! \r\n");
     
    
	
//	if(f_mount(&USBHFatFS,(const TCHAR*)USBHPath,1) !=FR_OK)
//	{
//		//Fatfs Initialization Error
//		Error_Handler();
//		printf(" mount USB fail!!! \r\n");
//	}
//	else
//	{
//		printf(" mount USB sucess!!! \r\n");
//		if(f_open(&USBHFile, "STM32_USB.TXT", FA_CREATE_ALWAYS | FA_WRITE) !=FR_OK){
//			// "STM32_USB.TXT" file open for write error
//			Error_Handler();
//			printf(" open usb file fail!!! \r\n");
//		}else{
//			printf(" open usb file sucess!!! \r\n");
//			//write data to the text file
//			res = f_write(&USBHFile, wtext, sizeof(wtext), (void *)&byteswritten);
//			if((byteswritten==0) || (res != FR_OK)){
//				Error_Handler();
//				printf(" write usb file fail!!! \r\n");
//			}else{
//				printf(" write usb file sucess!!! \r\n");
//				//close the open text file
//				f_close(&USBHFile);
//			}
//		printf(" operate USB file end \r\n");	
//		}
//	}
}
void UsbTest(void)
{
	#include "usb_host.h"
	extern ApplicationTypeDef Appli_state;
	
	switch(Appli_state)
	{
		case APPLICATION_READY:
			MSC_Application();
			Appli_state = APPLICATION_DISCONNECT;
			break;
		
		case APPLICATION_DISCONNECT:
			f_mount(NULL, (const TCHAR*)"",0);
			break;
		
		default:
			break;
	}
}	
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
