#include "Circle.h"



//���ð뾶
void Circle::setR(int r)
{
	m_R = r;
}
//����Բ�� 
void Circle::setCenter(Point center)
{
	m_Center = center;
}
//��ȡ�뾶 
int Circle::getR()
{
	return m_R;
}

//��ȡԲ��
Point Circle::getCenter()
{
	return m_Center;
}

//���ó�Ա���� �жϵ��Բ��ϵ
void Circle::isInCircleByClass(Point p)
{
	//��ȡ ����֮����� ��ƽ��
	int distance = (m_Center.getX() - p.getX()) * (m_Center.getX() - p.getX()) + (m_Center.getY() - p.getY()) *(m_Center.getY() - p.getY());

	//�뾶��ƽ��
	int rDistance = m_R * m_R;

	if (distance == rDistance)
	{
		cout << "��Ա������ ����Բ��" << endl;
	}
	else if (distance > rDistance)
	{
		cout << "��Ա����������Բ��" << endl;
	}
	else
	{
		cout << "��Ա����������Բ��" << endl;
	}
}

