#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
	Base()
	{
		this->m_A = 100;
	}

	void func()
	{
		cout << "Base�е�Func����" << endl;
	}

	void func(int a)
	{
		cout << "Base�е�Func(int a)����" << endl;
	}

	int m_A;
};

class Son : public Base
{
public:
	Son()
	{
		this->m_A = 200;
	}

	void func()
	{
		cout << "Son�е�Func����" << endl;
	}

	int m_A;
};

void test01()
{
	Son s;

	cout << s.m_A << endl; //����Son��� m_A 
	cout << "Base�е�m_A " << s.Base::m_A << endl; //����Base���е�m_A

	//ͬ���ĳ�Ա���� ����������ص������е����а汾
	s.func();//����Son��� func 
	s.Base::func(10);//����Base��� func 

}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}