#include"CLabel.h"
#include<iostream>
using namespace std;
#include"CTools.h"
#include<string.h>
CLabel::CLabel()
{
//	cout<<"Ĭ�Ϲ��캯��"<<endl;
}
 
CLabel::CLabel(int x,int y,int w,int h,char pcontent[20])
{
//	cout<<"�������Ĺ��캯��"<<endl;
	startX = x;
	startY = y;
	width = w;
	height = h;
	strcpy(content,pcontent);
}
 
/*
//�Լ�д�������캯��	
CLabel::CLabel(CLabel &lab)
{
	cout<<"�������캯��"<<endl;
	startX = lab.startX;
	startY = lab.startY;
	width = lab.width;
	height = lab.height;
	strcpy(content,lab.content);	
}
*/
 
//���Ա������ʵ�ָ�ʽ������ֵ���� ����::��Ա������(�����б�){������}
void CLabel::show()
{
	gotoxy(startX,startY);
	cout<<content<<endl;
}
 
CLabel::~CLabel()
{
}