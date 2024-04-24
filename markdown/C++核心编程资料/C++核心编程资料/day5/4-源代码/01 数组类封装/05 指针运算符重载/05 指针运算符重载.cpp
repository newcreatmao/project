#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person(int age )
	{
		cout << "�вι��캯��" << endl;
		this->m_Age = age;
	}

	void showAge()
	{
		cout << "����Ϊ�� " << this->m_Age << endl;
	}

	~Person()
	{
		cout << "������������" << endl;
	}

private:
	int m_Age;//����
};

//����ָ��  �����й�new�����Ķ�����ͷ�
class SmartPointer
{
public:
	SmartPointer(Person * person)
	{
		cout << "SmartPointer���캯������" << endl;
		this->person = person;
	}

	//����ָ������� 
	Person * operator->()
	{
		return this->person;
	}

	//����*�����
	Person& operator*()
	{
		return *this->person;
	}

	~SmartPointer()
	{
		if (this->person != NULL)
		{
			cout << "SmartPointer������������" << endl;
			delete this->person;
			this->person = NULL;
		}
	}


private:
	Person * person;
};


void test01()
{
	 Person * p = new Person(18);
	 //p->showAge();
	 //(*p).showAge();

	 //delete p;

	SmartPointer sp = SmartPointer(new Person(18));
	sp->showAge(); // sp->->showAge(); ��������Ϊ sp->showAge();
	(*sp).showAge();
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}