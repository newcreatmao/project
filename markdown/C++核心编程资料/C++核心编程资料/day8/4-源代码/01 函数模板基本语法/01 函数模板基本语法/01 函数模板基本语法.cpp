#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

void mySwapInt(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void mySwapDouble(double &a, double &b)
{
	double temp = a;
	a = b;
	b = temp;
}


//利用模板实现通用交换函数
template<typename T> //T是一个通用类型，告诉编译器后面紧跟着的函数或者类中出现了T，不要报错
void mySwap(T & a  ,T & b )
{
	T temp = a;
	a = b;
	b = temp;
}


template<typename T>
void mySwap2()
{
}


void test01()
{
	int a = 10;
	int b = 20;
	char x = 'x';
	//mySwapInt(a, b);
	//1、自动类型推导   必须让编译器推导出一致的T，才能使用模板
	//mySwap(a, x); // a x不能推出 一致T类型
	//mySwap(a, b);

	//2、显示指定类型
	//mySwap<int>(a, x); // 显示指定类型 可以进行隐式类型转换，如果转不成功，那么也不可以使用模板
	mySwap<int>(a, b);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;


	mySwap2<double>(); //模板必须要指定出T的类型，才可以使用

	//double c = 1.1;
	//double d = 3.14;
	////mySwapDouble(c, d);
	//mySwap(c, d);
	//cout << "c = " << c << endl;
	//cout << "d = " << d << endl;
}





int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}