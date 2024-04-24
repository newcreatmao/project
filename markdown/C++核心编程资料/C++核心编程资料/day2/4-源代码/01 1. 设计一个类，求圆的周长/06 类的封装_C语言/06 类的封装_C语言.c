#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Person
{
	char m_Name[64];
	int m_Age;
	
};

void PersonEat(struct Person * p)
{
	printf("%s在吃人饭\n",p->m_Name);
}


void test01()
{
	struct Person p1;
	strcpy(p1.m_Name, "老王");

	PersonEat(&p1);

}



struct Dog
{
	char m_Name[64];
	int m_Age;
};

void DogEat(struct Dog * d)
{
	printf("%s在吃狗粮\n", d->m_Name);
}

void test02()
{
	struct Dog d;
	strcpy(d.m_Name, "旺财");

	DogEat(&d);

	struct Person p;
	strcpy(p.m_Name, "老王");
	DogEat(&p);

}


int main(){

	//test01();
	test02();


	system("pause");
	return EXIT_SUCCESS;
}