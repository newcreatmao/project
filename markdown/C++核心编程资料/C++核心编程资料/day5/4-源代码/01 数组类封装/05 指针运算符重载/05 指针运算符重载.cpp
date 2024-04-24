#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person(int age )
	{
		cout << "有参构造函数" << endl;
		this->m_Age = age;
	}

	void showAge()
	{
		cout << "年龄为： " << this->m_Age << endl;
	}

	~Person()
	{
		cout << "析构函数调用" << endl;
	}

private:
	int m_Age;//年龄
};

//智能指针  用来托管new出来的对象的释放
class SmartPointer
{
public:
	SmartPointer(Person * person)
	{
		cout << "SmartPointer构造函数调用" << endl;
		this->person = person;
	}

	//重载指针运算符 
	Person * operator->()
	{
		return this->person;
	}

	//重载*运算符
	Person& operator*()
	{
		return *this->person;
	}

	~SmartPointer()
	{
		if (this->person != NULL)
		{
			cout << "SmartPointer析构函数调用" << endl;
			delete this->person;
			this->person = NULL;
		}
	}


private:
	Person * person;
};


void test01()
{
	 Person * p = new Person(18);
	 //p->showAge();
	 //(*p).showAge();

	 //delete p;

	SmartPointer sp = SmartPointer(new Person(18));
	sp->showAge(); // sp->->showAge(); 编译器简化为 sp->showAge();
	(*sp).showAge();
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}