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

	Person(const  Person & p )
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

//1��ʹ��һ���Ѿ������õĶ�������ʼ����һ������
void test01()
{
	Person p1(18);

	Person p2(p1);

	cout << "p2����Ϊ�� " << p2.m_Age << endl;
}


//2����ֵ���ݵķ�ʽ �������Ĳ�����ֵ
void doWork( Person p)
{
}

void test02()
{
	Person p1;
	doWork(p1);
}

//3����ֵ�ķ�ʽ���ؾֲ�����
Person doWork2()
{
	Person p1;

	return p1;
}


void test03()
{
	Person p = doWork2();
}

/*
   ������������������Ż�
   void doWork2(Person & p)
   {
   }
   void test03()
   {
	Person p;
	doWork2(p);
   }

*/


int main(){
	//test01();
	//test02();
	test03();



	system("pause");
	return EXIT_SUCCESS;
}