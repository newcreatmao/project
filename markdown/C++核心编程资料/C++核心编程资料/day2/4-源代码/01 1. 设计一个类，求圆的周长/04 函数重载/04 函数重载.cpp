#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//��������
//���㺯����������
//1�������������ͬ
//2������������ͬ
//3�������Ĳ������Ͳ�ͬ���߸�����ͬ����˳��ͬ

// �����func�ǳ�Ա����  ���Բ�����Ϊ���ص�����
//class Person
//{
//	void func(){};
//};

void func()
{
	cout << "func ���� ����" << endl;
}

void func(int a)
{
	cout << "func ��int a �� ����" << endl;
}

void func(double a)
{
	cout << "func ��double a �� ����" << endl;
}

void func(int a , double b)
{
	cout << "func ��int a , double b �� ����" << endl;
}

void func(double a, int b)
{
	cout << "func ��double a , int b �� ����" << endl;
}

//int func(double a, int b)
//{
//cout << "func ��double a , int b �� ����" << endl;
//return 1;
//}


//����ֵ���Բ�������Ϊ��������
//���  ����ֵ��������Ϊ������������ ,ԭ�����ֶ�����
void test01()
{
	func(3.14 , 1);
}


//���õ����ذ汾
//�������ö��� ��const �� ����constҲ������Ϊ��������

void myfunc(int a)
{
	cout << "myfunc(int a)���� " << endl;
}

void myfunc(int &a) // int &a = 10;
{
	cout << "myfunc(int &a)���� " << endl;
}

void myfunc(const  int &a) // const int &a = 10;
{
	cout << "myfunc(const int &a)���� " << endl;
}


void test02()
{
	int a = 10;
	//������� �������úͼ����ÿ���ͬʱ���ã�ע��Ҫ���������
	//myfunc(a);
}



// ������������������Ĭ�ϲ���
void myfunc2(int a ,int b = 10)
{

}

void myfunc2(int a)
{

}

void test03()
{

	//ע����������
	//myfunc2(10);
}


int main(){

	//test01();
	//test02();
	test03();

	system("pause");
	return EXIT_SUCCESS;
}