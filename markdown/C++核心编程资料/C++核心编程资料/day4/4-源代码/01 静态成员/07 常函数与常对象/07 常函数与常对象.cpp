#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;


class Person
{
public:

	// ������
	// ��Ա������������ �� const  �����������������޸ĳ�Ա������
	void showPerson() const
	{
		// const  Person * const  this
		// thisָ��ı���  ��һ��ָ�볣����ָ���ָ���ǲ������޸ĵģ�ָ��ָ���ֵ���Ը�
		cout << this->m_A << endl;
		
		//this = NULL;
		// this->m_A = 100; 

		this->m_B = 100;
	}

	void showPerson2()
	{
		this->m_A = 100;
		cout << "aaa" << endl;
	}

	int m_A;
	mutable int m_B; //��ʹ�ǳ�������m_B��Ҳ������޸�
};

void test01()
{
	Person p1;
	p1.m_A = 10;
	p1.showPerson();

}


//������
void test02()
{
	const Person p1; //������
	//������Ҳ�������޸��ڲ�������
	//p1.m_A = 100;

	p1.m_B = 100; //m_B���������ԣ���ʹ�ĳ����� ���߳����� ���ǿ��Ը�


	p1.showPerson();  //������ ֻ�ܵ���  ������
	//p1.showPerson2(); //������ �ǲ����Ե�����ͨ�ĳ�Ա������

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}