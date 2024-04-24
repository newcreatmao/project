#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

void mySwapInt(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void mySwapDouble(double &a, double &b)
{
	double temp = a;
	a = b;
	b = temp;
}


//����ģ��ʵ��ͨ�ý�������
template<typename T> //T��һ��ͨ�����ͣ����߱�������������ŵĺ����������г�����T����Ҫ����
void mySwap(T & a  ,T & b )
{
	T temp = a;
	a = b;
	b = temp;
}


template<typename T>
void mySwap2()
{
}


void test01()
{
	int a = 10;
	int b = 20;
	char x = 'x';
	//mySwapInt(a, b);
	//1���Զ������Ƶ�   �����ñ������Ƶ���һ�µ�T������ʹ��ģ��
	//mySwap(a, x); // a x�����Ƴ� һ��T����
	//mySwap(a, b);

	//2����ʾָ������
	//mySwap<int>(a, x); // ��ʾָ������ ���Խ�����ʽ����ת�������ת���ɹ�����ôҲ������ʹ��ģ��
	mySwap<int>(a, b);

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;


	mySwap2<double>(); //ģ�����Ҫָ����T�����ͣ��ſ���ʹ��

	//double c = 1.1;
	//double d = 3.14;
	////mySwapDouble(c, d);
	//mySwap(c, d);
	//cout << "c = " << c << endl;
	//cout << "d = " << d << endl;
}





int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}