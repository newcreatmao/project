#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、分类
//按照参数进行分类  有参构造函数    无参构造函数（默认构造函数）
//按照类型进行分类  普通构造函数    拷贝构造函数
class Person
{
public:
	//默认构造
	Person()
	{
		cout << "Person的默认构造函数调用" << endl;
	}
	//有参构造
	Person(int age)
	{
		m_Age = age;
		cout << "Person的有参构造函数调用" << endl;
	}

	//拷贝构造
	Person( const Person &p ) // 类名( const 类名&  aa )
	{
		cout << "Person的拷贝构造函数调用" << endl;
		m_Age = p.m_Age;
	}

	//析构函数
	~Person()
	{
		cout << "Person析构函数调用" << endl;
	}

	int m_Age;

};


//2、调用
void test01()
{
	////无参构造函数
	//Person p1;

	////有参构造函数
	////括号法
	//Person p2(10); //有参构造调用
	//Person p3(p2);  //拷贝构造函数调用

	//cout << "p3的年龄: " << p3.m_Age << endl;

	////显示法
	//Person p4 = Person(10); //有参构造函数
	//Person p5 = Person(p4); //拷贝构造函数调用


	//注意点 
	//Person p(); //不可以用括号法 调用无参构造函数 原因Person p();编译器认为是一个函数的声明

	//Person(10); //匿名函数对象 特点：当前行执行完后，系统就回收

	//Person(p5); //不可以调用拷贝构造函数 来初始化匿名函数对象 Person(p5); 编译器认为代码为 Person p5;  


	//隐式法
	Person p6 = 10; // Person p6 = 10; 等价于写了  Person p6 = Person(10)
	Person p7 = p6;

}


int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}