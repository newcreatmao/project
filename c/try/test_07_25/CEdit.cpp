#include"CEdit.h"
#include"CTools.h"
#include<iostream>
#include<string.h>
using namespace std;
 
CEdit::CEdit()
{
	this->startX = 0;
	this->startY = 0;
	this->width = 0;
	this->height = 0;
	memset(this->content,'\0',sizeof(this->content));
}
 
CEdit::CEdit(int x,int y,int w,int h,char *pcontent,
			int maxLen,int inputType,int ips )
{
	this->startX = x;
	this->startY = y;
	this->width = w;
	this->height = h;
	this->maxLen = maxLen;
	this->inputType = inputType;
	this->ips = ips;
	memset(this->content,0,sizeof(this->content));
	if(pcontent!=NULL)
	{
		strcpy(this->content,pcontent);
	}
}
 
void CEdit::show()
{
	paintWindow(startX-1,startY-1,width,height);
	gotoxy(startX,startY);
	cout<<content<<endl;
}