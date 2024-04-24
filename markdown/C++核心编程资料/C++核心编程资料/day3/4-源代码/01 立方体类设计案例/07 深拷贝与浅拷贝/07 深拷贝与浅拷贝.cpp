#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:

	Person(char * name, int age)
	{
		cout << "Person的有参构造函数调用" << endl;
		m_Name =  (char *)malloc(strlen(name) + 1);
		strcpy(m_Name, name);

		m_Age = age;
	}

	Person(const Person & p)
	{
		m_Age = p.m_Age;

		//m_Name = p.m_Name; 系统提供的浅拷贝

		//利用深拷贝 解决浅拷贝带来的问题
		m_Name =(char *) malloc(strlen(p.m_Name) + 1);
		strcpy(m_Name, p.m_Name);
	
	}

	~Person()
	{
		if (m_Name != NULL)
		{
			cout << "Person的析构函数调用" << endl;
			free(m_Name);
			m_Name = NULL;
		}
	}

	char * m_Name; //姓名
	int m_Age; //年龄
};

void test01()
{
	Person p1("Tom",18);

	cout << "p1的姓名： " << p1.m_Name << " 年龄： " << p1.m_Age << endl;



	Person p2(p1);

	cout << "p2的姓名： " << p2.m_Name << " 年龄： " << p2.m_Age << endl;




}


int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}