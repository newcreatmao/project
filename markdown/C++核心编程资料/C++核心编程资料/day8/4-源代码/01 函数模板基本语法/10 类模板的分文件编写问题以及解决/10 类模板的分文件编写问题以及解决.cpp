#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "Person.hpp"

void test01()
{
	//类模板 不建议做分文件编写，因为成员函数创建时机在运行阶段，使用时候必须要包含.cpp才可以
	Person<string, int> p("aaa", 100);

	p.showPerson();

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}