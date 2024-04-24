#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class MyInter
{
	friend ostream & operator<<(ostream & cout, MyInter & myInt);
public:
	MyInter()
	{
		this->m_Num = 0;
	}

	//����ǰ��++
	MyInter & operator++()
	{
		//��++
		m_Num++;

		//�󷵻�
		return *this;
	}


	//���غ���++
	MyInter  operator++(int)
	{
		//�� ����
		MyInter temp = *this;

		//�� ++
		this->m_Num++;

		return temp;
	}

private:
	int m_Num;

};

//�������������
ostream & operator<<(ostream & cout, MyInter & myInt)
{
	cout << myInt.m_Num;
	return cout;
}


//ǰ��
void test01()
{
	MyInter myInt;

	cout << ++(++myInt) << endl;

	cout << myInt << endl;
}

//����
void test02()
{
	MyInter myInt;

	cout << myInt++ << endl; // 0

	cout << myInt << endl; // 1
}

int main(){

	//test01();
	test02();

	//int a = 0;
	//cout << ++(++a) << endl;
	//cout << a << endl;

	

	system("pause");
	return EXIT_SUCCESS;
}