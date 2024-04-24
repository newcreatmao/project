#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
//
//class calculator
//{
//public:
//	int getResult(string oper)
//	{
//		if (oper == "+")
//		{
//			return m_A + m_B;
//		}
//		else if (oper == "-")
//		{
//			return m_A - m_B;
//		}
//		else if (oper == "*")
//		{
//			return m_A * m_B;
//		}
//
//	}
//
//	int m_A;
//	int m_B;
//
//};

//开发有个原则 ---  开闭原则 
// 开闭原则  --- 对扩展进行开放 对修改进行关闭


//利用多态实现计算器

class AbstractCalculator
{
public:

	//纯虚函数
	virtual int getResult() = 0;
	//如果一个类中有纯虚函数出现，那么这个类就无法实例化对象了
	//有纯虚函数的类，也称为  抽象类


	//virtual int getResult()
	//{
	//	return  0;
	//}
	int m_A;
	int m_B;
};

//如果子类继承了抽象类，那么子类必须要重写父类中的纯虚函数，否则子类也属于抽象类
//class A :public AbstractCalculator
//{
//public:
//	virtual int getResult()
//	{
//		return 0;
//	}
//};

//加法计算器
class AddCalculator: public AbstractCalculator
{
public:
	virtual int getResult()
	{
		return  m_A + m_B;
	}
};


//减法计算器
class SubCalculator :public AbstractCalculator
{
public:
	virtual int getResult()
	{
		return  m_A - m_B;
	}
};

//乘法计算器
class MultiCalculator :public AbstractCalculator
{
public:
	virtual int getResult()
	{
		return  m_A * m_B;
	}
};



void test01()
{
	//加法计算器
	AbstractCalculator * calculator = new AddCalculator;
	calculator->m_A = 10;
	calculator->m_B = 20;

	cout << calculator->getResult() << endl;

	delete calculator;

	//改为减法计算器
	calculator = new SubCalculator;
	calculator->m_A = 10;
	calculator->m_B = 20;

	cout << calculator->getResult() << endl;
}

//多态的好处：  对扩展性提高，组织性强，可读性强
//如果父类中有了虚函数，子类并没有重写父类的虚函数，那么这样的代码是毫无意义的
//如果子类不重写父类虚函数，那么没有用到多态带来的好处 ，而且内部结构还变得更为复杂

int main(){


	test01();


	system("pause");
	return EXIT_SUCCESS;
}