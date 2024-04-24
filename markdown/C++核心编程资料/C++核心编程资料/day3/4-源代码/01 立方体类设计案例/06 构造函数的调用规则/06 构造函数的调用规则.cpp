#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person()
	{
		cout << "默认构造函数调用" << endl;
	}

	Person(int a)
	{
		m_Age = a;
		cout << "有参构造函数调用" << endl;
	}

	Person(const  Person & p)
	{
		m_Age = p.m_Age;
		cout << "拷贝构造函数调用" << endl;
	}

	~Person()
	{
		cout << "析构函数调用" << endl;
	}

	int m_Age;
};

//1、系统会默认给一个类添加至少3个函数  默认构造函数、析构函数、拷贝构造函数(简单的值拷贝)
void test01()
{
	Person p1(20);

	Person p2(p1);

	cout << p2.m_Age << endl;
}

//2、如果我们自己提供了 有参的构造函数，那么系统就不会提供默认的构造函数了,但是依然会提供拷贝构造函数
void test02()
{
	Person p1(10);
	Person p2(p1);

	cout << p2.m_Age << endl;
}

//3、如果我们自己提供了 拷贝构造函数  ，那么系统就不会提供其他的普通构造函数了
void test03()
{
	
	//Person p1;
}



int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}