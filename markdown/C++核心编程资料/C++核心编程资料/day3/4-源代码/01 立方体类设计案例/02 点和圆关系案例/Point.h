#pragma  once 
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


class Point
{
public:
	//设置X
	void setX(int x);

	//设置Y
	void setY(int y);
	
	//获取X
	int getX();
	
	//获取Y
	int getY();
	

private:
	int m_X;
	int m_Y;
};