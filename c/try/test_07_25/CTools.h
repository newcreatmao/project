#ifndef CTOOLS_H
#define CTOOLS_H
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define KEY_ENTER 13
 
void paintWindow(int startX,int startY,int width,int height);//��ӡ����
 
void gotoxy(int x,int y);//�β�  ��궨λ
 
/*
�������ܣ��ַ����������
����������
int maxLen ����������󳤶�
int inputType ����������ַ�����  0������ 1����ĸ 2����ĸ+����
int ips       ������ʾ��ʽ        0������  1������
char str[] �洢�����ַ�
��������ֵ����
char str[]    char str[20]    char*str
*/
void glb_string(int maxLen,int inputType,int ips,char str[]); 
 
/*
��������int getkey()
�������ܣ���ȡ�û�������������ֵ
������������
�������أ�ascii  
*/
int getkey();
 
#endif