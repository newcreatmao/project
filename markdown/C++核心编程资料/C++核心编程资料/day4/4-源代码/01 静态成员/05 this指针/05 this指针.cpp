#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person(int age)
	{
		//this指针指向的是被调用的成员函数所属的对象
		this->age = age;
	}

	void showAge()
	{
		cout << "年龄：" << this->age << endl;
	}

	Person &  AddAge( Person & p)
	{
		this->age += p.age;
		return *this;
	}

	int age;
};

void test01()
{
	Person p1(18);

	//cout << "p1的年龄为：" << p1.age << endl;
	p1.showAge();


	Person p2(10);

	p1.AddAge(p2).AddAge(p2).AddAge(p2); //链式编程

	p1.showAge();

}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}