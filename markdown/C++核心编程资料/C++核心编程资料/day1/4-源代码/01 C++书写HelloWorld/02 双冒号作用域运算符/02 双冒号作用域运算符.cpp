#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int atk = 1000;

void test01()
{
	int atk = 2000;
	cout << "�ֲ�������Ϊ�� " << atk  << endl;
	//:: �����������  ��::ǰ��û���κ�����������£�����ʹ��ȫ��������
	cout << "ȫ�ֹ�����Ϊ�� " << ::atk  << endl;

}


int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}