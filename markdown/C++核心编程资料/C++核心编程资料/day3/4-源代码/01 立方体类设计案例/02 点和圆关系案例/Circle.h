#pragma  once 
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "Point.h"

class Circle
{
public:

	//���ð뾶
	void setR(int r);
	
	//����Բ�� 
	void setCenter(Point center);
	
	//��ȡ�뾶 
	int getR();
	

	//��ȡԲ��
	Point getCenter();
	

	//���ó�Ա���� �жϵ��Բ��ϵ
	void isInCircleByClass(Point p);
	

private:

	//�뾶
	int m_R;

	//Բ�� 
	Point m_Center;

};