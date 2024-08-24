#ifndef __OLED_H
#define __OLED_H

#include "sys.h"

void OLED_Init(void);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N);
void OLED_ShowCN_STR(u8 x , u8 y , u8 begin , u8 num);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,const unsigned char BMP[]);
void OLED_DrawGIF(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1, unsigned char k, int m, unsigned char GIF[][m]);
#endif
