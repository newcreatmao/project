#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Person
{
public:
	Person()
	{
		cout << "Ĭ�Ϲ��캯������" << endl;
	}

	Person(int a)
	{
		m_Age = a;
		cout << "�вι��캯������" << endl;
	}

	Person(const  Person & p)
	{
		m_Age = p.m_Age;
		cout << "�������캯������" << endl;
	}

	~Person()
	{
		cout << "������������" << endl;
	}

	int m_Age;
};

//1��malloc �� new ����
// new delete ��һ�������   malloc  free ��һ���⺯��
// malloc ����ֵ void *   new ���ص���new�����Ķ����ָ��
// malloc ��Ҫ�ж��Ƿ񿪱ٳɹ� ��new�ڲ������˲���(�ڲ���malloc�����ڶ������ж��ڴ��Ƿ����ɣ����ù��캯��)
// malloc ������ù��캯��   �� new���ù��캯��   
// malloc ��Ӧ���ͷ��� free      new ��Ӧ���ͷ���  delete
void test01()
{

	
	//Person p1; //����ջ��

	//���ٵ�����
	Person * p1 = new Person;
	Person * p2 = new Person(10);
	Person * p3 = new Person(*p2);

	//�ͷ�new�����Ķ���
	delete p1;
	delete p2;
	delete p3;
}

//2��ע������
void test02()
{
	//��Ҫ��void * ȥ����new�����Ķ���ԭ���ǲ��ܹ��ͷ�
	void * p = new Person;
	delete (Person * )p;
}

//3������new��������
void test03()
{
  //int* pInt =	new int[10];
  //char * pChar = new char[64];

	//����new �ڶ����������飬���б���Ҫ����Ĭ�Ϲ��캯���������޷�����
	Person * persons = new Person[10];

	//�����������ջ�Ͽ��ٵģ���ô����ָ�������ĸ����캯������ʼ������
	//Person persons2[3] = { Person(10), Person(10), Person(10) };

	//��������� �ͷ�ʱ��Ҫ�� delete��� []
	delete [] persons;

}

int main(){

	//test01();
	//test02();
	test03();


	system("pause");
	return EXIT_SUCCESS;
}