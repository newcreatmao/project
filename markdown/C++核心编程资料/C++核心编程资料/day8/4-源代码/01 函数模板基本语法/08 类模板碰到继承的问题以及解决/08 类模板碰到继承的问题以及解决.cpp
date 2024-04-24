#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

template<class T>
class Base
{
	T m_A; //子类创建时候 必须要知道T的类型，才能给父类中的m_A分配内存
};

template<class T1 , class T2>
class Son :public Base<T2>
{
	T1 m_B;
};


void test01()
{
	Son <int ,double>s;
	
}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}