#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include <string>
class Printer
{
public:
	static Printer * getInstance()
	{
		return printer;
	}

	//��ӡ����
	void printText(string text)
	{
		cout << "��ӡ�����ݣ� " << text << endl;
		m_Count++;
	}
	int m_Count; //��ӡ��ʹ�ô���

private:
	Printer()
	{
		m_Count = 0;
	}

	Printer(const Printer & p)
	{
	
	}

	static Printer *  printer;

	

};

Printer *  Printer::printer = new Printer;


void test01()
{
	Printer * p1 = Printer::getInstance();
	p1->printText("��ְ����");
	p1->printText("��ְ����");
	p1->printText("��������");
	p1->printText("�������");

	cout << "��ӡ��ʹ�ô��� : " << p1->m_Count << endl;

	Printer * p2 = Printer::getInstance();
	p2->printText("��������");

	cout << "��ӡ��ʹ�ô��� : " << p1->m_Count << endl;
}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}