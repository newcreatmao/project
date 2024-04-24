#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyException
{
public:
	MyException()
	{
		cout << "MyException构造函数调用" << endl;
	}

	MyException(const MyException & e)
	{
		cout << "MyException拷贝构造函数调用" << endl;
	}

	~MyException()
	{
		cout << "MyException的析构函数调用" << endl;
	}
};

void doWork()
{
	throw  MyException();
}

void test01()
{
	try
	{
		doWork();
	}
	//MyException e会调用拷贝构造
	//MyException &e 引用方式 接受  建议用这种方式  节省开销
	//MyException *e 指针方式 接受 抛出  &MyException();匿名对象，对象被释放掉，不可以再操作e了
	//MyException *e 指针方式 接受 抛出 new  MyException(); 堆区创建的对象  记得手动释放 delete e;
	catch (MyException &e)
	{
		cout << "MyException的异常捕获" << endl;

	}
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}