#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>

//1����const���εı���ȡ��ַʱ�򣬻������ʱ�ڴ�
void test01()
{
	const int m_A = 10;
	int * p = (int*)&m_A;
}

//2��constǰ���� extern�ؼ��ֺ�Ҳ������ڴ�

//3��ʹ�ñ�������ʼ��const���εı���
void test02()
{
	int a = 10;
	const int m_A = a;

	int *p = (int *) &m_A;

	*p = 20;
	cout << m_A << endl;

}

//4�������Զ����������� ��Ҳ������ڴ�
struct Person
{
	string name;
	int age;
};
void test03()
{
	const Person p;
	//������ֱ���޸�
	//p.age = 100;
	//p.name = "aaa";

	Person * pp = (Person *)&p;

	pp->name = "aaa";
	pp->age = 10;

	cout << "������ " << pp->name << " ���䣺 " << pp->age << endl;


}



int main(){
	//test02();
	test03();

	system("pause");
	return EXIT_SUCCESS;
}