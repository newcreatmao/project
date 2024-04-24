#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:

	//静态成员变量
	//1、数据共享
	//2、在编译阶段就分配了内存
	//3、在类内声明、类外进行初始化
	static int m_A;

	void func2() //非静态成员函数 可以访问静态成员变量 也可以访问 非静态成员变量
	{
		m_C = 100;
		m_A = 1000;
	}

	static void func()
	{
		//m_C = 100; //静态成员函数 是不可以访问非静态成员变量
		m_A = 1000;  //静态成员函数  可以访问 静态成员变量，因为都是共享数据
		cout << "静态成员函数调用" << endl;
	}

	int m_C;

private:
	static int m_B;//私有权限的数据 类外访问不到

	static void func3(){ cout << "aaa" << endl; };

};

int Person::m_A = 10; //静态成员变量 类外初始化

int Person::m_B = 20;

void test01()
{
	//访问方式
	//1、通过对象进行访问
	Person p1;
	cout <<"p1的m_A ： " <<  p1.m_A << endl;

	Person p2;
	p2.m_A = 20;
	cout << "p1的m_A ： " << p1.m_A << endl;
	cout << "p2的m_A ： " << p2.m_A << endl;

	//2、通过类名进行访问
	cout << "m_A :" << Person::m_A << endl;

	//静态成员变量也是有访问权限的
	// Person::m_B = 100;  m_B是私有权限 因此在类外访问不到

}

void test02()
{
	//1、通过对象可以进行调用
	Person p1;
	p1.func();

	//2、通过类名进行调用
	Person::func();

	//Person::func3();//静态成员函数也是有访问权限的，私有的权限类外访问不到

}



int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}