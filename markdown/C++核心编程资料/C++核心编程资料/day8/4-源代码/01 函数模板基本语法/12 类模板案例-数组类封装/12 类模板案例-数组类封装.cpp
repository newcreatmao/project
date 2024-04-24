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
	//���� int ��������
	MyArray<int> myIntArray(100);
	for (int i = 0; i < 10;i++)
	{
		myIntArray.pushBack(i + 100);
	}

	//��ӡint��������
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
		cout << "������ " << myArr[i].m_Name << " ���䣺 " << myArr[i].m_Age << endl;
	}
}

void test02()
{
	//�����Զ�����������  Person
	MyArray <Person> personArray(10);

	Person p1("�����", 100);
	Person p2("������", 19);
	Person p3("����", 60);
	Person p4("����", 80);
	Person p5("�ŷ�", 70);

	personArray.pushBack(p1);
	personArray.pushBack(p2);
	personArray.pushBack(p3);
	personArray.pushBack(p4);
	personArray.pushBack(p5);

	printPerons(personArray);

	cout << "�����С�� " << personArray.getSize() << endl;

}

int main(){
//	test01();

	test02();

	system("pause");
	return EXIT_SUCCESS;
}