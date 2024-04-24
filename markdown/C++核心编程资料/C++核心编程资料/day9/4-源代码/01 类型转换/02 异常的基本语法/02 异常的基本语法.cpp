#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyException
{
public:
	void printError()
	{
		cout << "���Լ����쳣��Ĵ���" << endl;
	}
};

class Person
{
public:
	Person()
	{
		cout << "Person�Ĺ��캯��" << endl;
	}

	~Person()
	{
		cout << "Person����������" << endl;
	}

};

int myDivide(int a , int b)
{
	if ( b == 0)
	{
		//return -1; //C���Դ����쳣ȱ������  ���ص�ֵ û��ͳһ�����ص�ֵ�������쳣�Ľ����Ҳ��������ȷ�Ľ��

		//�׳��쳣
		//throw 1;
		//throw 3.14;
		//throw 'a';


		//ջ������ ��try����鿪ʼ�𣬵� throw�׳��쳣ǰ������ջ�ϵĶ��󶼱��ͷŵ���
		//	       �ͷŵ�˳��͹����˳�����෴�ģ�������̳�Ϊջ����
		Person p1;
		Person p2;
		

		throw MyException(); //�׳�һ�� MyException ��������
	}

	return a / b;

}

void test01()
{
	int a = 10;
	int b = 0;

	//����ִ��һ�� ���ܻ�����쳣�Ĵ���
	try
	{
		int ret = myDivide(a, b);
		cout << "ret ���Ϊ�� " << ret << endl;
	}
	catch (int ) //�����쳣
	{
		cout << "int���͵��쳣�Ĳ���" << endl;
	}
	catch (double) 
	{
		//����double�� ���봦������쳣������������׳�����쳣
		throw;
		cout << "double���͵��쳣�Ĳ���" << endl;
	}
	catch (MyException e)
	{
		e.printError();
	}
	catch (...)
	{
		cout << "���������쳣�Ĳ���" << endl;
	}

}


int main(){

	try
	{
		test01();
	}
	catch (int) //�쳣��������Ҫ�������û���κεĴ���������Զ�����һ��terminate�������ó����жϵ�
	{
		cout << "main�����е� int���͵��쳣�Ĳ���" << endl;
	}
	catch (...)
	{
		cout << "mian�����е� ���������쳣�Ĳ���" << endl;
	}

	system("pause");
	return EXIT_SUCCESS;
}