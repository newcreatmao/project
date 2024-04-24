#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
template<class NAMETYPE, class AGETYPE >
class Person
{
public:
	Person(NAMETYPE name, AGETYPE age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	NAMETYPE m_Name;
	AGETYPE m_Age;

};

//1、指定传入类型
void doWork(Person<string,int>&p) 
{
	cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
}

void test01()
{
	Person <string, int> p1("aaa", 10);
	doWork(p1);
}

//2、参数模板化
template<class T1, class T2>
void doWork2(Person<T1,T2>&p)
{
	//cout << typeid(T1).name() << endl;
	//cout << typeid(T2).name() << endl;
	cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
}


void test02()
{
	Person <string, int> p1("bbb", 10);
	doWork2(p1);
}


//3、整个类模板化
template <class T>
void doWork3( T & p)
{
	cout << typeid(T).name() << endl;
	cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
}

void test03()
{
	Person <string, int> p1("ccc", 10);
	doWork3(p1);
}

int main(){

	//test01();
	//test02();
	test03();
	system("pause");
	return EXIT_SUCCESS;
}