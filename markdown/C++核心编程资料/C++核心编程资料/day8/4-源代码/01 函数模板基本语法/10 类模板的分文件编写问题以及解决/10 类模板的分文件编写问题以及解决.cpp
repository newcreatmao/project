#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include "Person.hpp"

void test01()
{
	//��ģ�� �����������ļ���д����Ϊ��Ա��������ʱ�������н׶Σ�ʹ��ʱ�����Ҫ����.cpp�ſ���
	Person<string, int> p("aaa", 100);

	p.showPerson();

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}