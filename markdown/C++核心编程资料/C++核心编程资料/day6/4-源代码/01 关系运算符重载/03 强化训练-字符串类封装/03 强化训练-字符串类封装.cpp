#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#include "MyString.h"

void test01()
{
	MyString str = "aaa";

	cout << "str 当前内容为： " << str << endl;

	cout << "请给str字符串进行重新赋值" << endl;

	cin >> str;

	cout << "str 当前内容为： " << str << endl;


	//MyString str2(str);
	//cout << "str2 当前内容为： " << str2 << endl;

	cout << "str第一个字母为： " << str[0] << endl;

	str[0] = 'w';

	cout << "str修改第一个字母后 =  " << str << endl;


	MyString str2 = " ";

	str2 = str;


}

void test02()
{

	MyString str3 = "abc";
	MyString str4 = "def";
	MyString str = str3 + str4;

	MyString str2 = "abcdef";
	cout << "str = " << str << endl;


	if ( str == str2)
	{
		cout << "str 与 str2 相等" << endl;
	}
	else
	{
		cout << "str 与 str2 不相等" << endl;
	}

	

}

int main(){

	//test01();
	test02();
	/*int a = 0;
	cin >> a;
	cout << "a = " << a << endl;*/

	system("pause");
	return EXIT_SUCCESS;
}