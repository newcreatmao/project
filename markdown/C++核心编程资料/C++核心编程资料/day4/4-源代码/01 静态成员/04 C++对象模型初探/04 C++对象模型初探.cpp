#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#pragma  pack(show) //对齐模数

class Person
{
public:


	int m_A; //成员属性 算在类的大小中

	//成员函数 并不算在类的大小中
	void func(  )
	{
		m_A = 100;
	}

	static int m_B; //静态成员变量 ，不属于类的大小中

	static void func2()//静态成员函数 ，不属于类的大小中
	{
		//m_A = 100;
	}

	double m_D;

};
int Person::m_B = 0;


void test01()
{
	
	// 空类的大小为：1   
	// 空类也是可以实例化对象的，每个对象在内存中都应该有独一无二的地址
	// Person p[10];    p[0]  p[1]
	cout << sizeof(Person) << endl;

	//this指针指向被调用的成员函数所属的对象
	Person p1;
	p1.func();

	Person p2;
	p2.func();
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}