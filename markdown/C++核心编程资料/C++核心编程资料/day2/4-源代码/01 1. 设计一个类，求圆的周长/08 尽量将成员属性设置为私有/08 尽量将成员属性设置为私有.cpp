#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
class Person
{
public:

	//��������
	void setName(string name)
	{
		m_Name = name;
	}
	//��ȡ����
	string getName()
	{
		return m_Name;
	}

	//��ȡ����
	int getAge()
	{
		return m_Age;
	}

	//��������
	void setAge(int age)
	{
		if (age < 0 || age > 150)
		{
			m_Age = 0;
			cout << "�����������" << endl;
			return;
		}
		m_Age = age;
	}

	//��������
	void setLover(string lover)
	{
		m_Lover = lover;
	}

private:
	string m_Name; //�ɶ���д  ����
	int  m_Age ;  //�ɶ���д  ����
	string m_Lover; //ֻд  ����
};

//����Ա��������Ϊ˽�кô���  �Լ��������ԵĶ�дȨ��
//���û���������� ���м��


void test01()
{
	Person p1;
	//p1.m_Name;
	p1.setName("����");

	//��������
	p1.setLover("�־�");

	//��������
	p1.setAge(100);
	

	cout << "������ " << p1.getName() << endl;

	cout << "���䣺 " << p1.getAge() << endl;

	//cout << "���ˣ� " << p1.m_Lover;  ���˷��ʲ��� ��Ϊֻд״̬


}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}