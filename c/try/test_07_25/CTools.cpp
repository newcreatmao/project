#include "CTools.h"
#include <windows.h>   //引用库头文件
#include<stdio.h>
#include<conio.h>
 
void gotoxy(int x,int y)//形参
{
	HANDLE hOut;
	COORD pos= {x,y};
	// 光标的起始位（第1列，第3行） 0是第1列 2是第3行
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
	//printf("定位光标位置搜索(%d,%d)\n",pos.X,pos.Y);
}
 
void paintWindow(int startX,int startY,int width,int height)  
{
	int i=0;
	//打印顶部   
	//光标定位 找规律 ┗  ┛ ┏ ┓ ┃ ━
	//顶部 y不变 x 在变 (x-x+w)
	gotoxy(startX,startY);
	printf("┏");
	for(i=0;i<width-2;i++)  //控制循环次数width-2次
	{
		printf("━ ");
	}
	printf("┓");
 
	//左边 x不变 y在变 (y到y+height)
	for(i=1;i<=height-1;i++)
	{
		gotoxy(startX,startY+i);
		printf("┃");
	}
	
	//右边 x不变 =startx+width-1  y在变 y 到 y+height
	for(i=1;i<=height-1;i++)
	{
		gotoxy(startX+width*2-3,startY+i);
		printf("┃");
	}
 
	//底部 x在变化    y不变 （x到x+width） ━ 
	gotoxy(startX,startY+height-1);
	printf("┗");
	for(i=0;i<width-2;i++)
	{
		printf("━ ");
	}
	printf("┛");
 
	gotoxy(startX,startX+height);
}
 
void glb_string(int maxLen,int inputType,int ips,char str[])
{ 
	   char ch=0;
	   int i=0;
	   while(1)
	   {
		   ch=getch();
		   if(ch=='\r'&&i>0)//换行结束输入
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
函数名：int getkey()
函数功能：获取用户输入的任意键盘值
函数参数：无
函数返回：ascii  
*/
int getkey()
{
	char key=0;
	key=getch();
	if(key==-32)//方向按键 第一个值都是32
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