#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、值传递
void mySwap01(int a , int b)
{
	int temp = a;
	a = b;
	b = temp;


	cout << "mySwap01 a = " << a << endl;
	cout << "mySwap01 b = " << b << endl;
}

void test01()
{
	int a = 10;
	int b = 20;

	mySwap01(a, b);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
}


//2、地址传递
void mySwap02(int * a, int * b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void test02()
{
	int a = 10;
	int b = 20;

	mySwap02(&a, &b);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
}


//3、引用传递
void mySwap03(int &a, int &b) // int &a = a ;  int &b = b;
{
	int temp = a;
	a = b;
	b = temp;

}

void test03()
{
	int a = 10;
	int b = 20;

	mySwap03(a, b);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;

}

//引用的注意事项
//1、不要返回局部变量的引用

int& myFunc()
{
	int a = 10;
	return a;
}

void test04()
{
	int &ret = myFunc();
	cout << "ret = " << ret << endl; //编译器优化结果，保存住之前的数据
	cout << "ret = " << ret << endl;
	cout << "ret = " << ret << endl;
	cout << "ret = " << ret << endl;

}


//2、如果函数的返回值是一个引用，那么这个函数可以作为左值进行运算
int& myFunc2()
{
	static int a = 10;
	return a;
}

void test05()
{
	int &ret = myFunc2();
	cout << "ret = " << ret << endl; //编译器优化结果，保存住之前的数据
	cout << "ret = " << ret << endl;
	cout << "ret = " << ret << endl;
	cout << "ret = " << ret << endl;

	myFunc2() = 100;
	cout << "ret = " << ret << endl;
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