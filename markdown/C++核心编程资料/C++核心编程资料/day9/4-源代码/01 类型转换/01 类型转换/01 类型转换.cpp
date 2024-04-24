#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//1、静态类型转换
void test01()
{
	//内置数据类型
	char a = 'a';

	//static_cast<目标类型>(原对象)
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
	//自定义数据类型
	Base * base = NULL;
	Son * son = NULL;


	//base 转为 Son*类型    向下类型转换  不安全
	Son * son2 = static_cast<Son *>(base);

	//son 转为  Base * 类型      向上类型转换   安全
	Base* base2 = static_cast<Base*>(son);

	//base 转为 Other*
	//没有父子关系的两个类型之间是无法转换成功的
	//Other * other = static_cast<Other *>(base);

}

//2、动态类型转换
void test03()
{
	//内置数据类型 不允许内置数据类型之间的转换
	//char c = 'c';
	//double d = dynamic_cast<double>(c);

	
	//自定义数据类型
	Base * base = NULL;
	Son * son = NULL;

	//base 转为 Son* 类型  不安全  
	//不安全 转换失败
	//Son * son2 = dynamic_cast<Son*>(base);

	//son 转为  Base*   安全
	Base * base2 = dynamic_cast<Base*>(son);

	//base 转为Other* 
	//Other* other = dynamic_cast<Other*>(base);

	//如果发生多态，那么父子之间的转换 总是安全的
	Base * base3 = new Son;
	//将 base3转为  Son*
	Son * son3 = dynamic_cast<Son*>(base3);


}


//3、常量转换
void test04()
{
	//指针之间的转换
	const int * p = NULL;
	//将 const int * 转为 int *
	int * p2 = const_cast<int *>(p);

	//将 p2 转为  const int * 
	const int * p3 = const_cast<const int *>(p2);


	//引用之间的转换
	const int a = 10;
	const int & aRef = a;

	int & aRef2 = const_cast<int &>(aRef);

	//不可以对非指针 或者 非引用 做const_cast转换
	//int b = const_cast<int>(a);
}

//4、重新解释转换  最不安全 不建议用
void tet05()
{
	//int a = 10;
	//int * p = reinterpret_cast<int*>(a);

	//将base* 转为 Other * 
	Base * base = NULL;

	Other * other = reinterpret_cast<Other *>(base);
}

int main(){
	test01();


	system("pause");
	return EXIT_SUCCESS;
}