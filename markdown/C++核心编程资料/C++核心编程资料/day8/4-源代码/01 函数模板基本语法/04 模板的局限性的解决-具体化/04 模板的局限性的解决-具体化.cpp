#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	string m_Name;
	int m_Age;
};

//通过模板进行两个数据比较
template<class T>
bool myCompare(T & a, T &b)
{
	if (a == b)
	{
		return true;
	}
	return false;
}


//利用具体化Person函数，告诉编译器 走Person对比代码
template<> bool myCompare<Person>(Person & a, Person  &b)
{
	cout << "调用的是具体化代码" << endl;
	if (a.m_Name == b.m_Name && a.m_Age == b.m_Age)
	{
		return true;
	}
	return false;
}

void test01()
{
	Person p1("Tom", 19);
	Person p2("Jerry", 20);

	bool ret =  myCompare(p1, p2);
	if (ret )
	{
		cout << "p1与p2相等" << endl;
	}
	else
	{
		cout << "不相等" << endl;
	}
	
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}