#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
//��ģ�� 
//template��������ŵ��������࣬��ô������Ϊ ��ģ��
//  ��ģ���е����� Ҳ������Ĭ�ϲ���
// ���ͱ��  ���Ͳ�����

template<class NAMETYPE, class AGETYPE = int >
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

void test01()
{
	//Person p1("Tom", 11); // ������ģ�壬ʹ��ʱ�򲻿������Զ������Ƶ�
	Person<string> p1 ("Tom", 11); //��ģ���������ʾָ������
	cout << "������ " << p1.m_Name << " ���䣺 " << p1.m_Age << endl;
}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}