#include"CButton.h"
#include<iostream>
using namespace std;
#include"CTools.h"
#include<string.h>
CButton::CButton()
{
//	cout<<"Ĭ�Ϲ��캯��"<<endl;
}
 
CButton::CButton(int x,int y,int w,int h,char pcontent[])
{
//	cout<<"�������Ĺ��캯��"<<endl;
	this->startX = x;
	this->startY = y;
	this->width = w;
	this->height = h;
	strcpy(this->content,pcontent);
}
 
CButton::~CButton()
{
//	cout<<"��������"<<endl;
}
 
void CButton::show()
{
	paintWindow(startX,startY,width,height);
	gotoxy(startX+(width*2-strlen(content))/2-1,startY+1);
	cout<<content<<endl;
}