#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyString
{
public:
	MyString(char * str)
	{
	
	}
	//explicit �ؼ�����; ����ֹ��ʽ����ת����ʽ����ʼ������
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

	//MyString str2 = 10; //�е��û���Ϊ  �ַ���������10  �� �е��û���Ϊ  �ַ���Ϊ10

	MyString str3(10);

	MyString str4 = MyString(10);

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}