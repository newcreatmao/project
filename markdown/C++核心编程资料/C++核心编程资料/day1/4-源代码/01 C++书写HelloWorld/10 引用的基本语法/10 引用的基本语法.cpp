#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//引用 ： 给一个内存空间  起别名
//语法 ： Type &别名 = 原名
void test01()
{
	int a = 10;

	int &b = a;

	b = 20;

	cout << "a = " << a << endl;

}

//引用必须要初始化
void test02()
{
	int a = 10;
	int &b = a;

	//一旦初始化后  就不可以修改指向了
	int c = 20;
	b = c; //赋值

	cout << "a = " << a<<endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}

//建立对数组的引用
void test03()
{
	int arr[10];

	int(&pArr)[10] = arr;

	for (int i = 0; i < 10;i++)
	{
		arr[i] = i;
	}

	//for (int i = 0; i < 10;i++)
	//{
	//	cout << pArr[i] << endl;
	//}

	//先定义出数组的类型，再定义引用
	typedef int(ARRAY_TYPE)[10];
	//语法 ： Type &别名 = 原名
	ARRAY_TYPE &pArr2 = arr;
	for (int i = 0; i < 10; i++)
	{
		cout << pArr2[i] << endl;
	}

}


int main(){

	//test01();
	//test02();
	test03();
	system("pause");
	return EXIT_SUCCESS;
}