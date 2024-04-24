#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "game1.h"
#include "game2.h"

//1、命名空间 用途  解决命名冲突
void test01()
{
	LOL::goAtk();
	kingGlory::goAtk();
}

//2、命名空间下  可以存放 变量、函数、结构体、类....
namespace A
{
	int m_A = 10;
	void func(){};
	struct Person
	{
		int age;
	};

	class Animal
	{
		int age;
	};
}

//3、命名空间必须 声明下 全局作用域下
//void func()
//{
//	namespace B
//	{
//
//	}
//}

//4、命名空间  可以 嵌套命名空间
namespace B
{
	int m_A = 10;
	namespace C
	{
		int m_A = 20;
	}
}

void test02()
{
	cout << "B空间下的m_A = " << B::m_A << endl;
	cout << "C空间下的m_A = " << B::C::m_A << endl;
}

//5、命名空间是开放的，可以随时向命名空间下添加新的成员
namespace B
{
	int m_B = 100;
}
void test03()
{
	cout << "B空间下的m_A = " << B::m_A << endl;
	cout << "B空间下的m_B = " << B::m_B << endl;
}

//6、命名空间是可以匿名的
namespace
{
	int m_C = 100;
	int m_D = 200;
	//相当于 在变量前加了一个关键字  static
	// static int m_C = 100;
	// static int m_D = 200;
}

void test04()
{
	cout << "m_D = " << ::m_D << endl;
}

//7、命名空间是可以起别名的
namespace veryLongName
{
	int m_A = 1000;
}
void test05()
{
	namespace veryShortName = veryLongName;

	cout << veryShortName::m_A << endl;
	cout << veryLongName::m_A << endl;

}


int main(){

	//test01();
	//test02();
	//test03();
	//test04();
	test05();

	system("pause");
	return EXIT_SUCCESS;
}