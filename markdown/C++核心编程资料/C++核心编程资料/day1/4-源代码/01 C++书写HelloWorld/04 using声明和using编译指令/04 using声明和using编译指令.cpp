#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

namespace kingGlory
{
	int sunwukongId = 1;
}

void test01()
{
	int sunwukongId = 2;

	//1、using 声明
	//当就近原则 和 using声明同时出现时候 ，需要避免二义性
	//using kingGlory::sunwukongId;

	//cout << "sunwukongId = " << kingGlory::sunwukongId << endl;
}


namespace LOL
{
	int sunwukongId = 3;
}

void test02()
{
	//int sunwukongId = 2;

	//2、using 编译指令
	using namespace kingGlory;
	using namespace LOL;

	//如果有就近原则出现 ，那么优先使用就近原则
	//如果using编译指令 存在多个并且有同名出现，需要加作用域区分
	cout << "sunwukongId = " << LOL::sunwukongId << endl;
}



int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}