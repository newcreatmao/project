#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

//自己的异常类
class myOutOfRange :public exception
{
public:

	myOutOfRange(char * errorInfo)
	{
		//将char * 转为 string
		this->m_ErrorInfo = string(errorInfo);
	}

	myOutOfRange(string errorInfo)
	{
		this->m_ErrorInfo = errorInfo;
	}

	virtual  ~myOutOfRange()
	{
	}
	const char *  what() const
	{
		//string 转为 const char *
		//.c_str();
		return this->m_ErrorInfo.c_str();
	}

	//保存住 用户传入的异常信息的 字符串
	string m_ErrorInfo;

};

class Person
{
public:

	Person(int age)
	{
		if (age < 0 || age > 150)
		{
			//年龄越界异常抛出
			throw myOutOfRange(  "我的异常类 ---- 年龄必须在 0 到 150 之间");
		}
		this->m_Age = age;
	}

	int m_Age;
};

void test01()
{
	try
	{
		Person p1(1111);
	}
	catch (exception & e)
	{
		cout << e.what() << endl;
	}


}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}