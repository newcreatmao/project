#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#include "MyString.h"

void test01()
{
	MyString str = "aaa";

	cout << "str ��ǰ����Ϊ�� " << str << endl;

	cout << "���str�ַ����������¸�ֵ" << endl;

	cin >> str;

	cout << "str ��ǰ����Ϊ�� " << str << endl;


	//MyString str2(str);
	//cout << "str2 ��ǰ����Ϊ�� " << str2 << endl;

	cout << "str��һ����ĸΪ�� " << str[0] << endl;

	str[0] = 'w';

	cout << "str�޸ĵ�һ����ĸ�� =  " << str << endl;


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
		cout << "str �� str2 ���" << endl;
	}
	else
	{
		cout << "str �� str2 �����" << endl;
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