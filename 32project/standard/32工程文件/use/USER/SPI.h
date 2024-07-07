#ifndef __MYI2C_H
#define __MYI2C_H

#include "stm32f10x.h"                  // Device header

void SPI_SD_Init(void);
u8 SPIx_ReadWriteByte(u8 byte);
u16 SPIx_ReadWriteHalfWord(u16 HalfWord);
void SPIx_SetSpeed(u8 SpeedSet);
#endif
