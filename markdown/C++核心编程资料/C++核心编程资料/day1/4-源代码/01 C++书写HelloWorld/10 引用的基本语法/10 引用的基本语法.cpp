#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//���� �� ��һ���ڴ�ռ�  �����
//�﷨ �� Type &���� = ԭ��
void test01()
{
	int a = 10;

	int &b = a;

	b = 20;

	cout << "a = " << a << endl;

}

//���ñ���Ҫ��ʼ��
void test02()
{
	int a = 10;
	int &b = a;

	//һ����ʼ����  �Ͳ������޸�ָ����
	int c = 20;
	b = c; //��ֵ

	cout << "a = " << a<<endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
}

//���������������
void test03()
{
	int arr[10];

	int(&pArr)[10] = arr;

	for (int i = 0; i < 10;i++)
	{
		arr[i] = i;
	}

	//for (int i = 0; i < 10;i++)
	//{
	//	cout << pArr[i] << endl;
	//}

	//�ȶ������������ͣ��ٶ�������
	typedef int(ARRAY_TYPE)[10];
	//�﷨ �� Type &���� = ԭ��
	ARRAY_TYPE &pArr2 = arr;
	for (int i = 0; i < 10; i++)
	{
		cout << pArr2[i] << endl;
	}

}


int main(){

	//test01();
	//test02();
	test03();
	system("pause");
	return EXIT_SUCCESS;
}