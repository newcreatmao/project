#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
	static int m_A; // �������ݣ�����׶η����ڴ棬���������������ʼ��

	static void func()
	{
		cout << "Base�е�func����" << endl;
	}

	static void func(int a)
	{
		cout << "Base�е�func(int a)����" << endl;
	}

};

int Base::m_A = 10;


class Son :public Base
{
public:
	static int m_A;

	static void func()
	{
		cout << "Son�е�func����" << endl;
	}
};

int Son::m_A = 20;

void test01()
{
	//��m_A���з���
	Son s;
	cout << "son�е�m_A = "<<  s.m_A << endl;
	cout << "base�е�m_A = " << s.Base::m_A << endl;

	//ͨ���������з���
	cout << "ͨ���������� son�е�m_A = " << Son::m_A << endl;
	cout << "ͨ���������� base�е�m_A = " << Son::Base::m_A << endl;

	//ͬ����Ա���� ���е���
	s.func();
	Son::func();

	//������ͬ����Ա���� �����ص�����������ͬ����Ա���������ذ汾������ͨ���������ʵ������е������汾
	s.Base::func(1);
	Son::Base::func(1);

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}