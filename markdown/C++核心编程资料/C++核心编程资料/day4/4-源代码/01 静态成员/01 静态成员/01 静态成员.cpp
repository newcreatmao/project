#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:

	//��̬��Ա����
	//1�����ݹ���
	//2���ڱ���׶ξͷ������ڴ�
	//3��������������������г�ʼ��
	static int m_A;

	void func2() //�Ǿ�̬��Ա���� ���Է��ʾ�̬��Ա���� Ҳ���Է��� �Ǿ�̬��Ա����
	{
		m_C = 100;
		m_A = 1000;
	}

	static void func()
	{
		//m_C = 100; //��̬��Ա���� �ǲ����Է��ʷǾ�̬��Ա����
		m_A = 1000;  //��̬��Ա����  ���Է��� ��̬��Ա��������Ϊ���ǹ�������
		cout << "��̬��Ա��������" << endl;
	}

	int m_C;

private:
	static int m_B;//˽��Ȩ�޵����� ������ʲ���

	static void func3(){ cout << "aaa" << endl; };

};

int Person::m_A = 10; //��̬��Ա���� �����ʼ��

int Person::m_B = 20;

void test01()
{
	//���ʷ�ʽ
	//1��ͨ��������з���
	Person p1;
	cout <<"p1��m_A �� " <<  p1.m_A << endl;

	Person p2;
	p2.m_A = 20;
	cout << "p1��m_A �� " << p1.m_A << endl;
	cout << "p2��m_A �� " << p2.m_A << endl;

	//2��ͨ���������з���
	cout << "m_A :" << Person::m_A << endl;

	//��̬��Ա����Ҳ���з���Ȩ�޵�
	// Person::m_B = 100;  m_B��˽��Ȩ�� �����������ʲ���

}

void test02()
{
	//1��ͨ��������Խ��е���
	Person p1;
	p1.func();

	//2��ͨ���������е���
	Person::func();

	//Person::func3();//��̬��Ա����Ҳ���з���Ȩ�޵ģ�˽�е�Ȩ��������ʲ���

}



int main(){
	//test01();
	test02();

	system("pause");
	return EXIT_SUCCESS;
}