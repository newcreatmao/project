#ifndef _LCD1602_H
#define _LCD1602_H

void Init_LCD1602();//LCD1602��ʼ��
void LCD1602_Dis_Str(uint8 x, uint8 y, uint8 *str); //LCD1602д�ַ���
void LCD1602_Dis_OneChar(uint8 x, uint8 y, uint8 dat);	//LCD1602дһ���ֽڵ�����
void LCD1602_Set_Cursor(uint8 x, uint8 y);//LCD1602���ù����ʾλ��
void LCD1602_Close_Cursor();//LCD1602�رչ����ʾ
void LCD1602_Open_Cursor();	//LCD1602�򿪹����ʾ
void LCD1602_Clear_Screen();//LCD1602����

#endif
