#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1����̬����ת��
void test01()
{
	//������������
	char a = 'a';

	//static_cast<Ŀ������>(ԭ����)
	double d = static_cast<double>(a);

	cout << d << endl;
}

class Base
{
	virtual void func(){};
};
class Son :public Base
{
	virtual void func(){};
};
class Other
{};
void test02()
{
	//�Զ�����������
	Base * base = NULL;
	Son * son = NULL;


	//base תΪ Son*����    ��������ת��  ����ȫ
	Son * son2 = static_cast<Son *>(base);

	//son תΪ  Base * ����      ��������ת��   ��ȫ
	Base* base2 = static_cast<Base*>(son);

	//base תΪ Other*
	//û�и��ӹ�ϵ����������֮�����޷�ת���ɹ���
	//Other * other = static_cast<Other *>(base);

}

//2����̬����ת��
void test03()
{
	//������������ ������������������֮���ת��
	//char c = 'c';
	//double d = dynamic_cast<double>(c);

	
	//�Զ�����������
	Base * base = NULL;
	Son * son = NULL;

	//base תΪ Son* ����  ����ȫ  
	//����ȫ ת��ʧ��
	//Son * son2 = dynamic_cast<Son*>(base);

	//son תΪ  Base*   ��ȫ
	Base * base2 = dynamic_cast<Base*>(son);

	//base תΪOther* 
	//Other* other = dynamic_cast<Other*>(base);

	//���������̬����ô����֮���ת�� ���ǰ�ȫ��
	Base * base3 = new Son;
	//�� base3תΪ  Son*
	Son * son3 = dynamic_cast<Son*>(base3);


}


//3������ת��
void test04()
{
	//ָ��֮���ת��
	const int * p = NULL;
	//�� const int * תΪ int *
	int * p2 = const_cast<int *>(p);

	//�� p2 תΪ  const int * 
	const int * p3 = const_cast<const int *>(p2);


	//����֮���ת��
	const int a = 10;
	const int & aRef = a;

	int & aRef2 = const_cast<int &>(aRef);

	//�����ԶԷ�ָ�� ���� ������ ��const_castת��
	//int b = const_cast<int>(a);
}

//4�����½���ת��  ���ȫ ��������
void tet05()
{
	//int a = 10;
	//int * p = reinterpret_cast<int*>(a);

	//��base* תΪ Other * 
	Base * base = NULL;

	Other * other = reinterpret_cast<Other *>(base);
}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}