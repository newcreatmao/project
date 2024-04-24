#pragma  once 
#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class MyString
{
	//左移运算符 配合友元
	friend ostream& operator<<(ostream& cout, MyString &str);

	//右移运算符 配合友元
	friend istream&  operator>>(istream & cin, MyString &str);
public:

	//有参构造函数
	MyString(char * str);

	//拷贝构造
	MyString(const MyString & str);

	// 用户使用方式：  MyString str = "aaa";   MyString str2 (str);

	//重载[]运算符
	char& operator[] (int index);

	//重载 = 运算符
	MyString&  operator=(char * str);

	MyString&  operator=(MyString & str);

	//重载 + 运算符 实现字符串拼接
	MyString operator+(char * str);

	MyString operator+(MyString & str);

	//重载 == 运算符
	bool operator== (char * str);
	bool operator== (MyString & str);


	//析构函数
	~MyString();

private:

	//指向堆区字符串指针
	char * pString; 

	//字符串长度
	int m_Size;
};