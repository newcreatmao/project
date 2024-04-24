#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

void test01()
{
	extern const int m_A;
	cout << "m_A = " << m_A << endl;
}

int main(){

	test01();

	system("pause");
	return EXIT_SUCCESS;
}