#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyClass
{
public:

	//1�����캯����д��
	//û�з���ֵ   Ҳ��дvoid  ��������������ͬ
	//�����в��� �����Է�������
	//�ɱ������Զ����ã�����Ҫ�ֶ����ã����ұ�����ֻ�����һ��

	MyClass()
	{
		cout << "MyClass�Ĺ��캯������" << endl;
	}


	MyClass(int a)
	{
		cout << "MyClass��int a���Ĺ��캯������" << endl;
	}

	//2������������д��
	//û�з���ֵ  ��дvoid  ��������������ͬ   �ں�������ǰ��~
	//�������в��� �������Է�������
	//�ɱ������Զ����ã�����Ҫ�ֶ����ã�������Ҳֻ����һ��

	~MyClass()
	{
		cout << "MyClass�����������ĵ���" << endl;
	}


};

void test01()
{
	MyClass myclass;

}

int main(){

	test01();

	

	system("pause");
	return EXIT_SUCCESS;
}