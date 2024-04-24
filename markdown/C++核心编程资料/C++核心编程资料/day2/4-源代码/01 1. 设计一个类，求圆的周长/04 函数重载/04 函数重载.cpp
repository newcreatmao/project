#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//函数重载
//满足函数重载条件
//1、作用域必须相同
//2、函数名称相同
//3、函数的参数类型不同或者个数不同或者顺序不同

// 下面的func是成员函数  所以不能作为重载的条件
//class Person
//{
//	void func(){};
//};

void func()
{
	cout << "func （） 调用" << endl;
}

void func(int a)
{
	cout << "func （int a ） 调用" << endl;
}

void func(double a)
{
	cout << "func （double a ） 调用" << endl;
}

void func(int a , double b)
{
	cout << "func （int a , double b ） 调用" << endl;
}

void func(double a, int b)
{
	cout << "func （double a , int b ） 调用" << endl;
}

//int func(double a, int b)
//{
//cout << "func （double a , int b ） 调用" << endl;
//return 1;
//}


//返回值可以不可以作为重载条件
//结果  返回值不可以作为函数重载条件 ,原因会出现二义性
void test01()
{
	func(3.14 , 1);
}


//引用的重载版本
//对于引用而言 加const 和 不加const也可以作为重载条件

void myfunc(int a)
{
	cout << "myfunc(int a)调用 " << endl;
}

void myfunc(int &a) // int &a = 10;
{
	cout << "myfunc(int &a)调用 " << endl;
}

void myfunc(const  int &a) // const int &a = 10;
{
	cout << "myfunc(const int &a)调用 " << endl;
}


void test02()
{
	int a = 10;
	//如果出现 不加引用和加引用可以同时调用，注意要避免二义性
	//myfunc(a);
}



// 函数重载遇到函数的默认参数
void myfunc2(int a ,int b = 10)
{

}

void myfunc2(int a)
{

}

void test03()
{

	//注意避免二义性
	//myfunc2(10);
}


int main(){

	//test01();
	//test02();
	test03();

	system("pause");
	return EXIT_SUCCESS;
}