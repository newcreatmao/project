#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
	Base()
	{
		cout << "Base�Ĺ��캯������" << endl;
	}

	~Base()
	{
		cout << "Base��������������" << endl;
	}
};


//�̳��У��ȵ��ø���Ĺ��죬�ٵ�������Ĺ��죬������˳��͹���˳���෴��
class Son :public Base
{
public:
	Son()
	{
		cout << "Son�Ĺ��캯������" << endl;
	}

	~Son()
	{
		cout << "Son��������������" << endl;
	}

};

void test01()
{
	//Base b;

	Son s;
}


class Base2
{
public:
	Base2(int a)
	{
		this->m_A = a;
	}
	int m_A;
};
// �� ����̳�
class Son2 :public Base2
{
public:
	//�� ��ʼ���б�
	// �������ó�ʼ���б��﷨ ��ʾָ�������ø�����ĸ����캯��
	Son2(int a = 1000) : Base2(a)
	{
		
	}
	int m_B;
};

void test02()
{
	Son2 s(10);

}

//���಻��̳� �����еĹ��������������ֻ�и����Լ���֪���������������Լ�������

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}