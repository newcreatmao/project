#pragma  once 
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "Point.h"

class Circle
{
public:

	//设置半径
	void setR(int r);
	
	//设置圆心 
	void setCenter(Point center);
	
	//获取半径 
	int getR();
	

	//获取圆心
	Point getCenter();
	

	//利用成员函数 判断点和圆关系
	void isInCircleByClass(Point p);
	

private:

	//半径
	int m_R;

	//圆心 
	Point m_Center;

};