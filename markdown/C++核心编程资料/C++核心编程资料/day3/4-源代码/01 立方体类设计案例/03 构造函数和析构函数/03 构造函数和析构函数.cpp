#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyClass
{
public:

	//1、构造函数的写法
	//没有返回值   也不写void  函数名与类名相同
	//可以有参数 ，可以发生重载
	//由编译器自动调用，不需要手动调用，而且编译器只会调用一次

	MyClass()
	{
		cout << "MyClass的构造函数调用" << endl;
	}


	MyClass(int a)
	{
		cout << "MyClass（int a）的构造函数调用" << endl;
	}

	//2、析构函数的写法
	//没有返回值  不写void  函数名与类名相同   在函数名称前加~
	//不可以有参数 ，不可以发生重载
	//由编译器自动调用，不需要手动调用，编译器也只调用一次

	~MyClass()
	{
		cout << "MyClass的析构函数的调用" << endl;
	}


};

void test01()
{
	MyClass myclass;

}

int main(){

	test01();

	

	system("pause");
	return EXIT_SUCCESS;
}