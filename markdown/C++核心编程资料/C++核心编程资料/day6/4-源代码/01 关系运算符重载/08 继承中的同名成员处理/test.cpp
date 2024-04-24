#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
	Base()
	{
		this->m_A = 100;
	}

	void func()
	{
		cout << "Base中的Func调用" << endl;
	}

	void func(int a)
	{
		cout << "Base中的Func(int a)调用" << endl;
	}

	int m_A;
};

class Son : public Base
{
public:
	Son()
	{
		this->m_A = 200;
	}

	void func()
	{
		cout << "Son中的Func调用" << endl;
	}

	int m_A;
};

void test01()
{
	Son s;

	cout << s.m_A << endl; //调用Son类的 m_A 
	cout << "Base中的m_A " << s.Base::m_A << endl; //调用Base类中的m_A

	//同名的成员函数 ，子类会隐藏掉父类中的所有版本
	s.func();//调用Son类的 func 
	s.Base::func(10);//调用Base类的 func 

}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}