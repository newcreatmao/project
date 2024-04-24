#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void test01()
{
	extern const int m_a;
	printf("a = %d\n", m_a);

}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}