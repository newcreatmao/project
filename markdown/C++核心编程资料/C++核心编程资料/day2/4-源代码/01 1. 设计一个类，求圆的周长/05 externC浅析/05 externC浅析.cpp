#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#include "test.h"

//告诉编译器  下面有个 show函数 ，不要用C++的方式去链接，要用C语言的方式链接
//extern "C"  void show();



void test01()
{
	show(); //_Z4showv
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}