#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
	static int m_A; // 共享数据，编译阶段分配内存，类内声明，类外初始化

	static void func()
	{
		cout << "Base中的func调用" << endl;
	}

	static void func(int a)
	{
		cout << "Base中的func(int a)调用" << endl;
	}

};

int Base::m_A = 10;


class Son :public Base
{
public:
	static int m_A;

	static void func()
	{
		cout << "Son中的func调用" << endl;
	}
};

int Son::m_A = 20;

void test01()
{
	//对m_A进行访问
	Son s;
	cout << "son中的m_A = "<<  s.m_A << endl;
	cout << "base中的m_A = " << s.Base::m_A << endl;

	//通过类名进行访问
	cout << "通过类名访问 son中的m_A = " << Son::m_A << endl;
	cout << "通过类名访问 base中的m_A = " << Son::Base::m_A << endl;

	//同名成员函数 进行调用
	s.func();
	Son::func();

	//子类中同名成员函数 会隐藏掉父类中所有同名成员函数的重载版本，可以通过类名访问到父类中的其他版本
	s.Base::func(1);
	Son::Base::func(1);

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}