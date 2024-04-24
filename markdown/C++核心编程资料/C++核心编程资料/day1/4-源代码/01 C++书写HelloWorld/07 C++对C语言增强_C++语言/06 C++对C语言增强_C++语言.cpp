#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、全局变量检测增强
//int a;
//int a = 10;


//2、函数检测增强  形参变量类型检测增强、 函数声明的返回值检测增强 、函数返回值检测增强、调用时候参数传入个数检测增强
int getRectS(int w, int h)
{
	return w * h;
}
void test02()
{
	getRectS(10, 10);
}

//3、类型转换检测增强
void test03()
{
	char * p = (char *)malloc(64);
}


//4、struct 增强
struct Person
{
	int age;
	void func(){ age++; }; //C++语言下 结构体中可以放函数
};

void test04()
{
	Person p1; // C++语言下 声明结构体时候 可以不加struct关键字
	p1.age = 17;
	p1.func();

	cout << "p1的年龄： " << p1.age << endl;
}


//5、bool类型增强 C语言下 没有bool类型  C++有bool类型
// bool类型 代表 真和假   真  true --- 1   加  false --- 0
bool flag = true;
void test05()
{
	cout << "sizeof bool = " << sizeof(bool) << endl;
	flag = 1000;
	cout << "flag = " << flag << endl;

}


//6、三目运算符增强
void  test06()
{
	int a = 10;
	int b = 20;

	printf("ret = %d\n", a > b ? a : b);

	a > b ? a : b = 100; // b = 100 C++语言下  三目运算符返回的是变量

	printf("a = %d\n", a);
	printf("b = %d\n", b);
}

//7、const增强
const int m_A = 100; //全局const修饰变量 受到常量区保护，即使语法通过，运行阶段会报错
void test07()
{
	//m_A = 200;
	//int * p = (int *)&m_A;
	//*p = 200;

	const int m_B = 100;
	//m_B = 200;
	int * p2 = (int *)&m_B;
	*p2 = 200;
	cout << "m_B = " << m_B << endl;

	int arr[m_B]; //可以用来初始化数组    常量

}



int main(){

	//test04();
	//test05();
	//test06();
	test07();
	system("pause");
	return EXIT_SUCCESS;
}