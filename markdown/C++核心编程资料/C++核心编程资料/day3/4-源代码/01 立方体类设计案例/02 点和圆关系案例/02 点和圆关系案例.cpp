#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "Point.h"
#include "Circle.h"
/*
设计一个圆形类（AdvCircle），和一个点类（Point），计算点和圆的关系
*/

//class Point
//{
//public:
//	//设置X
//	void setX(int x)
//	{
//		m_X = x;
//	}
//	//设置Y
//	void setY(int y)
//	{
//		m_Y = y;
//	}
//	//获取X
//	int getX()
//	{
//		return m_X;
//	}
//	//获取Y
//	int getY()
//	{
//		return m_Y;
//	}
//
//private:
//	int m_X;
//	int m_Y;
//};


//class Circle
//{
//public:
//	//设置半径
//	void setR(int r)
//	{
//		m_R = r;
//	}
//	//设置圆心 
//	void setCenter(Point center)
//	{
//		m_Center = center;
//	}
//	//获取半径 
//	int getR()
//	{
//		return m_R;
//	}
//
//	//获取圆心
//	Point getCenter()
//	{
//		return m_Center;
//	}
//
//	//利用成员函数 判断点和圆关系
//	void isInCircleByClass(Point p)
//	{
//		//获取 两点之间距离 的平方
//		int distance = (m_Center.getX() - p.getX()) * (m_Center.getX() - p.getX()) + (m_Center.getY() - p.getY()) *(m_Center.getY() - p.getY());
//
//		//半径的平方
//		int rDistance =  m_R * m_R;
//
//		if (distance == rDistance)
//		{
//			cout << "成员函数： 点在圆上" << endl;
//		}
//		else if (distance > rDistance)
//		{
//			cout << "成员函数：点在圆外" << endl;
//		}
//		else
//		{
//			cout << "成员函数：点在圆内" << endl;
//		}
//	}
//
//private:
//
//	//半径
//	int m_R;
//
//	//圆心 
//	Point m_Center;
//
//};




//利用全局函数 判断点和圆的关系
void isInCircle(Circle &c , Point &p)
{
	//获取 两点之间距离 的平方
	int distance = (c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) + (c.getCenter().getY() - p.getY()) *(c.getCenter().getY() - p.getY());

	//半径的平方
	int rDistance = c.getR() * c.getR();

	if ( distance == rDistance)
	{
		cout << "点在圆上" << endl;
	}
	else if ( distance > rDistance)
	{
		cout << "点在圆外" << endl;
	}
	else
	{
		cout << "点在圆内" << endl;
	}

}

void test01()
{
	//利用全局函数判断点和圆关系
	Point p;
	p.setX(10);
	p.setY(10);

	Circle c;
	Point pCenter;
	pCenter.setX(10);
	pCenter.setY(0);
	//设置圆心
	c.setCenter(pCenter);
	//设置半径
	c.setR(10);

	isInCircle(c, p);

	//利用成员函数判断
	c.isInCircleByClass(p);

}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}