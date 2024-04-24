#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Animal
{
public:
	Animal()
	{
		cout << "Animal的构造函数调用" << endl;
	}

	//虚析构 解决的问题是  当子类中有堆区内容，释放时候对导致释放不干净，内存泄露
	//virtual ~Animal()
	//{
	//	cout << "Animal的析构函数调用" << endl;
	//}

	//纯虚析构
	//有声明  也必须有实现，类外实现
	// 如果一个类中 有了 纯虚析构函数后，那么这个类 也属于抽象类
	virtual ~Animal() = 0;


	virtual void speak()
	{
		cout << "动物在说话" << endl;
	}

	

};

Animal::~Animal()
{

	cout << "Animal的纯虚析构函数调用" << endl;
}


class Cat :public Animal
{
public:

	Cat(char * name)
	{
		cout << "Cat的构造函数的调用" << endl;
		this->m_Name = new char[strlen(name) + 1];
		strcpy(this->m_Name, name);
	}

	void speak()
	{
		cout << m_Name <<"小猫在说话" << endl;
	}

	~Cat()
	{
		if (this->m_Name != NULL)
		{
			cout << "Cat的析构函数的调用" << endl;
			delete [] this->m_Name;
			this->m_Name = NULL;
		}
	}

	char * m_Name; //猫的姓名
};


void test01()
{
	Animal * animal = new Cat("Tom");

	animal->speak();


	delete animal;
}

int main(){

	test01();


	system("pause");
	return EXIT_SUCCESS;
}