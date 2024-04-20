#include"CButton.h"
#include<iostream>
using namespace std;
#include"CTools.h"
#include<string.h>
CButton::CButton()
{
//	cout<<"默认构造函数"<<endl;
}
 
CButton::CButton(int x,int y,int w,int h,char pcontent[])
{
//	cout<<"带参数的构造函数"<<endl;
	this->startX = x;
	this->startY = y;
	this->width = w;
	this->height = h;
	strcpy(this->content,pcontent);
}
 
CButton::~CButton()
{
//	cout<<"析构函数"<<endl;
}
 
void CButton::show()
{
	paintWindow(startX,startY,width,height);
	gotoxy(startX+(width*2-strlen(content))/2-1,startY+1);
	cout<<content<<endl;
}