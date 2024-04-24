#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
class MyFunc
{
public:

	void operator()(string text)
	{
		cout << text << endl;
	}

};

void myFunc(string str)
{
	cout << str << endl;
}

void test01()
{
	MyFunc func; // 仿函数
	func("hello world");


	//myFunc("hello world");
}


class MyAdd
{
public:

	int operator()(int a ,int b)
	{
		return a + b;
	}

};

void test02()
{
	MyAdd myAdd;
	cout << myAdd(1, 1) << endl;

	//  MyAdd()(10, 10) 匿名函数对象
	cout << MyAdd()(10, 10) << endl;

}

int main(){

	//test01();
	test02();
	system("pause");
	return EXIT_SUCCESS;
}