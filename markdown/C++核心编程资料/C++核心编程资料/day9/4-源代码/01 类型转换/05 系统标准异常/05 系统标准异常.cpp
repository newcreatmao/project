#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//ʹ��ϵͳ��׼��Ȼ ��Ҫ����һ��ͷ�ļ�   
#include <stdexcept> //ϵͳ��׼�쳣ͷ�ļ�

class Person
{
public:

	Person(int age)
	{
		if (age < 0 || age > 150)
		{
			//����Խ���쳣�׳�
			//throw out_of_range("��������� 0 �� 150֮�䣡");
			throw length_error("��������� 0 �� 150֮�䣡");
		}
		this->m_Age = age;
	}

	int m_Age;
};

void test01()
{
	try
	{
		Person p1(151);
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