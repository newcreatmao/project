#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyInter
{
	friend ostream & operator<<(ostream & cout, MyInter & myInt);
public:
	MyInter()
	{
		this->m_Num = 0;
	}

	//重载前置++
	MyInter & operator++()
	{
		//先++
		m_Num++;

		//后返回
		return *this;
	}


	//重载后置++
	MyInter  operator++(int)
	{
		//先 返回
		MyInter temp = *this;

		//后 ++
		this->m_Num++;

		return temp;
	}

private:
	int m_Num;

};

//重载左移运算符
ostream & operator<<(ostream & cout, MyInter & myInt)
{
	cout << myInt.m_Num;
	return cout;
}


//前置
void test01()
{
	MyInter myInt;

	cout << ++(++myInt) << endl;

	cout << myInt << endl;
}

//后置
void test02()
{
	MyInter myInt;

	cout << myInt++ << endl; // 0

	cout << myInt << endl; // 1
}

int main(){

	//test01();
	test02();

	//int a = 0;
	//cout << ++(++a) << endl;
	//cout << a << endl;

	

	system("pause");
	return EXIT_SUCCESS;
}