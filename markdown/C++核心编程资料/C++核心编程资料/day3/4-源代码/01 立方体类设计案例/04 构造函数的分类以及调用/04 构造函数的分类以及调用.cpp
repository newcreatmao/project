#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1������
//���ղ������з���  �вι��캯��    �޲ι��캯����Ĭ�Ϲ��캯����
//�������ͽ��з���  ��ͨ���캯��    �������캯��
class Person
{
public:
	//Ĭ�Ϲ���
	Person()
	{
		cout << "Person��Ĭ�Ϲ��캯������" << endl;
	}
	//�вι���
	Person(int age)
	{
		m_Age = age;
		cout << "Person���вι��캯������" << endl;
	}

	//��������
	Person( const Person &p ) // ����( const ����&  aa )
	{
		cout << "Person�Ŀ������캯������" << endl;
		m_Age = p.m_Age;
	}

	//��������
	~Person()
	{
		cout << "Person������������" << endl;
	}

	int m_Age;

};


//2������
void test01()
{
	////�޲ι��캯��
	//Person p1;

	////�вι��캯��
	////���ŷ�
	//Person p2(10); //�вι������
	//Person p3(p2);  //�������캯������

	//cout << "p3������: " << p3.m_Age << endl;

	////��ʾ��
	//Person p4 = Person(10); //�вι��캯��
	//Person p5 = Person(p4); //�������캯������


	//ע��� 
	//Person p(); //�����������ŷ� �����޲ι��캯�� ԭ��Person p();��������Ϊ��һ������������

	//Person(10); //������������ �ص㣺��ǰ��ִ�����ϵͳ�ͻ���

	//Person(p5); //�����Ե��ÿ������캯�� ����ʼ�������������� Person(p5); ��������Ϊ����Ϊ Person p5;  


	//��ʽ��
	Person p6 = 10; // Person p6 = 10; �ȼ���д��  Person p6 = Person(10)
	Person p7 = p6;

}


int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}