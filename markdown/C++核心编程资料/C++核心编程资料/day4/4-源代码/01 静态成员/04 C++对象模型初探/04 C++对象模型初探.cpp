#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#pragma  pack(show) //����ģ��

class Person
{
public:


	int m_A; //��Ա���� ������Ĵ�С��

	//��Ա���� ����������Ĵ�С��
	void func(  )
	{
		m_A = 100;
	}

	static int m_B; //��̬��Ա���� ����������Ĵ�С��

	static void func2()//��̬��Ա���� ����������Ĵ�С��
	{
		//m_A = 100;
	}

	double m_D;

};
int Person::m_B = 0;


void test01()
{
	
	// ����Ĵ�СΪ��1   
	// ����Ҳ�ǿ���ʵ��������ģ�ÿ���������ڴ��ж�Ӧ���ж�һ�޶��ĵ�ַ
	// Person p[10];    p[0]  p[1]
	cout << sizeof(Person) << endl;

	//thisָ��ָ�򱻵��õĳ�Ա���������Ķ���
	Person p1;
	p1.func();

	Person p2;
	p2.func();
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}