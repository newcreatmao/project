#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、函数的默认参数

int func(int a = 1 , int b = 1)
{
	return a + b;

}

void test01()
{
	cout << func(10) << endl;

}

//2、注意事项
// 如果参数列表中 有一位置有了默认参数，那么从这个位置起从左到右都必须有默认参数
int func2(int a = 1 , int b = 1 , int c = 1 )
{
	return a + b + c;

}

void test02()
{
	cout << func2(10) << endl;

}

//函数的声明和实现 只能有一个有默认参数
int func3(int a = 100, int b = 200);
int func3(int a , int b){ return a + b; };

void test03()
{
	cout << func3() << endl;;
}




//3、函数的占位参数
//占位参数 用途： 目前没有，后面学习符号重载时候会用到一点点
int func4(int a , int = 10  )
{
	return a;	
}
void test04()
{
	func4(1);
}



int main(){
	//test01();
	//test02();
	test03();


	system("pause");
	return EXIT_SUCCESS;
}