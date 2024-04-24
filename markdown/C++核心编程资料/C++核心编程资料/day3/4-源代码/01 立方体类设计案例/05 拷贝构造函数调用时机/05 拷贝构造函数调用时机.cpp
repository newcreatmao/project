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

	Person(const  Person & p )
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

//1、使用一个已经创建好的对象来初始化另一个对象
void test01()
{
	Person p1(18);

	Person p2(p1);

	cout << "p2年龄为： " << p2.m_Age << endl;
}


//2、以值传递的方式 给函数的参数传值
void doWork( Person p)
{
}

void test02()
{
	Person p1;
	doWork(p1);
}

//3、以值的方式返回局部对象
Person doWork2()
{
	Person p1;

	return p1;
}


void test03()
{
	Person p = doWork2();
}

/*
   编译器将代码进行了优化
   void doWork2(Person & p)
   {
   }
   void test03()
   {
	Person p;
	doWork2(p);
   }

*/


int main(){
	//test01();
	//test02();
	test03();



	system("pause");
	return EXIT_SUCCESS;
}