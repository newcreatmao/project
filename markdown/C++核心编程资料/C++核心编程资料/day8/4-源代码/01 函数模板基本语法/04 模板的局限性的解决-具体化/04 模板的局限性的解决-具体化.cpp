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

//ͨ��ģ������������ݱȽ�
template<class T>
bool myCompare(T & a, T &b)
{
	if (a == b)
	{
		return true;
	}
	return false;
}


//���þ��廯Person���������߱����� ��Person�Աȴ���
template<> bool myCompare<Person>(Person & a, Person  &b)
{
	cout << "���õ��Ǿ��廯����" << endl;
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
		cout << "p1��p2���" << endl;
	}
	else
	{
		cout << "�����" << endl;
	}
	
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}