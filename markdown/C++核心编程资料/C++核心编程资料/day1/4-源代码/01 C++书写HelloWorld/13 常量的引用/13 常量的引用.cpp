#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


void test01()
{
	//int & ref = 10;//���ñ�����һ��Ϸ����ڴ�ռ�
	const int &ref = 10;//���Ǽ���const֮���﷨��ͨ���ˣ��������Ż���������  int temp = 10; const int & ref = temp;

	//ref = 1000;

	int * p = (int *)&ref;
	*p = 1000;
	cout << "ref = " << ref << endl;
}

//�������� ʹ�ó���  ���κ����е��β�  ��ֹ�����
void showValue(const int &a)
{
	//a = 100000;
	cout << a << endl;
}

void test02()
{
	int a = 100;
	showValue(a);
}


int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}