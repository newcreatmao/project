#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "Point.h"
#include "Circle.h"
/*
���һ��Բ���ࣨAdvCircle������һ�����ࣨPoint����������Բ�Ĺ�ϵ
*/

//class Point
//{
//public:
//	//����X
//	void setX(int x)
//	{
//		m_X = x;
//	}
//	//����Y
//	void setY(int y)
//	{
//		m_Y = y;
//	}
//	//��ȡX
//	int getX()
//	{
//		return m_X;
//	}
//	//��ȡY
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
//	//���ð뾶
//	void setR(int r)
//	{
//		m_R = r;
//	}
//	//����Բ�� 
//	void setCenter(Point center)
//	{
//		m_Center = center;
//	}
//	//��ȡ�뾶 
//	int getR()
//	{
//		return m_R;
//	}
//
//	//��ȡԲ��
//	Point getCenter()
//	{
//		return m_Center;
//	}
//
//	//���ó�Ա���� �жϵ��Բ��ϵ
//	void isInCircleByClass(Point p)
//	{
//		//��ȡ ����֮����� ��ƽ��
//		int distance = (m_Center.getX() - p.getX()) * (m_Center.getX() - p.getX()) + (m_Center.getY() - p.getY()) *(m_Center.getY() - p.getY());
//
//		//�뾶��ƽ��
//		int rDistance =  m_R * m_R;
//
//		if (distance == rDistance)
//		{
//			cout << "��Ա������ ����Բ��" << endl;
//		}
//		else if (distance > rDistance)
//		{
//			cout << "��Ա����������Բ��" << endl;
//		}
//		else
//		{
//			cout << "��Ա����������Բ��" << endl;
//		}
//	}
//
//private:
//
//	//�뾶
//	int m_R;
//
//	//Բ�� 
//	Point m_Center;
//
//};




//����ȫ�ֺ��� �жϵ��Բ�Ĺ�ϵ
void isInCircle(Circle &c , Point &p)
{
	//��ȡ ����֮����� ��ƽ��
	int distance = (c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) + (c.getCenter().getY() - p.getY()) *(c.getCenter().getY() - p.getY());

	//�뾶��ƽ��
	int rDistance = c.getR() * c.getR();

	if ( distance == rDistance)
	{
		cout << "����Բ��" << endl;
	}
	else if ( distance > rDistance)
	{
		cout << "����Բ��" << endl;
	}
	else
	{
		cout << "����Բ��" << endl;
	}

}

void test01()
{
	//����ȫ�ֺ����жϵ��Բ��ϵ
	Point p;
	p.setX(10);
	p.setY(10);

	Circle c;
	Point pCenter;
	pCenter.setX(10);
	pCenter.setY(0);
	//����Բ��
	c.setCenter(pCenter);
	//���ð뾶
	c.setR(10);

	isInCircle(c, p);

	//���ó�Ա�����ж�
	c.isInCircleByClass(p);

}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}