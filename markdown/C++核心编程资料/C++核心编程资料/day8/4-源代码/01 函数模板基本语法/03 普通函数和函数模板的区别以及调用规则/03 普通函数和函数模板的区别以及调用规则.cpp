#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//��ͨ���� �� ����ģ�� ����
int myPlus(int a, int b)
{
	return  a + b;
}

template<class T>
T myPlus2(T a, T b)
{
	return a + b;
}

void test01()
{
	int a = 10;
	int b = 20;
	char c = 'c';
	cout << myPlus(a, c) << endl; //��ʽ����ת�� �� char cתΪ int����

	//myPlus2(a, c); //�Զ������Ƶ���ʽ �������Խ�����ʽ����ת���ģ�������ʾָ�����ͷ�ʽ���Խ�����ʽ����ת��

}

//��ͨ���� �� ����ģ�� ���ù���
template<class T>
void myPrint(T a, T b)
{
	cout << "����ģ�����" << endl;
}

/*
//���贫��T��int���� ������һ�� ����ĺ������������ ��Ϊ ģ�庯��
void myPrint(int a, int b)
{
cout << "����ģ�����" << endl;
}

*/

template<class T>
void myPrint(T a, T b , T c)
{
	cout << "����ģ�����myPrint(T a, T b , T c)" << endl;
}

void myPrint(int a, int b)
{
	cout << "��ͨ��������" << endl;
}

void test02()
{
	//1�������ͨ�����ͺ���ģ�����ͬʱ���ã�����ʹ������ͨ����
	int a = 0;
	int b = 0;
	//myPrint(a, b);

	//2�������ǿ�Ƶ��� ����ģ���е����ݣ�����ʹ�ÿղ����б�
	//myPrint<>(a, b);

	////3������ģ�� ���Է�����������
	//myPrint(a, b, 10);

	//4���������ģ����Բ������õ�ƥ�䣬��ô����ʹ���Ǻ���ģ��
	char c = 'c';
	char d = 'd';
	myPrint(c, d);

}


int main(){

	//test01();
	test02();
	system("pause");
	return EXIT_SUCCESS;
}