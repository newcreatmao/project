#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

struct Person
{
	int age;
};

void allocateSpace( Person ** p ) // **p ָ��person����   *p ָ��  p ָ���ָ��
{
	*p = ( Person * )malloc(sizeof(Person));

	(*p)->age = 100;
}

void test01()
{
	Person * p = NULL;
	allocateSpace(&p);

	cout << "���䣺" << p->age << endl;
}



//2��ָ�������
void allocateSpace2(Person* &p) // Person * &p = p
{
	 p = (Person *)malloc(sizeof(Person));

	 p->age = 200;
}

void test02()
{
	Person * p = NULL;
	allocateSpace2(p);

	cout << "���䣺" << p->age << endl;
}


int main(){
//	test01();

	test02();


	system("pause");
	return EXIT_SUCCESS;
}