#include "MyString.h"

//���� << �����
ostream& operator<<( ostream& cout , MyString &str)
{
	cout << str.pString;
	return cout;
}

//���� >> �����
istream&  operator>>(istream & cin, MyString &str)
{
	//���ж�str��ԭ���Ƿ������ݣ������ �Ƚ����ͷ�
	if (str.pString != NULL)
	{
		delete[] str.pString;
		str.pString = NULL;
	}


	char buf[1024]; //������

	cin >> buf; //���û���������� �ȴ�ŵ� buf��

	//��buf�е����ݷ��뵽���ڲ�ά���� pString��
	str.pString = new char[strlen(buf) + 1];
	strcpy(str.pString, buf);
	str.m_Size = strlen(buf);

	return cin;
}


MyString::MyString(char * str)
{
	this->pString = new char[strlen(str) + 1];
	strcpy(this->pString, str);

	this->m_Size = strlen(str);

}

MyString::MyString(const MyString & str)
{
	this->pString = new char[strlen(str.pString) + 1];
	strcpy(this->pString, str.pString);

	this->m_Size = strlen(str.pString);

}

char& MyString::operator[](int index)
{
	return this->pString[index];
}

MyString& MyString::operator=(char * str)
{
	//���ж�ԭ���Ƿ������ݣ���������ͷ�
	if (this->pString != NULL)
	{
		delete[] this->pString;
		this->pString = NULL;
	}

	this->pString = new char[strlen(str) + 1];
	strcpy(this->pString, str);
	this->m_Size = strlen(str);

	return *this;
}

MyString& MyString::operator=(MyString & str)
{
	//���ж�ԭ���Ƿ������ݣ���������ͷ�
	if (this->pString != NULL)
	{
		delete[] this->pString;
		this->pString = NULL;
	}

	this->pString = new char[strlen(str.pString) + 1];
	strcpy(this->pString, str.pString);
	this->m_Size = strlen(str.pString);

	return *this;
}

MyString MyString::operator+(char * str)
{
	//��ǰ�ַ���  �� abc
	// str  �� def
	int newSize = this->m_Size + strlen(str) + 1;

	char * temp = new char[newSize]; //���ٵĿռ�

	//�� abc  �� def  ���뵽 temp�ռ���
	memset(temp, 0, newSize);
	strcat(temp, this->pString);
	strcat(temp, str);
	MyString newString(temp);
	delete [] temp;
	return newString;
}

MyString MyString::operator+(MyString & str)
{
	int newSize = this->m_Size + strlen(str.pString) + 1;

	char * temp = new char[newSize]; //���ٵĿռ�

	//�� abc  �� def  ���뵽 temp�ռ���
	memset(temp, 0, newSize);
	strcat(temp, this->pString);
	strcat(temp, str.pString);
	MyString newString(temp);
	delete[] temp;
	return newString;
}

bool MyString::operator==(char * str)
{
	if (  strcmp( this->pString,str) == 0 )
	{
		return true;
	}
	return false;
}

bool MyString::operator==(MyString & str)
{
	if (strcmp(this->pString, str.pString) == 0)
	{
		return true;
	}
	return false;
}

MyString::~MyString()
{
	if (this->pString != NULL)
	{
		delete [] this->pString;
		this->pString = NULL;
	}
}
