#pragma  once 
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


class Point
{
public:
	//����X
	void setX(int x);

	//����Y
	void setY(int y);
	
	//��ȡX
	int getX();
	
	//��ȡY
	int getY();
	

private:
	int m_X;
	int m_Y;
};