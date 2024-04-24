#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyException
{
public:
	void printError()
	{
		cout << "我自己的异常类的错误" << endl;
	}
};

class Person
{
public:
	Person()
	{
		cout << "Person的构造函数" << endl;
	}

	~Person()
	{
		cout << "Person的析构函数" << endl;
	}

};

int myDivide(int a , int b)
{
	if ( b == 0)
	{
		//return -1; //C语言处理异常缺陷在于  返回的值 没有统一，返回的值可以是异常的结果，也可以是正确的结果

		//抛出异常
		//throw 1;
		//throw 3.14;
		//throw 'a';


		//栈解旋： 从try代码块开始起，到 throw抛出异常前，所有栈上的对象都被释放掉，
		//	       释放的顺序和构造的顺序是相反的，这个过程称为栈解旋
		Person p1;
		Person p2;
		

		throw MyException(); //抛出一个 MyException 匿名对象
	}

	return a / b;

}

void test01()
{
	int a = 10;
	int b = 0;

	//尝试执行一段 可能会出现异常的代码
	try
	{
		int ret = myDivide(a, b);
		cout << "ret 结果为： " << ret << endl;
	}
	catch (int ) //捕获异常
	{
		cout << "int类型的异常的捕获" << endl;
	}
	catch (double) 
	{
		//捕获到double后 不想处理这个异常，想继续向上抛出这个异常
		throw;
		cout << "double类型的异常的捕获" << endl;
	}
	catch (MyException e)
	{
		e.printError();
	}
	catch (...)
	{
		cout << "其他类型异常的捕获" << endl;
	}

}


int main(){

	try
	{
		test01();
	}
	catch (int) //异常必须有人要处理，如果没有任何的处理，程序会自动调用一个terminate函数，让程序中断掉
	{
		cout << "main函数中的 int类型的异常的捕获" << endl;
	}
	catch (...)
	{
		cout << "mian函数中的 其他类型异常的捕获" << endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}