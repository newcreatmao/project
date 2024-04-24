#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
	//将全局函数  左移运算符重载  变为Person的友元函数
	friend ostream & operator<<(ostream &cout, Person & p1);
public:
	Person(){};
	Person(int a, int b)
	{
		this->m_A = a;
		this->m_B = b;
	}

	//试图利用成员函数 实现 <<运算符重载
	//void operator<< (ostream & cout)
	//{
	//
	//}

private:
	int m_A;
	int m_B;
};

//利用全局函数 实现<<运算符重载
ostream & operator<<( ostream & cout , Person & p1)
{
	cout << "m_A = " << p1.m_A << " m_B = " << p1.m_B ;

	return cout;
}

void test01()
{
	Person p1(10, 10);

	//cout << "m_A = " << p1.m_A << " m_B = " << p1.m_B << endl;

	cout << p1 << endl;

}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}