#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
//
//class calculator
//{
//public:
//	int getResult(string oper)
//	{
//		if (oper == "+")
//		{
//			return m_A + m_B;
//		}
//		else if (oper == "-")
//		{
//			return m_A - m_B;
//		}
//		else if (oper == "*")
//		{
//			return m_A * m_B;
//		}
//
//	}
//
//	int m_A;
//	int m_B;
//
//};

//�����и�ԭ�� ---  ����ԭ�� 
// ����ԭ��  --- ����չ���п��� ���޸Ľ��йر�


//���ö�̬ʵ�ּ�����

class AbstractCalculator
{
public:

	//���麯��
	virtual int getResult() = 0;
	//���һ�������д��麯�����֣���ô�������޷�ʵ����������
	//�д��麯�����࣬Ҳ��Ϊ  ������


	//virtual int getResult()
	//{
	//	return  0;
	//}
	int m_A;
	int m_B;
};

//�������̳��˳����࣬��ô�������Ҫ��д�����еĴ��麯������������Ҳ���ڳ�����
//class A :public AbstractCalculator
//{
//public:
//	virtual int getResult()
//	{
//		return 0;
//	}
//};

//�ӷ�������
class AddCalculator: public AbstractCalculator
{
public:
	virtual int getResult()
	{
		return  m_A + m_B;
	}
};


//����������
class SubCalculator :public AbstractCalculator
{
public:
	virtual int getResult()
	{
		return  m_A - m_B;
	}
};

//�˷�������
class MultiCalculator :public AbstractCalculator
{
public:
	virtual int getResult()
	{
		return  m_A * m_B;
	}
};



void test01()
{
	//�ӷ�������
	AbstractCalculator * calculator = new AddCalculator;
	calculator->m_A = 10;
	calculator->m_B = 20;

	cout << calculator->getResult() << endl;

	delete calculator;

	//��Ϊ����������
	calculator = new SubCalculator;
	calculator->m_A = 10;
	calculator->m_B = 20;

	cout << calculator->getResult() << endl;
}

//��̬�ĺô���  ����չ����ߣ���֯��ǿ���ɶ���ǿ
//��������������麯�������ಢû����д������麯������ô�����Ĵ����Ǻ��������
//������಻��д�����麯������ôû���õ���̬�����ĺô� �������ڲ��ṹ����ø�Ϊ����

int main(){


	test01();


	system("pause");
	return EXIT_SUCCESS;
}