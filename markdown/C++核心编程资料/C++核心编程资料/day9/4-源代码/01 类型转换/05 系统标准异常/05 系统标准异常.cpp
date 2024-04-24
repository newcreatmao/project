#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//使用系统标准依然 需要引用一个头文件   
#include <stdexcept> //系统标准异常头文件

class Person
{
public:

	Person(int age)
	{
		if (age < 0 || age > 150)
		{
			//年龄越界异常抛出
			//throw out_of_range("年龄必须在 0 到 150之间！");
			throw length_error("年龄必须在 0 到 150之间！");
		}
		this->m_Age = age;
	}

	int m_Age;
};

void test01()
{
	try
	{
		Person p1(151);
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