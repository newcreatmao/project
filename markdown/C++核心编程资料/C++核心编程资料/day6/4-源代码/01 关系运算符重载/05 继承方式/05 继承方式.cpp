#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//�����̳�
class Base1
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son1 : public Base1
{
public:

	void func()
	{
		m_A = 100;  // m_A��Son1���� public Ȩ��
		m_B = 100;  // m_B��Son1���� protected Ȩ��
		//m_C = 100; // �����е�˽������ ����Ҳ���ʲ���
	}
};
void test01()
{
	Son1 s;
	s.m_A = 100; // m_A ��Son1����publicȨ�ޣ������������
}


// ------------------------  �����̳�  ------------------------

class Base2
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son2 : protected Base2
{
public:

	void func()
	{
		m_A = 100; //m_A��Son2���е�Ȩ��Ϊ protected 
		m_B = 100; //m_B��Son2���е�Ȩ��Ϊ protected
		//m_C = 100; //�����е�˽������ ����Ҳ���ʲ���
	}
};

void test02()
{
	Son2 s;
	//s.m_A = 100; //m_A��Son2�е�Ȩ�� ��protected �����ⲻ���Է���
}

// ------------------------  ˽�м̳�  ------------------------
class Base3
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};
class Son3 :private Base3
{
public:
	void func()
	{
		m_A = 100; //m_A��Son3���е�Ȩ��Ϊ private 
		m_B = 100; //m_B��Son3���е�Ȩ��Ϊ private 
		//m_C = 100; //�����е�˽������ ����Ҳ���ʲ���
	}
};
class GrandSon3 :public Son3
{
public:
	void func()
	{
		//m_A = 100; m_A��Son3���Ѿ���Ϊ privateȨ�ޣ���˷��ʲ���
	}
};
void test03()
{
	Son3 s;
	//3�����Զ����ʲ���
	//s.m_A = 100;
	//s.m_B = 100;
	//s.m_C = 100;

}


int main(){



	system("pause");
	return EXIT_SUCCESS;
}