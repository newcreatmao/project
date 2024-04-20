#include"CLabel.h"
#include<iostream>
using namespace std;
#include"CTools.h"
#include<string.h>
CLabel::CLabel()
{
//	cout<<"默认构造函数"<<endl;
}
 
CLabel::CLabel(int x,int y,int w,int h,char pcontent[20])
{
//	cout<<"带参数的构造函数"<<endl;
	startX = x;
	startY = y;
	width = w;
	height = h;
	strcpy(content,pcontent);
}
 
/*
//自己写拷贝构造函数	
CLabel::CLabel(CLabel &lab)
{
	cout<<"拷贝构造函数"<<endl;
	startX = lab.startX;
	startY = lab.startY;
	width = lab.width;
	height = lab.height;
	strcpy(content,lab.content);	
}
*/
 
//类成员函数的实现格式：返回值类型 类名::成员函数名(参数列表){函数体}
void CLabel::show()
{
	gotoxy(startX,startY);
	cout<<content<<endl;
}
 
CLabel::~CLabel()
{
}