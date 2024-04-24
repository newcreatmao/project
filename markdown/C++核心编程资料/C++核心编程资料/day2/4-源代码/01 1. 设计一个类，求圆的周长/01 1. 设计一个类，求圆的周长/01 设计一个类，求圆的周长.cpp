#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

const double PI = 3.14;

//创建一个类  关键字 class + 类名
class Circle
{
public: //公共作用域

	//类中的函数  称为成员函数 成员方法
	double calculateZC()
	{
		return 2 * PI * m_R;
	}

	//设置半径 
	void setR(int r)
	{
		m_R = r;
	}

	//获取圆当前半径
	int getR()
	{
		return m_R;
	}

	//类中的变量 我们称为 成员变量、成员属性
	int m_R; //半径  属性
};

void test01()
{
	Circle c1; //通过类 创建对象      实例化对象

	//c1.m_R = 10;
	c1.setR(10);
	//cout << "圆的半径为：" << c1.m_R << endl;
	cout << "圆的半径为：" << c1.getR() << endl;
	cout << "圆的周长为：" << c1.calculateZC() << endl;

}


/*
2.	设计一个学生类，属性有姓名和学号，可以给姓名和学号赋值，可以显示学生的姓   名和学号
*/
class Student
{
public:

	//设置姓名
	void setName(string name)
	{
		m_Name = name;
	}

	//设置学号
	void setId(int id)
	{
		m_Id = id;
	}

	//显示姓名和学号
	void showInfo()
	{
		cout << "成员函数--- 姓名： " << m_Name << " 学号： " << m_Id << endl;
	}


	string m_Name; //姓名
	int m_Id; //学号

};

void test02()
{
	Student s1; //实例化学生对象
	s1.setName("张三");
	s1.setId(1);
	//cout << "姓名：" << s1.m_Name << " 学号： " << s1.m_Id << endl;
	s1.showInfo();


	Student s2;
	s2.setName("李四");
	s2.setId(2);
	s2.showInfo();

}



int main(){

	//test01();

	test02();

	system("pause");
	return EXIT_SUCCESS;
}