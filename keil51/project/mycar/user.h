#ifndef __USER_H__
#define __USER_H__

void timer();		//100Œ¢√Î@11.0592MHz

void uart();

void sendbyte(unsigned char byte);

unsigned char Keyreturn(void);

unsigned char Key_GetState();

void forward();

void stop();

void backward();

unsigned char red();

void tlf();

void tgb();

void tlb();

void tgf();

void reward();

void Key_Loop(void);

void look_road();
#endif