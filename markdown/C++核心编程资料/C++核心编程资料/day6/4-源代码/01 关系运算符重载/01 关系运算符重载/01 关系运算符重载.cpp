#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	}

	bool operator==( const Person & p)
	{
		/*if (this->m_Name == p.m_Name && this->m_Age == p.m_Age)
		{
			return true;
		}
		return false;*/

		return this->m_Name == p.m_Name && this->m_Age == p.m_Age;
	}

	bool operator!=(const Person & p)
	{
		return !(this->m_Name == p.m_Name && this->m_Age == p.m_Age);
	}

	string m_Name;
	int m_Age;

};

void test01()
{
	//int a = 10;
	//int b = 10;
	//if ( a== b)
	//{
	//	cout << "a 等于 b" << endl;
	//}
	//else
	//{
	//	cout << "a不等于 b" << endl;
	//}

	Person p1("Tom", 10);
	Person p2("Tom", 10);

	if ( p1 == p2)
	{
		cout << "p1 等于 p2" << endl;
	}
	else
	{
		cout << "p1 不等于 p2" << endl;
	}

	if ( p1 != p2)
	{
		cout << "p1 不等于 p2" << endl;
	}
	else
	{
		cout << "p1 等于 p2" << endl;
	}

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}