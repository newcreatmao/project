#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person()
	{
		cout << "默认构造函数调用" << endl;
	}

	Person(int a)
	{
		m_Age = a;
		cout << "有参构造函数调用" << endl;
	}

	Person(const  Person & p)
	{
		m_Age = p.m_Age;
		cout << "拷贝构造函数调用" << endl;
	}

	~Person()
	{
		cout << "析构函数调用" << endl;
	}

	int m_Age;
};

//1、malloc 和 new 区别
// new delete 是一个运算符   malloc  free 是一个库函数
// malloc 返回值 void *   new 返回的是new出来的对象的指针
// malloc 需要判断是否开辟成功 而new内部做好了操作(内部会malloc数据在堆区，判断内存是否分配成，调用构造函数)
// malloc 不会调用构造函数   而 new调用构造函数   
// malloc 对应的释放是 free      new 对应的释放是  delete
void test01()
{

	
	//Person p1; //开辟栈上

	//开辟到堆区
	Person * p1 = new Person;
	Person * p2 = new Person(10);
	Person * p3 = new Person(*p2);

	//释放new出来的对象
	delete p1;
	delete p2;
	delete p3;
}

//2、注意事项
void test02()
{
	//不要用void * 去接受new出来的对象，原因是不能够释放
	void * p = new Person;
	delete (Person * )p;
}

//3、利用new创建数组
void test03()
{
  //int* pInt =	new int[10];
  //char * pChar = new char[64];

	//利用new 在堆区创建数组，类中必须要存在默认构造函数，否则无法创建
	Person * persons = new Person[10];

	//如果数组是在栈上开辟的，那么可以指定利用哪个构造函数来初始化对象
	//Person persons2[3] = { Person(10), Person(10), Person(10) };

	//如果是数组 释放时候要在 delete后加 []
	delete [] persons;

}

int main(){

	//test01();
	//test02();
	test03();


	system("pause");
	return EXIT_SUCCESS;
}