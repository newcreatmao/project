#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person()
	{
		cout << "Ĭ�Ϲ��캯������" << endl;
	}

	Person(int a)
	{
		m_Age = a;
		cout << "�вι��캯������" << endl;
	}

	Person(const  Person & p)
	{
		m_Age = p.m_Age;
		cout << "�������캯������" << endl;
	}

	~Person()
	{
		cout << "������������" << endl;
	}

	int m_Age;
};

//1��ϵͳ��Ĭ�ϸ�һ�����������3������  Ĭ�Ϲ��캯���������������������캯��(�򵥵�ֵ����)
void test01()
{
	Person p1(20);

	Person p2(p1);

	cout << p2.m_Age << endl;
}

//2����������Լ��ṩ�� �вεĹ��캯������ôϵͳ�Ͳ����ṩĬ�ϵĹ��캯����,������Ȼ���ṩ�������캯��
void test02()
{
	Person p1(10);
	Person p2(p1);

	cout << p2.m_Age << endl;
}

//3����������Լ��ṩ�� �������캯��  ����ôϵͳ�Ͳ����ṩ��������ͨ���캯����
void test03()
{
	
	//Person p1;
}



int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}