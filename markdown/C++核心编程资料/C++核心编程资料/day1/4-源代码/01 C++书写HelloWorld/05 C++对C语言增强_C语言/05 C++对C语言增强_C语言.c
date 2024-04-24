#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//1、全局变量检测增强
int a;
int a = 10;

//2、函数检测增强  
int getRectS( w,  h)
{
	//return w * h;
}

void test02()
{
	getRectS(10, 10,10);
}

//3、类型转换检测增强
void test03()
{
	char * p =  malloc(64);

}


//4、struct 增强
struct Person
{
	int age;
	//void func(); C语言下 结构体中不可以放函数
};
void test04()
{
	struct Person p1; // C语言下 声明结构体时候 必须加struct关键字
	p1.age = 17;
}


//5、bool类型增强 C语言下 没有bool类型
//bool flag;


//6、三目运算符增强
void  test06()
{
	int a = 10;
	int b = 20;

	printf("ret = %d\n", a > b ? a : b);

	*(a > b ? &a : &b )= 100;  // C语言下 三目运算符返回的是值 20 = 100


	printf("a = %d\n", a);
	printf("b = %d\n", b);
}

//7、const增强
const int m_A = 100; //全局const修饰变量 受到常量区保护，即使语法通过，运行阶段会报错
void test07()
{
	//m_A = 200;
	//int * p = &m_A;
	//*p = 200;

	const int m_B = 100; //局部const修饰的变量可以间接修改成功
	//m_B = 200;

	int * p2 = &m_B;
	*p2 = 200;

	printf("m_B = %d\n", m_B);

	//int arr[m_B]; //不可以初始化数组

}


int main(){

	//test06();
	test07();

	system("pause");
	return EXIT_SUCCESS;
}