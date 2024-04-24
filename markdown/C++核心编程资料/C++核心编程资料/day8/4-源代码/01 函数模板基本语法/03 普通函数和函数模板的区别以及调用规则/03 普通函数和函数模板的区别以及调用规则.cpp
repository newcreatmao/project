#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//普通函数 和 函数模板 区别
int myPlus(int a, int b)
{
	return  a + b;
}

template<class T>
T myPlus2(T a, T b)
{
	return a + b;
}

void test01()
{
	int a = 10;
	int b = 20;
	char c = 'c';
	cout << myPlus(a, c) << endl; //隐式类型转换 将 char c转为 int类型

	//myPlus2(a, c); //自动类型推导方式 ，不可以进行隐式类型转换的，但是显示指定类型方式可以进行隐式类型转换

}

//普通函数 和 函数模板 调用规则
template<class T>
void myPrint(T a, T b)
{
	cout << "函数模板调用" << endl;
}

/*
//假设传入T是int类型 ，生成一个 下面的函数，这个函数 称为 模板函数
void myPrint(int a, int b)
{
cout << "函数模板调用" << endl;
}

*/

template<class T>
void myPrint(T a, T b , T c)
{
	cout << "函数模板调用myPrint(T a, T b , T c)" << endl;
}

void myPrint(int a, int b)
{
	cout << "普通函数调用" << endl;
}

void test02()
{
	//1、如果普通函数和函数模板可以同时调用，优先使用是普通函数
	int a = 0;
	int b = 0;
	//myPrint(a, b);

	//2、如果想强制调用 函数模板中的内容，可以使用空参数列表
	//myPrint<>(a, b);

	////3、函数模板 可以发生函数重载
	//myPrint(a, b, 10);

	//4、如果函数模板可以产生更好的匹配，那么优先使用是函数模板
	char c = 'c';
	char d = 'd';
	myPrint(c, d);

}


int main(){

	//test01();
	test02();
	system("pause");
	return EXIT_SUCCESS;
}