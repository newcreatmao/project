#ifndef _APP_H
#define _APP_H

extern bit Timer1Overflow;	//������1�����־λ
void DispDistance(unsigned int Val);//LCD1602��ʾ������������
void bubble(unsigned int *a, unsigned char n);
unsigned int RefreshDistance();
void PTZ_Avoid();
void IR_Avoid();
#endif