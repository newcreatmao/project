#include "CTools.h"
#include <windows.h>   //���ÿ�ͷ�ļ�
#include<stdio.h>
#include<conio.h>
 
void gotoxy(int x,int y)//�β�
{
	HANDLE hOut;
	COORD pos= {x,y};
	// ������ʼλ����1�У���3�У� 0�ǵ�1�� 2�ǵ�3��
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
	//printf("��λ���λ������(%d,%d)\n",pos.X,pos.Y);
}
 
void paintWindow(int startX,int startY,int width,int height)  
{
	int i=0;
	//��ӡ����   
	//��궨λ �ҹ��� ��  �� �� �� �� ��
	//���� y���� x �ڱ� (x-x+w)
	gotoxy(startX,startY);
	printf("��");
	for(i=0;i<width-2;i++)  //����ѭ������width-2��
	{
		printf("�� ");
	}
	printf("��");
 
	//��� x���� y�ڱ� (y��y+height)
	for(i=1;i<=height-1;i++)
	{
		gotoxy(startX,startY+i);
		printf("��");
	}
	
	//�ұ� x���� =startx+width-1  y�ڱ� y �� y+height
	for(i=1;i<=height-1;i++)
	{
		gotoxy(startX+width*2-3,startY+i);
		printf("��");
	}
 
	//�ײ� x�ڱ仯    y���� ��x��x+width�� �� 
	gotoxy(startX,startY+height-1);
	printf("��");
	for(i=0;i<width-2;i++)
	{
		printf("�� ");
	}
	printf("��");
 
	gotoxy(startX,startX+height);
}
 
void glb_string(int maxLen,int inputType,int ips,char str[])
{ 
	   char ch=0;
	   int i=0;
	   while(1)
	   {
		   ch=getch();
		   if(ch=='\r'&&i>0)//���н�������
		   {	   
			   break;	   
		   }
		   switch(inputType)
		   {
		   case 0:
			   if(ch>='0'&&ch<='9'&&i<maxLen)
			   {
				   if(ips==0)
				   {
					   putch('*');	   
				   }
				   else{			   
					   putch(ch);
				   }
				   str[i++]=ch;		   
			   }
			   break;
		   case 1:
			   if(i<maxLen&&(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
			   {
				   if(ips==0)
				   {
					   putch('*');   
				   }
				   else{   
					   putch(ch);
				   }
				   str[i++]=ch;   
			   }
			   break;
		   case 2:
			   if(i<maxLen&&(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9'))
			   {
				   if(ips==0)
				   {
					   putch('*');
				   }
				   else{  
					   putch(ch);
				   }
				   str[i++]=ch;   
			   }
			   break;
		   default:
			   break; 
		   }
	   }	    
}
 
/*
��������int getkey()
�������ܣ���ȡ�û�������������ֵ
������������
�������أ�ascii  
*/
int getkey()
{
	char key=0;
	key=getch();
	if(key==-32)//���򰴼� ��һ��ֵ����32
	{
		key=getch();
		switch(key){
		case 72:
			return KEY_UP;
		case 80:
			return KEY_DOWN;
		case 75:
			return KEY_LEFT;
		case 77:
			return KEY_RIGHT;
		}	
	}
	else if(key==13)
	{
		return KEY_ENTER;
	}
	else if(key==27)
	{
		return KEY_ESC;
	}
	return key;
}