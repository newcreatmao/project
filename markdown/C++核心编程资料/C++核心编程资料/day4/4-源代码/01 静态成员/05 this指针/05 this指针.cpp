#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person(int age)
	{
		//thisָ��ָ����Ǳ����õĳ�Ա���������Ķ���
		this->age = age;
	}

	void showAge()
	{
		cout << "���䣺" << this->age << endl;
	}

	Person &  AddAge( Person & p)
	{
		this->age += p.age;
		return *this;
	}

	int age;
};

void test01()
{
	Person p1(18);

	//cout << "p1������Ϊ��" << p1.age << endl;
	p1.showAge();


	Person p2(10);

	p1.AddAge(p2).AddAge(p2).AddAge(p2); //��ʽ���

	p1.showAge();

}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}