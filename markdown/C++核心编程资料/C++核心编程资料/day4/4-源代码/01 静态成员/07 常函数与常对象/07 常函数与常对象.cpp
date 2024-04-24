#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


class Person
{
public:

	// 常函数
	// 成员函数声明后面 加 const  代表常函数，不可以修改成员属性了
	void showPerson() const
	{
		// const  Person * const  this
		// this指针的本质  是一个指针常量，指针的指向是不可以修改的，指针指向的值可以改
		cout << this->m_A << endl;
		
		//this = NULL;
		// this->m_A = 100; 

		this->m_B = 100;
	}

	void showPerson2()
	{
		this->m_A = 100;
		cout << "aaa" << endl;
	}

	int m_A;
	mutable int m_B; //即使是常函数，m_B我也想可以修改
};

void test01()
{
	Person p1;
	p1.m_A = 10;
	p1.showPerson();

}


//常对象
void test02()
{
	const Person p1; //常对象
	//常对象也不可以修改内部的属性
	//p1.m_A = 100;

	p1.m_B = 100; //m_B是特殊属性，即使的常对象 或者常函数 都是可以改


	p1.showPerson();  //常对象 只能调用  常函数
	//p1.showPerson2(); //常对象 是不可以调用普通的成员函数的

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}