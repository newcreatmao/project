#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyException
{
public:
	MyException()
	{
		cout << "MyException���캯������" << endl;
	}

	MyException(const MyException & e)
	{
		cout << "MyException�������캯������" << endl;
	}

	~MyException()
	{
		cout << "MyException��������������" << endl;
	}
};

void doWork()
{
	throw  MyException();
}

void test01()
{
	try
	{
		doWork();
	}
	//MyException e����ÿ�������
	//MyException &e ���÷�ʽ ����  ���������ַ�ʽ  ��ʡ����
	//MyException *e ָ�뷽ʽ ���� �׳�  &MyException();�������󣬶����ͷŵ����������ٲ���e��
	//MyException *e ָ�뷽ʽ ���� �׳� new  MyException(); ���������Ķ���  �ǵ��ֶ��ͷ� delete e;
	catch (MyException &e)
	{
		cout << "MyException���쳣����" << endl;

	}
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}