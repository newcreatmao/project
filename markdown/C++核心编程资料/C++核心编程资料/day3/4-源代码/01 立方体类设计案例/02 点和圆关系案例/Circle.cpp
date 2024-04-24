#include "Circle.h"



//设置半径
void Circle::setR(int r)
{
	m_R = r;
}
//设置圆心 
void Circle::setCenter(Point center)
{
	m_Center = center;
}
//获取半径 
int Circle::getR()
{
	return m_R;
}

//获取圆心
Point Circle::getCenter()
{
	return m_Center;
}

//利用成员函数 判断点和圆关系
void Circle::isInCircleByClass(Point p)
{
	//获取 两点之间距离 的平方
	int distance = (m_Center.getX() - p.getX()) * (m_Center.getX() - p.getX()) + (m_Center.getY() - p.getY()) *(m_Center.getY() - p.getY());

	//半径的平方
	int rDistance = m_R * m_R;

	if (distance == rDistance)
	{
		cout << "成员函数： 点在圆上" << endl;
	}
	else if (distance > rDistance)
	{
		cout << "成员函数：点在圆外" << endl;
	}
	else
	{
		cout << "成员函数：点在圆内" << endl;
	}
}

