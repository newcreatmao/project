#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1��������Ĭ�ϲ���

int func(int a = 1 , int b = 1)
{
	return a + b;

}

void test01()
{
	cout << func(10) << endl;

}

//2��ע������
// ��������б��� ��һλ������Ĭ�ϲ�������ô�����λ��������Ҷ�������Ĭ�ϲ���
int func2(int a = 1 , int b = 1 , int c = 1 )
{
	return a + b + c;

}

void test02()
{
	cout << func2(10) << endl;

}

//������������ʵ�� ֻ����һ����Ĭ�ϲ���
int func3(int a = 100, int b = 200);
int func3(int a , int b){ return a + b; };

void test03()
{
	cout << func3() << endl;;
}




//3��������ռλ����
//ռλ���� ��;�� Ŀǰû�У�����ѧϰ��������ʱ����õ�һ���
int func4(int a , int = 10  )
{
	return a;	
}
void test04()
{
	func4(1);
}



int main(){
	//test01();
	//test02();
	test03();


	system("pause");
	return EXIT_SUCCESS;
}