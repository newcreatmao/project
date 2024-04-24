#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base1
{
public:
	Base1()
	{
		this->m_A = 10;
	}
	int m_A;
};

class Base2
{
public:
	Base2()
	{
		this->m_A = 20;
	}
	int m_A;
};

//多继承语法 
class Son : public Base1, public Base2
{
public:

	int m_C;
	int m_D;
};



void test01()
{
	cout << sizeof (Son) << endl;
	Son s;
	cout << "Base1中的 m_A = " << s.Base1::m_A << endl;
	cout << "Base2中的 m_A = " << s.Base2::m_A << endl;
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}