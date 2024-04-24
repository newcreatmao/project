#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:

	void showClassName()
	{
		cout << "class Name is Person" << endl;
	}

	void showAge()
	{
		// NULL->m_Age;
		if (this == NULL)
		{
			return;
		}
		cout << "age = " << this->m_Age << endl;
	}

	int m_Age = 10;
};

void test01()
{
	/*Person p1;
	p1.m_Age = 18;

	p1.showAge();
	p1.showClassName();*/


	Person * p1 = NULL;
	p1->showAge();
	//p1->showClassName();

}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}