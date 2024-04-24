#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
	Base()
	{
		cout << "Base的构造函数调用" << endl;
	}

	~Base()
	{
		cout << "Base的析构函数调用" << endl;
	}
};


//继承中，先调用父类的构造，再调用子类的构造，析构的顺序和构造顺序相反的
class Son :public Base
{
public:
	Son()
	{
		cout << "Son的构造函数调用" << endl;
	}

	~Son()
	{
		cout << "Son的析构函数调用" << endl;
	}

};

void test01()
{
	//Base b;

	Son s;
}


class Base2
{
public:
	Base2(int a)
	{
		this->m_A = a;
	}
	int m_A;
};
// ： 代表继承
class Son2 :public Base2
{
public:
	//： 初始化列表
	// 可以利用初始化列表语法 显示指定出调用父类的哪个构造函数
	Son2(int a = 1000) : Base2(a)
	{
		
	}
	int m_B;
};

void test02()
{
	Son2 s(10);

}

//子类不会继承 父类中的构造和析构函数，只有父类自己才知道如果构造和析构自己的属性

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}