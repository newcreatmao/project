#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "game1.h"
#include "game2.h"

//1�������ռ� ��;  ���������ͻ
void test01()
{
	LOL::goAtk();
	kingGlory::goAtk();
}

//2�������ռ���  ���Դ�� �������������ṹ�塢��....
namespace A
{
	int m_A = 10;
	void func(){};
	struct Person
	{
		int age;
	};

	class Animal
	{
		int age;
	};
}

//3�������ռ���� ������ ȫ����������
//void func()
//{
//	namespace B
//	{
//
//	}
//}

//4�������ռ�  ���� Ƕ�������ռ�
namespace B
{
	int m_A = 10;
	namespace C
	{
		int m_A = 20;
	}
}

void test02()
{
	cout << "B�ռ��µ�m_A = " << B::m_A << endl;
	cout << "C�ռ��µ�m_A = " << B::C::m_A << endl;
}

//5�������ռ��ǿ��ŵģ�������ʱ�������ռ�������µĳ�Ա
namespace B
{
	int m_B = 100;
}
void test03()
{
	cout << "B�ռ��µ�m_A = " << B::m_A << endl;
	cout << "B�ռ��µ�m_B = " << B::m_B << endl;
}

//6�������ռ��ǿ���������
namespace
{
	int m_C = 100;
	int m_D = 200;
	//�൱�� �ڱ���ǰ����һ���ؼ���  static
	// static int m_C = 100;
	// static int m_D = 200;
}

void test04()
{
	cout << "m_D = " << ::m_D << endl;
}

//7�������ռ��ǿ����������
namespace veryLongName
{
	int m_A = 1000;
}
void test05()
{
	namespace veryShortName = veryLongName;

	cout << veryShortName::m_A << endl;
	cout << veryLongName::m_A << endl;

}


int main(){

	//test01();
	//test02();
	//test03();
	//test04();
	test05();

	system("pause");
	return EXIT_SUCCESS;
}