#ifndef __LCD1602_H__
#define __LCD1602_H__

//command
#define XP 0x9C;//xp通道对应的命令
#define YP 0xDC;//yp通道对应的命令


unsigned int READ(unsigned char command);

#endif
