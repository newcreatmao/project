#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "myArray.hpp"
#include <string>

void printIntArray( MyArray<int>&myArr )
{
	for (int i = 0; i < myArr.getSize();i++)
	{
		cout << myArr[i] << " ";
	}
	cout << endl;
}



void test01()
{
	//测试 int 类型数组
	MyArray<int> myIntArray(100);
	for (int i = 0; i < 10;i++)
	{
		myIntArray.pushBack(i + 100);
	}

	//打印int类形数组
	printIntArray(myIntArray);

}

class Person
{
public:
	Person(){};
	Person(string name, int age) : m_Name(name), m_Age(age){}
	string m_Name;
	int m_Age;
};

void printPerons(MyArray <Person> & myArr)
{
	for (int i = 0; i < myArr.getSize();i++)
	{
		cout << "姓名： " << myArr[i].m_Name << " 年龄： " << myArr[i].m_Age << endl;
	}
}

void test02()
{
	//测试自定义数据类型  Person
	MyArray <Person> personArray(10);

	Person p1("孙悟空", 100);
	Person p2("孙尚香", 19);
	Person p3("刘备", 60);
	Person p4("关羽", 80);
	Person p5("张飞", 70);

	personArray.pushBack(p1);
	personArray.pushBack(p2);
	personArray.pushBack(p3);
	personArray.pushBack(p4);
	personArray.pushBack(p5);

	printPerons(personArray);

	cout << "数组大小： " << personArray.getSize() << endl;

}

int main(){
//	test01();

	test02();

	system("pause");
	return EXIT_SUCCESS;
}