#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class Base
{
public:
	int m_A;
protected:
	int m_B;
private:
	int m_C;
};

class Son :public Base
{
public:
	//������˽�����ԣ�����̳��ˣ����Ǳ����������أ���˷��ʲ���
	int m_D;
};

void test01()
{
	cout << sizeof(Son) << endl; // 16 ��4 �� 12  
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}