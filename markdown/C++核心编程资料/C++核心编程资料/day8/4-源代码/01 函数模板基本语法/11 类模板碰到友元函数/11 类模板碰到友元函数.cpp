#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

//告诉编译器 有个Person模板类，先不要报错
template<class T1, class T2> class Person;

//告诉编译器 有个函数模板的声明
template<class T1,class T2> void printPerson2(Person<T1, T2>&p);


//将函数模板  声明和实现写到一起
template<class T1, class T2>
void printPerson3(Person<T1, T2>&p)
{
	cout << "类外实现2 --- 姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
}

template <class T1, class T2>
class Person
{

	//1、全局函数 配合友元 做类内实现
	friend void printPerson(Person<T1,T2>&p)
	{
		cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
	}

	//2、全局函数 配合友元做 类外实现
	friend void printPerson2<>(Person<T1, T2>&p);

	//3、全局函数 配合友元做 类外实现
	friend void printPerson3<>(Person<T1, T2>&p);

public:
	Person(T1 name, T2 age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

private:
	T1 m_Name;
	T2 m_Age;
};

template<class T1, class T2>
void printPerson2(Person<T1, T2>&p)
{
	cout << "类外实现 --- 姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
}




void test01()
{
	Person<string, int>p("bbb", 20);
	//printPerson(p);


	//printPerson2(p);

	printPerson3(p);



}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}