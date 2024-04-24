#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person(){};
	Person(int a, int b) :m_A(a), m_B(b)
	{}

	//利用成员函数 重载
	//+号运算符重载
	//Person operator+(Person & p)
	//{
	//	Person temp;
	//	temp.m_A = this->m_A + p.m_A;
	//	temp.m_B = this->m_B + p.m_B;
	//	return temp;
	//}


	int m_A;
	int m_B;
};

//利用全局函数进行+运算符重载
Person operator+(Person & p1, Person & p2)
{
	Person temp;
	temp.m_A = p1.m_A + p2.m_A;
	temp.m_B = p1.m_B + p2.m_B;

	return temp;

}

//运算符重载 发生 函数重载
Person operator+(Person & p1, int a)
{
	Person temp;
	temp.m_A = p1.m_A + a;
	temp.m_B = p1.m_B + a;

	return temp;
}

void test01()
{
	Person p1(10, 10);
	Person p2(10, 10);

	Person p3 = p1 + p2;

	//本质
	//成员函数的本质
	//Person p3 = p1.operator+(p2);
	//全局函数的本质
	//Person p3 = operator+(p1, p2);

	cout << "p3的m_A = " << p3.m_A << endl;
	cout << "p3的m_B = " << p3.m_B << endl;

	//运算符重载 可不可以发生函数重载？ 可以！

	Person p4 =  p1 + 100;
	cout << "p4的m_A = " << p4.m_A << endl;
	cout << "p4的m_B = " << p4.m_B << endl;

}


int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}