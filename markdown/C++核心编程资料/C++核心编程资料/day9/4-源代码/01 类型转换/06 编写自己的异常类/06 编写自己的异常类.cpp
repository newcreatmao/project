#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

//�Լ����쳣��
class myOutOfRange :public exception
{
public:

	myOutOfRange(char * errorInfo)
	{
		//��char * תΪ string
		this->m_ErrorInfo = string(errorInfo);
	}

	myOutOfRange(string errorInfo)
	{
		this->m_ErrorInfo = errorInfo;
	}

	virtual  ~myOutOfRange()
	{
	}
	const char *  what() const
	{
		//string תΪ const char *
		//.c_str();
		return this->m_ErrorInfo.c_str();
	}

	//����ס �û�������쳣��Ϣ�� �ַ���
	string m_ErrorInfo;

};

class Person
{
public:

	Person(int age)
	{
		if (age < 0 || age > 150)
		{
			//����Խ���쳣�׳�
			throw myOutOfRange(  "�ҵ��쳣�� ---- ��������� 0 �� 150 ֮��");
		}
		this->m_Age = age;
	}

	int m_Age;
};

void test01()
{
	try
	{
		Person p1(1111);
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