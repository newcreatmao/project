#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyString
{
public:
	MyString(char * str)
	{
	
	}
	//explicit 关键字用途 ：防止隐式类型转换方式来初始化对象
	explicit MyString(int len)
	{
		m_Len = len;
	}

	int m_Len;
	char * m_Str;
};


void test01()
{
	MyString str = "abc";

	//MyString str2 = 10; //有的用户认为  字符串长度是10  ， 有的用户认为  字符串为10

	MyString str3(10);

	MyString str4 = MyString(10);

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}