#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#include "test.h"

//���߱�����  �����и� show���� ����Ҫ��C++�ķ�ʽȥ���ӣ�Ҫ��C���Եķ�ʽ����
//extern "C"  void show();



void test01()
{
	show(); //_Z4showv
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}