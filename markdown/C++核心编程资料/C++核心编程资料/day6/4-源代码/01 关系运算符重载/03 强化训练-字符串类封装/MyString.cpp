#include "MyString.h"

//重载 << 运算符
ostream& operator<<( ostream& cout , MyString &str)
{
	cout << str.pString;
	return cout;
}

//重载 >> 运算符
istream&  operator>>(istream & cin, MyString &str)
{
	//先判断str中原来是否有数据，如果有 先进行释放
	if (str.pString != NULL)
	{
		delete[] str.pString;
		str.pString = NULL;
	}


	char buf[1024]; //缓冲区

	cin >> buf; //将用户输入的数据 先存放到 buf中

	//将buf中的数据放入到我内部维护的 pString中
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
	//先判断原来是否有数据，如果有先释放
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
	//先判断原来是否有数据，如果有先释放
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
	//当前字符串  是 abc
	// str  是 def
	int newSize = this->m_Size + strlen(str) + 1;

	char * temp = new char[newSize]; //开辟的空间

	//将 abc  和 def  放入到 temp空间下
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

	char * temp = new char[newSize]; //开辟的空间

	//将 abc  和 def  放入到 temp空间下
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
