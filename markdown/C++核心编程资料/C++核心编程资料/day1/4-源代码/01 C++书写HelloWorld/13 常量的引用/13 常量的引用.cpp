#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


void test01()
{
	//int & ref = 10;//引用必须引一块合法的内存空间
	const int &ref = 10;//但是加入const之后，语法就通过了，编译器优化：类似于  int temp = 10; const int & ref = temp;

	//ref = 1000;

	int * p = (int *)&ref;
	*p = 1000;
	cout << "ref = " << ref << endl;
}

//常量引用 使用场景  修饰函数中的形参  防止误操作
void showValue(const int &a)
{
	//a = 100000;
	cout << a << endl;
}

void test02()
{
	int a = 100;
	showValue(a);
}


int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}