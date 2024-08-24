#ifndef __USE_H
#define __USE_H	 

#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "malloc.h"  
#include "MMC_SD.h"  
#include "string.h"
#include "ff.h"
#include "flash.h"
#include "diskio.h"

void Lock_show();
void SD_Read_Sectorx(u32 sec);
void SD_rw();
void ReadSD();
void WritetoSD(char write_buff[],uint8_t bufSize);
void SD_Init();

#endif
