#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//1��ȫ�ֱ��������ǿ
int a;
int a = 10;

//2�����������ǿ  
int getRectS( w,  h)
{
	//return w * h;
}

void test02()
{
	getRectS(10, 10,10);
}

//3������ת�������ǿ
void test03()
{
	char * p =  malloc(64);

}


//4��struct ��ǿ
struct Person
{
	int age;
	//void func(); C������ �ṹ���в����Էź���
};
void test04()
{
	struct Person p1; // C������ �����ṹ��ʱ�� �����struct�ؼ���
	p1.age = 17;
}


//5��bool������ǿ C������ û��bool����
//bool flag;


//6����Ŀ�������ǿ
void  test06()
{
	int a = 10;
	int b = 20;

	printf("ret = %d\n", a > b ? a : b);

	*(a > b ? &a : &b )= 100;  // C������ ��Ŀ��������ص���ֵ 20 = 100


	printf("a = %d\n", a);
	printf("b = %d\n", b);
}

//7��const��ǿ
const int m_A = 100; //ȫ��const���α��� �ܵ���������������ʹ�﷨ͨ�������н׶λᱨ��
void test07()
{
	//m_A = 200;
	//int * p = &m_A;
	//*p = 200;

	const int m_B = 100; //�ֲ�const���εı������Լ���޸ĳɹ�
	//m_B = 200;

	int * p2 = &m_B;
	*p2 = 200;

	printf("m_B = %d\n", m_B);

	//int arr[m_B]; //�����Գ�ʼ������

}


int main(){

	//test06();
	test07();

	system("pause");
	return EXIT_SUCCESS;
}