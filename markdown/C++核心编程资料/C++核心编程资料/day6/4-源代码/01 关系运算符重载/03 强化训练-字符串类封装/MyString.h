#pragma  once 
#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

class MyString
{
	//��������� �����Ԫ
	friend ostream& operator<<(ostream& cout, MyString &str);

	//��������� �����Ԫ
	friend istream&  operator>>(istream & cin, MyString &str);
public:

	//�вι��캯��
	MyString(char * str);

	//��������
	MyString(const MyString & str);

	// �û�ʹ�÷�ʽ��  MyString str = "aaa";   MyString str2 (str);

	//����[]�����
	char& operator[] (int index);

	//���� = �����
	MyString&  operator=(char * str);

	MyString&  operator=(MyString & str);

	//���� + ����� ʵ���ַ���ƴ��
	MyString operator+(char * str);

	MyString operator+(MyString & str);

	//���� == �����
	bool operator== (char * str);
	bool operator== (MyString & str);


	//��������
	~MyString();

private:

	//ָ������ַ���ָ��
	char * pString; 

	//�ַ�������
	int m_Size;
};